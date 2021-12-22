#include "TypeCheckerVisitor.h"
#include "CompilerVisitor.h"
#include "CommonVisitorFunction.h"
#include "VM/VirtualMachine.h"
#include "VM/Chunk.h"

#include <iostream>
#include <utility>

namespace Pomme
{

    /*
     * todo : modded + enum
     * */

    TypeCheckerVisitor::TypeCheckerVisitor()
	{
	}

    void TypeCheckerVisitor::visiteVariable(Node * node, bool isConst, const std::unordered_set<std::string>& keywords)
    {
        const std::string &context = class_name;
        bool isStatic = keywords.count("static");

        if(class_context && !instrs_context)
        {
            auto it = classMap.find(context);
            if( it != classMap.end())
            {
                if (path_number == 1)
                {
                    dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier = getVariableType(dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier);
                }

                std::string &attributeType = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
                std::string &attributeName = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1))->m_Identifier;

                std::cout << it->second << std::endl << std::endl;

                if (it->second.getAttribute(attributeName) != nullptr)
                {
                    errors.emplace_back("Can't redefine variable " + attributeName);
                    return;
                }

                it->second.addAttribute(attributeType, attributeName, isConst, isStatic, this);

                auto* constant = dynamic_cast<ASTPommeConstant*>(node);
                if(constant != nullptr)
                {
                    constant->index = isStatic ? it->second.staticAttributes.size() - 1 : it->second.attributes.size() - 1;
                    std::cout << " INDEX FOR VARIABLE "<< attributeName << " = " << constant->index << std::endl;
                }else
                {
                    auto* variable = dynamic_cast<ASTPommeVariable*>(node);
                    variable->index = isStatic ? it->second.staticAttributes.size() - 1 : it->second.attributes.size() - 1;
                    variable->isStatic = isStatic;
                    std::cout << " INDEX FOR VARIABLE "<< attributeName << " = " << variable->index << std::endl;
                }
            }else // todo check coverage to remove this branche
            {
                std::cout << "ERRORS DETECTED : class " << context << " not defined " << std::endl;
                errors.push_back("ERRORS DETECTED : class "+ context +" not defined ");
            }
        }else if(instrs_context)
        {
            std::cout << "instrs_context " << std::endl;
            if (path_number == 1)
            {
                dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier = getVariableType(dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier);
            }

            std::string& localType = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
            std::cout << "localType : " << localType << std::endl;
            std::string &localName = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1))->m_Identifier;

            for(int scope_number = 0; scope_number <= current_scopes; scope_number++)
            {
                auto ot = locals.find(scope_number);
                if(ot != locals.end())
                {
                    for(const auto& local : ot->second)
                    {
                        if(local.variableName == localName)
                        {
                            errors.push_back("ERRORS DETECTED : variable "+ localName +" already defined in another scope");
                        }
                    }
                }
            }

            auto it = locals.find(current_scopes);
            if(it == locals.end())
            {
                std::vector<VariableClass> locals_current_scopes;
                locals_current_scopes.emplace_back(localType, localName, 0, isConst);
                locals.emplace(current_scopes, std::move(locals_current_scopes));
            }else
            {
                it->second.emplace_back(localType, localName, it->second.size(),isConst);
            }
        }
    }

    void TypeCheckerVisitor::addGlobalFunction(const std::string &functionType, const std::string &functionName, const std::string functionIdent, bool native,
                                               std::unordered_set<std::string> parameters)
    {
        std::cout << "Adding global function " << functionName << " with type " << functionType << " with ident " << functionIdent << std::endl;
        auto access = globalFunctionsMap.find(functionIdent);
        if(access != globalFunctionsMap.end())
        {
            if(access->second.functionIdent == functionIdent)
            {
                errors.push_back("Global function "+functionName+" already defined");
            }
        }else
        {
            FunctionClass function(functionType, functionName, functionIdent, std::move(parameters),
                                   std::unordered_set<std::string>(), globalFunctionsMap.size(), native);
            globalFunctionsMap.emplace(functionIdent, function);
        }
    }

    void TypeCheckerVisitor::addEnum(const std::string& enumName)
    {
        std::cout << "Adding enum " << enumName << std::endl;

        auto access = enumMap.find(enumName);
        if(access != enumMap.end())
        {
            errors.push_back("Adding enum "+ enumName +" : Enum already defined");
            std::cout << "Adding enum " << enumName << " : Enum already defined" <<  std::endl;
        }else
        {
            EnumClass enumClass(enumName,{},"");
            enumMap.emplace(enumName,enumClass);
            std::cout << "inserted " << enumName << std::endl;
        }
    }
    void TypeCheckerVisitor::addClass(const std::string& className)
    {

        std::cout << "Adding class " << className << std::endl;

        auto access = classMap.find(className);
        if(access != classMap.end())
        {
            errors.push_back("Adding class "+ className +" : Class already defined");
            std::cout << "Adding class " << className << " : Class already defined" <<  std::endl;
        }else
        {
            ClassClass classClass;
            classMap.emplace(className, classClass);
            std::cout << "inserted " << className << std::endl;
        }
    }

    TypeCheckerVisitor::FunctionClass* TypeCheckerVisitor::ClassClass::getMethod(const std::string& methodName)
    {
        auto it = methods.find(methodName);
        if (it == methods.end())
        {
            auto ot = nativeMethods.find(methodName);
            if (ot == nativeMethods.end())
            {
                return nullptr;
            }

            return &ot->second;
        }

        return &it->second;
    }

    TypeCheckerVisitor::VariableClass* TypeCheckerVisitor::ClassClass::getAttribute(const std::string& attributeName)
    {
        auto it = attributes.find(attributeName);
        if (it == attributes.end())
        {
            auto ot = staticAttributes.find(attributeName);
            if (ot == staticAttributes.end())
            {
                return nullptr;
            }

            return &ot->second;
        }

        return &it->second;
    }

    void TypeCheckerVisitor::ClassClass::addAttribute(std::string &attributeType, std::string attributeName,
                                                 bool isConst, bool isStatic, TypeCheckerVisitor *typeCheckerVisitor)
    {
        std::cout << "Adding attribute " << attributeName <<  " with type " << attributeType << " isStatic : " << isStatic << std::endl;

        auto addAttribute = [&] (std::unordered_map<std::string, VariableClass>& attributes) {
            auto access = attributes.find(attributeName);
            if(access == attributes.end())
            {
                VariableClass variable(attributeType, attributeName, attributes.size(), isConst);
                attributes.emplace(attributeName, variable);
                std::cout << "inserted " << attributeName <<  " with type " << attributeType << std::endl;
            }else
            {
                typeCheckerVisitor->errors.push_back("addAttribute ERROR : " + attributeName+" already defined");
                std::cout << "ERROR DETECTED while adding attribute " << attributeName << " : attribute already defined" <<  std::endl;
            }
        };

        if (isStatic)
        {
            auto access = attributes.find(attributeName);
            if (access != attributes.end())
            {
                typeCheckerVisitor->errors.push_back("addAttribute ERROR : " + attributeName+" already defined");
                std::cout << "ERROR DETECTED while adding attribute " << attributeName << " : attribute already defined" <<  std::endl;
            }

            addAttribute(staticAttributes);
        }
        else
        {
            auto access = staticAttributes.find(attributeName);
            if (access != staticAttributes.end())
            {
                typeCheckerVisitor->errors.push_back("addAttribute ERROR : " + attributeName+" already defined");
                std::cout << "ERROR DETECTED while adding attribute " << attributeName << " : attribute already defined" <<  std::endl;
            }

            addAttribute(attributes);
        }
    }

    std::unordered_set<std::string> TypeCheckerVisitor::buildSignature(ASTPommeHeaders *headers) {
        std::unordered_set<std::string> parameters;
        Pomme::Node* header;

        std::string parameterName;
        std::string delimiter = " ";

        std::cout << "buildSignature" << std::endl;
        while(headers != nullptr)
        {
            header = headers->jjtGetChild(0);

            const int index = (dynamic_cast<ASTPommeHeader*>(header) != nullptr) ? 1 : 2;
            parameterName = dynamic_cast<ASTPommeIdent*>(header->jjtGetChild(index))->m_Identifier;

            auto it = parameters.emplace(parameterName);
            std::cout << " parameter NAME =+++ ++ ++ ++ ++ ++  + " << parameterName <<std::endl;
            if(!it.second)
            {
                errors.push_back("Parameter " + parameterName + " already defined");
                std::cout << "ERROR DETECTED while adding parameter " << parameterName << " : parameter already defined"
                          << std::endl;
            }
            headers = dynamic_cast<ASTPommeHeaders*>(headers->jjtGetChild(1));
        }

        std::cout << "-------------parameters--------------" <<std::endl;
        for(const auto& it : parameters)
        {
            std::cout << it << std::endl;
        }
        return parameters;
    }

    bool TypeCheckerVisitor::getMethodType(ASTPommeAccessMethode *node, std::string* variableType, std::string& functionIdent, const std::string& className)
    {
        auto* functionParameters = dynamic_cast<ASTPommeListExp*>(node->jjtGetChild(1));
        std::string typeExp = "";
        return getExpType(functionParameters, node, variableType, functionIdent, typeExp, className);
    }

    bool TypeCheckerVisitor::getExpType(ASTPommeListExp* node, ASTPommeAccessMethode *accessNode, std::string* variableType, std::string& functionIdent, std::string& current, const std::string& className)
    {
        if (node == nullptr)
        {
            std::cout << functionIdent << current << " className : " << className << std::endl;
            //global scope
            if (className == "")
            {
                auto ut = globalFunctionsMap.find(functionIdent + current);
                if (ut != globalFunctionsMap.end())
                {
                    functionIdent += current;

                    if (accessNode != nullptr)
                    {
                        accessNode->name = functionIdent;
                        accessNode->global = true;
                        accessNode->native = ut->second.native;
                        accessNode->index = ut->second.index;
                    }
                    
                    if (variableType != nullptr) *variableType = ut->second.returnType;
                    return true;
                }
            }
            else
            {
                auto it = classMap.find(className);
                if (it != classMap.end())
                {
                    FunctionClass* function = it->second.getMethod(functionIdent + current);
                    if (function != nullptr)
                    {
                        functionIdent += current;

                        if (accessNode != nullptr)
                        {
                            accessNode->global = false;
                            accessNode->native = function->native;
                            accessNode->index = function->index;
                            accessNode->methodCall = variableType == nullptr || *variableType == "";
                            accessNode->superCall = super_call;
                        }
                        
                        if (variableType != nullptr) *variableType = function->returnType;
                        return true;
                    }
                    else
                    {
                        auto ut = globalFunctionsMap.find(functionIdent + current);
                        if (ut != globalFunctionsMap.end())
                        {
                            functionIdent += current;

                            if (accessNode != nullptr)
                            {
                                accessNode->name = functionIdent;
                                accessNode->global = true;
                                accessNode->native = ut->second.native;
                                accessNode->index = ut->second.index;
                            }
                            
                            if (variableType != nullptr) *variableType = ut->second.returnType;
                            return true;
                        }
                    }
                }
            }

            return false;
        }

        std::string next = current;

        std::string type;
        node->jjtGetChild(0)->jjtAccept(this, &type);

        current += type + HEADER_FUNC_SEPARATOR;
        
        if (getExpType(dynamic_cast<ASTPommeListExp*>(node->jjtGetChild(1)), accessNode, variableType, functionIdent, current, className))
        {
            node->convert = false;
            return true;
        }

        auto it = classMap.find(type);
        if (it == classMap.end()) assert (false);

        if (FunctionClass* fnc = it->second.getMethod(std::string("operatorbool") + NAME_FUNC_SEPARATOR))
        {
            next += std::string("bool") + HEADER_FUNC_SEPARATOR;
            if (getExpType(dynamic_cast<ASTPommeListExp*>(node->jjtGetChild(1)), accessNode, variableType, functionIdent, next, className))
            {
                node->convert = true;
                node->convertTo = "bool";
                node->index = fnc->index;
                node->native = fnc->native;
                return true;
            }
        }

        return false;
    }

    std::unordered_set<std::string> TypeCheckerVisitor::buildKeyword(ASTPommeIdentFuncs *node)
    {
        std::unordered_set<std::string> keywords;

        auto* nodeStatic = dynamic_cast<ASTPommeStatic*>(node->jjtGetChild(0));
        if(nodeStatic != nullptr)
        {
            keywords.emplace("static");
        }

        node->jjtChildAccept(1, this, &keywords); // public protected or private
        if(!keywords.count("protected") && !keywords.count("public") && !keywords.count("private"))
        {
            keywords.emplace("private");
        }

        auto* nodeOverride = dynamic_cast<ASTPommeOverride*>(node->jjtGetChild(2));
        if(nodeOverride != nullptr)
        {
            keywords.emplace("override");
        }

        std::cout << "keyword :::::: " << std::endl;
        for(const auto& keyword : keywords )
        {
            std::cout << keyword << " ";
        }
        std::cout << std::endl;

        return keywords;
    }

    void TypeCheckerVisitor::visit(SimpleNode *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(ASTPommeInput *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(ASTPommeIdent *node, void * data)
    {
        switch (path_number)
        {
            case 0u:
            case 1u:
            {
                auto* variableType = static_cast<std::string*>(data);
                std::string currentClassName = [&] () {
                    //Special case, where we had the type of return of left expression
                    if (variableType != nullptr && *variableType != "") return (*variableType).c_str();

                    //Special case, where we don't have the type of return, and we are not in class_context
                    if (class_context) return class_name.c_str();

                    return "";
                }();     
                
                std::cout << "ASTPommeIdent identifier : " << node->m_Identifier << " currentClassName : " << currentClassName << std::endl;

                //locals should be checked only when on left side of listaccess
                if (variableType == nullptr || *variableType == "")
                {
                    // locals
                    for(int scopes = current_scopes; scopes >= 0; scopes-- )
                    {
                        auto it = locals.find(scopes);
                        if(it != locals.end())
                        {
                            for(auto ot : it->second)
                            {
                                if(ot.variableName == node->m_Identifier)
                                {
                                    if (variableType != nullptr)
                                    {
                                        *variableType = ot.variableType;
                                    }

                                    return;
                                }
                            }
                        }
                    }

                    //check this variable
                    if (class_context && node->m_Identifier == "this")
                    {
                        if (variableType != nullptr)
                        {
                            *variableType = class_name;
                        }

                        return;
                    }

                    //check super variable
                    if (node->m_Identifier == "super")
                    {
                        if (class_context)
                        {
                            auto it = classMap.find(currentClassName);
                            if (it->second.parent != "")
                            {
                                node->m_Super = true;
                                super_call = true;
                                if (variableType != nullptr)
                                {
                                    *variableType = it->second.parent;
                                }

                                return;
                            }

                            errors.emplace_back("Can't user super in not extended/modded class");
                            return;
                        }

                        errors.emplace_back("Can't user super outside of class");
                        return;
                    }
                }

                //attributes of current className
                auto it = classMap.find(currentClassName);
                if(it != classMap.end())
                {
                    //non static attributes
                    auto ot = it->second.attributes.find(node->m_Identifier);
                    if(ot != it->second.attributes.end())
                    {
                        std::cout << "index of ident " << node->m_Identifier << " in class " << currentClassName << " = " << ot->second.index << std::endl;
                        node->m_IndexAttribute = ot->second.index;
                        node->m_Attribute = true;

                        if (variableType != nullptr)
                        {
                            *variableType = ot->second.variableType;
                        }

                        return;
                    }

                    //static attributes
                    auto pt = it->second.staticAttributes.find(node->m_Identifier);
                    if(pt != it->second.staticAttributes.end())
                    {
                        std::cout << "index of static ident " << node->m_Identifier << " in class " << currentClassName << " = " << pt->second.index << std::endl;
                        node->m_IndexAttribute = pt->second.index;
                        node->m_Attribute = true;
                        
                        if (variableType != nullptr)
                        {
                            *variableType = pt->second.variableType;
                        }

                        return;
                    }
                }

                //check static class name
                auto ot = classMap.find(node->m_Identifier);
                if (ot != classMap.end())
                {
                    if (variableType != nullptr)
                    {
                        *variableType = node->m_Identifier;
                    }
                    return;
                }

                auto ut = enumMap.find(node->m_Identifier);
                if (ut != enumMap.end())
                {
                    if (variableType != nullptr)
                    {
                        *variableType = node->m_Identifier;
                    }

                    return;
                }

                errors.push_back("Variable " + node->m_Identifier + " not found in either attribute of class nor locals variables nor class name nor enum name");
                break;
            }
        }
    }

    void TypeCheckerVisitor::visit(ASTPommeIdentOp *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeInt *node, void * data)
    {
        if (data == nullptr) return;
        
        auto* variableType = static_cast<std::string*>(data);
        *variableType = "int";
    }

    void TypeCheckerVisitor::visit(ASTPommeFloat *node, void * data)
    {
        if (data == nullptr) return;
        
        auto* variableType = static_cast<std::string*>(data);
        *variableType = "float";
    }

    void TypeCheckerVisitor::visit(ASTPommeString *node, void * data)
    {
        if (data == nullptr) return;
        
        auto* variableType = static_cast<std::string*>(data);
        *variableType = "string";
    }

    void TypeCheckerVisitor::visit(ASTPommeScopes *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }

    void TypeCheckerVisitor::visit(ASTPommeScinil *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }

    void TypeCheckerVisitor::visit(ASTPommeTypeDef *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeClass *node, void * data)
    {
        const std::string& context = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;

        class_context = true;
        class_name = context;

        switch (path_number)
        {
            case 0u:
            {
                addClass(context);
                moddedMap.emplace(context, context);
                node->jjtChildAccept(1, this, data);
                break;
            }

            case 1u:
            {
                auto it = classMap.find(context);
                assert(it != classMap.end());

                std::string constructorIdent = class_name + NAME_FUNC_SEPARATOR;
                node->generateDefaultConstructor = it->second.methods.find(constructorIdent) == it->second.methods.end();
                std::cout << "generateDefaultConstructor : " << node->generateDefaultConstructor << std::endl;
                if (node->generateDefaultConstructor)
                {
                    FunctionClass function("void", constructorIdent, std::string(), {}, {}, it->second.methods.size(), false);
                    node->defaultConstructorIndex = function.index;
                    it->second.methods.emplace(constructorIdent, std::move(function));
                    node->constructorIdent = std::move(constructorIdent);
                }
                
                node->nmbMethods = it->second.methods.size();
                node->nmbNativeMethods = it->second.nativeMethods.size();
                node->nmbStaticFields = it->second.staticAttributes.size();
                node->nmbFields = it->second.attributes.size();

                node->jjtChildAccept(1, this, data);
                break;
            }
        }

        class_context = false;
    }

    void TypeCheckerVisitor::visit(ASTPommeClassChild *node, void * data)
    {
        const std::string& context = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
        std::string& extendedClass = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1))->m_Identifier;

        class_context = true;
        class_name = context;
        child_context = true;
        parent_name = extendedClass;

        switch (path_number)
        {
            case 0u:
            {
                if (CommonVisitorFunction::isNativeType(extendedClass))
                {
                    errors.push_back("Can't extend from native type");
                    return;
                }

                if (classMap.find(extendedClass) == classMap.end())
                {
                    errors.push_back(context + " is extending a non existing class " + extendedClass);
                    return;
                }

                extendedClass = getVariableType(extendedClass);
                parent_name = extendedClass;

                auto it = classMap.find(extendedClass);
                if(it != classMap.end())
                {
                    addClass(context);
                    moddedMap.emplace(class_name, class_name);
                    ClassClass& classClass = classMap.find(context)->second;
                    classClass.parent = extendedClass;
                    classClass.methods = it->second.methods;
                    classClass.nativeMethods = it->second.nativeMethods;
                    classClass.attributes = it->second.attributes;
                    classClass.staticAttributes = it->second.staticAttributes;
                    classClass.keywords.emplace("extends");
                }

                node->jjtChildAccept(2, this, data);
                break;
            }

            case 1u:
            {
                auto it = classMap.find(class_name);
                assert(it != classMap.end());

                std::string constructorIdent = class_name + NAME_FUNC_SEPARATOR;
                node->generateDefaultConstructor = it->second.methods.find(constructorIdent) == it->second.methods.end();
                if (node->generateDefaultConstructor)
                {
                    FunctionClass function("void", constructorIdent, std::string(), {}, {}, it->second.methods.size(), false);
                    node->defaultConstructorIndex = function.index;
                    it->second.methods.emplace(constructorIdent, std::move(function));
                    node->constructorIdent = std::move(constructorIdent);
                }

                auto& superClass = classMap[parent_name];
                std::cout << "parent_name : " << parent_name << std::endl;
                assert(superClass.methods.find(parent_name + NAME_FUNC_SEPARATOR) != superClass.methods.end());
                node->defaultSuperConstructorIndex = superClass.methods.find(parent_name + NAME_FUNC_SEPARATOR)->second.index;
                
                node->nmbMethods = it->second.methods.size();
                node->nmbNativeMethods = it->second.nativeMethods.size();
                node->nmbStaticFields = it->second.staticAttributes.size();
                node->nmbFields = it->second.attributes.size();

                node->jjtChildAccept(2, this, data);
                break;
            }
        }

        class_context = false;
        child_context = false;
    }

    void TypeCheckerVisitor::visit(ASTPommeModdedClass *node, void * data)
    {
        std::string& context = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;

        class_context = true;
        class_name = context;
        child_context = true;
        parent_name = node->parentName;
        modded_context = true;

        switch (path_number)
        {
            case 0u:
            {
                static auto randString = [] (std::size_t length) -> std::string {
                    static auto randchar = [] () -> char
                    {
                        const char charset[] =
                        "0123456789"
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        "abcdefghijklmnopqrstuvwxyz";
                        const size_t max_index = (sizeof(charset) - 1);
                        return charset[ rand() % max_index ];
                    };
                    std::string str(length, 0);
                    std::generate_n( str.begin(), length, randchar);
                    return str;
                }; 

                std::cout << "context moddedClass : " << context << std::endl;

                auto it = moddedMap.find(context);
                if (it == moddedMap.end())
                {
                    errors.push_back("Can't find className : " + context);
                    return;
                }

                //Generate unique id for this class
                std::string id = context + "@" + randString(10u);
                auto ot = classMap.find(id);
                while (ot != classMap.end())
                {
                    id = context + "@" + randString(10u);
                    ot = classMap.find(id);
                }

                auto jt = classMap.find(it->second);

                node->defaultClassName = context;
                node->parentName = it->second;
                context = id;
                class_name = context;
                parent_name = node->parentName;

                std::cout << "context : " << context << " parentName : " << node->parentName << " defaultClassName : " << node->defaultClassName << std::endl;

                addClass(context);
                ClassClass& classClass = classMap[context];
                classClass.parent = it->second;
                classClass.methods = jt->second.methods;
                classClass.nativeMethods = jt->second.nativeMethods;
                classClass.attributes = jt->second.attributes;
                classClass.staticAttributes = jt->second.staticAttributes;
                classClass.keywords.emplace("modded");

                moddedMap[node->defaultClassName] = id;

                node->jjtChildAccept(1, this, data);
                break;
            }

            case 1u:
            {
                auto it = classMap.find(class_name);
                assert(it != classMap.end());

                std::string constructorIdent = class_name + NAME_FUNC_SEPARATOR;
                node->generateDefaultConstructor = it->second.methods.find(constructorIdent) == it->second.methods.end();
                if (node->generateDefaultConstructor)
                {
                    FunctionClass function("void", constructorIdent, std::string(), {}, {}, it->second.methods.size(), false);
                    node->defaultConstructorIndex = function.index;
                    it->second.methods.emplace(constructorIdent, std::move(function));
                    node->constructorIdent = std::move(constructorIdent);
                }

                auto& superClass = classMap[node->parentName];
                std::cout << node->parentName << " : " << superClass << std::endl;
                node->defaultSuperConstructorIndex = superClass.methods.find(node->parentName + NAME_FUNC_SEPARATOR)->second.index;
                
                node->nmbMethods = it->second.methods.size();
                node->nmbNativeMethods = it->second.nativeMethods.size();
                node->nmbStaticFields = it->second.staticAttributes.size();
                node->nmbFields = it->second.attributes.size();

                node->jjtChildAccept(1, this, data);
                break;
            }
        }

        class_context = false;
        child_context = false;
        modded_context = false;
    }

    void TypeCheckerVisitor::visit(ASTPommeDecls *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }

    void TypeCheckerVisitor::visit(ASTPommeVarDecls *node, void * data)
    {
        switch (path_number)
        {
            case 0u:
            {
                std::unordered_set<std::string> keywords = buildKeyword(dynamic_cast<ASTPommeIdentFuncs*>(node->jjtGetChild(0)));
                visiteVariable(node->jjtGetChild(1), dynamic_cast<ASTPommeConstant*>(node->jjtGetChild(1)) != nullptr, keywords);
                break;
            }

            case 1u:
            case 2u:
            {
                std::unordered_set<std::string> keywords = buildKeyword(dynamic_cast<ASTPommeIdentFuncs*>(node->jjtGetChild(0)));
                
                if (dynamic_cast<ASTPommeVariable*>(node->jjtGetChild(1)) != nullptr)
                {
                    checkVariable(dynamic_cast<ASTPommeVariable*>(node->jjtGetChild(1)));
                }
                else
                {
                    checkVariable(dynamic_cast<ASTPommeConstant*>(node->jjtGetChild(1)));
                }
            }
        }
    }
    void TypeCheckerVisitor::visit(ASTPommeVariable *node, void * data)
    {
        switch (path_number)
        {
            case 0u:
            {
                visiteVariable(node, false, {});
                break;
            }

            case 1u:
            case 2u:
            {
                visiteVariable(node, false, {});

                checkVariable(node);
                break;
            }
        }
    }

    void TypeCheckerVisitor::visit(ASTPommeDnil *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeMethode *node, void * data)
    {
        switch (path_number)
        {
            case 0u:
            {
                std::unordered_set<std::string> keywords = buildKeyword(dynamic_cast<ASTPommeIdentFuncs*>(node->jjtGetChild(0)));
                auto* type = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1));
                std::string functionType = [&] () {
                    if(type == nullptr)
                    {
                        return "void";
                    }

                    return type->m_Identifier.c_str();
                }();
                auto* name = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(2));
                auto* nameOp = dynamic_cast<ASTPommeIdentOp*>(node->jjtGetChild(2));
                assert(name != nullptr || nameOp != nullptr);

                const std::string& functionName = (name != nullptr) ? name->m_Identifier : nameOp->m_Identifier;
                std::string functionIdent = functionName + NAME_FUNC_SEPARATOR;

                auto it = classMap.find(class_name);
                if(it == classMap.end())
                {
                    errors.push_back("class" + class_name + "not defined");
                }

                if (functionName == class_name && !keywords.count("static"))
                {
                    errors.push_back("can't define a method with the same name of the class");
                }

                auto* headers = dynamic_cast<ASTPommeHeaders*>(node->jjtGetChild(3)); // headers
                std::unordered_set<std::string> parameters = buildSignature(headers);
                std::string signatureParameter = CommonVisitorFunction::getParametersType(headers);
                functionIdent += signatureParameter;
                bool overriding = false;

                if(keywords.count("override"))
                {
                    if(!it->second.keywords.count("extends") && !it->second.keywords.count("modded"))
                    {
                        errors.push_back("Overriding method " + functionName + " while your class don't extends/mod any other class");
                    }

                    auto parent = classMap.find(it->second.parent);
                    if(parent != classMap.end())
                    {
                        auto* function = parent->second.getMethod(functionIdent);
                        if(function == nullptr)
                        {
                            errors.push_back("Overriding method " + functionName + " while your parent class don't have this method defined");
                        }
                        else
                        {
                            overriding = true;
                        }
                    }
                    else
                    {
                        errors.push_back("Can't find parent class with name : " + it->second.parent);
                    }
                }

                it->second.addFunction(node, functionType, functionIdent, parameters, keywords, false, overriding, this);

                if (name != nullptr)
                {
                    name->m_MethodIdentifier = functionIdent;
                }
                else
                {
                    nameOp->m_MethodIdentifier = functionIdent;
                }
                
                break;
            }

            case 1u:
            {
                node->jjtChildAccept(3, this, data); // headers
                node->jjtChildAccept(4, this, data); // instrs
                break;
            }
        }
    }

    void TypeCheckerVisitor::visit(ASTPommeMethodeNative *node, void * data)
    {
        switch (path_number)
        {
            case 0u:
            {
                std::unordered_set<std::string> keywords;

                if (dynamic_cast<ASTPommeSnil*>(node->jjtGetChild(0)) == nullptr)
                {
                    keywords.emplace("static");
                }

                auto* type = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(2));
                std::string functionType = [&] () {
                    if(type == nullptr)
                    {
                        return "void";
                    }

                    return type->m_Identifier.c_str();
                }();
                auto* name = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(3));
                auto* nameOp = dynamic_cast<ASTPommeIdentOp*>(node->jjtGetChild(3));
                assert(name != nullptr || nameOp != nullptr);

                const std::string& functionName = (name != nullptr) ? name->m_Identifier : nameOp->m_Identifier;
                std::string functionIdent = functionName + NAME_FUNC_SEPARATOR;
                const std::string &context = class_name;

                auto it = classMap.find(context);
                if(it == classMap.end())
                {
                    errors.push_back("class" + context + "not defined");
                    return;
                }

                if (functionName == context && !keywords.count("static"))
                {
                    errors.push_back("can't define a method with the same name of the class");
                    return;
                }

                if(keywords.count("override"))
                {
                    errors.push_back("you can't override a native method");
                    return;
                }

                auto* headers = dynamic_cast<ASTPommeHeaders*>(node->jjtGetChild(4)); // headers
                std::unordered_set<std::string> parameters = buildSignature(headers);
                std::string signatureParameter = CommonVisitorFunction::getParametersType(headers);
                functionIdent += signatureParameter;

                auto parent = classMap.find(it->second.parent);
                if(parent != classMap.end())
                {
                    if (parent->second.nativeMethods.count(functionIdent))
                    {
                        errors.push_back("you can't override a native method");
                        return;
                    }
                }

                it->second.addFunction(node, functionType, functionIdent, parameters, keywords, true, false, this);

                if (name != nullptr)
                {
                    name->m_MethodIdentifier = functionIdent;
                }
                else
                {
                    nameOp->m_MethodIdentifier = functionIdent;
                }

                break;
            }
        }
    }

    void TypeCheckerVisitor::visit(ASTPommeIdentFuncs *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeStatic *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeSnil *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommePublic *node, void * data)
    {
        static_cast<std::unordered_set<std::string>*>(data)->insert("public");
    }

    void TypeCheckerVisitor::visit(ASTPommePrivate *node, void * data)
    {
        static_cast<std::unordered_set<std::string>*>(data)->insert("private");
    }

    void TypeCheckerVisitor::visit(ASTPommeProtected *node, void * data)
    {
        static_cast<std::unordered_set<std::string>*>(data)->insert("protected");
    }

    void TypeCheckerVisitor::visit(ASTPommeVinil *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeOverride *node, void * data)
    {
        static_cast<std::unordered_set<std::string>*>(data)->insert("override"); // check if correct todo
    }

    void TypeCheckerVisitor::visit(ASTPommeOnil *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeEnum *node, void * data)
    {
        switch (path_number)
        {
            case 0u: {
                std::string context = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
                addEnum(context);
                std::cout << "ASTPommeEnum " << std::endl;
                class_name = context;
                node->jjtChildAccept(1,this,data);
            }
        }
    }

    void TypeCheckerVisitor::visit(ASTPommeExtendsEnum *node, void * data)
    {
        switch (path_number)
        {
            case 0u: {
                std::string context = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
                std::string extendedEnum = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1))->m_Identifier;

                addEnum(context);
                std::cout << "ASTPommeExtendsEnum " << std::endl;

                auto it = enumMap.find(extendedEnum);
                if(it != enumMap.end())
                {
                    EnumClass& enumClass = enumMap.find(extendedEnum)->second;
                    enumClass.parent = extendedEnum;
                    enumMap.emplace(context, enumClass);
                    enumMap.find(context)->second.keywords.emplace("extends");
                }else
                {
                    errors.push_back(context + " is extending a non existing enum : " + extendedEnum);
                }

                class_name = context;
                node->jjtChildAccept(2,this,data);
            }
        }
    }

    void TypeCheckerVisitor::visit(ASTPommeModdedEnum *node, void * data)
    {
        switch (path_number)
        {
            case 0u: {
                std::string context = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
                addEnum(context);
                std::cout << "ASTPommeModdedEnum " << std::endl;
                class_name = context;
                node->jjtChildAccept(1,this,data);
            }
        }
    }

    void TypeCheckerVisitor::visit(ASTPommeDeclEnums *node, void * data)
    {
        node->jjtChildrenAccept(this,data);
    }

    void TypeCheckerVisitor::visit(ASTPommeEnnil *node, void * data)
    {
    }

    void TypeCheckerVisitor::checkNewMember(std::basic_string<char> enumName, std::basic_string<char> memberName)
    {
        auto currentEnum = this->enumMap.find(enumName);
        if(currentEnum != this->enumMap.end()) {
            if (std::find(currentEnum->second.members.begin(), currentEnum->second.members.end(), memberName) !=
                currentEnum->second.members.end())
            {
                this->errors.push_back("Member : " + memberName + " already defined in enum " + enumName);
            } else
            {
                currentEnum->second.members.push_back(memberName);
            }
        }
    }
    
    void TypeCheckerVisitor::visit(ASTPommeEnumAssign *node, void * data) {

        std::cout << " CLASS NAME = " << class_name << std::endl;
        std::string memberName = static_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
        checkNewMember(class_name, memberName);
    }

    void TypeCheckerVisitor::visit(ASTPommeEnumDefault *node, void * data)
    {
        std::cout << " CLASS NAME = "<< class_name <<std::endl;
        std::string memberName = static_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
        checkNewMember(class_name, memberName);
    }

    void TypeCheckerVisitor::visit(ASTPommeGlobalFunction *node, void * data)
    {
        switch (path_number)
        {
            case 0u:
            {
                std::cout << "ASTPommeGlobalFunction path 0" << std::endl;
                break;
            }

            case 1u:
            {
                ASTPommeIdent* functionIdentNode = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1));
                std::string functionName = functionIdentNode->m_Identifier;
                auto* headers = dynamic_cast<ASTPommeHeaders*>(node->jjtGetChild(2));
                std::string signatureParameter = CommonVisitorFunction::getParametersType(headers);
                std::unordered_set<std::string> parameters = buildSignature(headers);

                std::string functionIdent = functionName + NAME_FUNC_SEPARATOR + signatureParameter;

                std::cout << "parameters ___________________________" << std::endl;
                for(const auto& it : parameters)
                {
                    std::cout << it << std::endl;
                }

                functionIdentNode->m_MethodIdentifier = functionIdent;

                auto* typeIdentNode = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0));
                addGlobalFunction ( (
                        (typeIdentNode != nullptr) ? 
                        typeIdentNode->m_Identifier //get return type
                        : "void"
                    ),
                    functionName,
                    functionIdent,
                    false,
                    parameters
                );

                node->jjtChildAccept(2, this, data); // headers
                node->jjtChildAccept(3, this, data); // instrs
                break;
            }
        }
    }

    void TypeCheckerVisitor::visit(ASTPommeGlobalFunctionNative *node, void * data)
    {
        switch (path_number)
        {
            case 1u:
            {
                ASTPommeIdent* functionIdentNode = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1));
                std::string functionName = functionIdentNode->m_Identifier;
                auto* headers = dynamic_cast<ASTPommeHeaders*>(node->jjtGetChild(2));
                std::string signatureParameter = CommonVisitorFunction::getParametersType(headers);
                std::unordered_set<std::string> parameters = buildSignature(headers);
                
                std::string functionIdent = functionName + NAME_FUNC_SEPARATOR + signatureParameter;

                std::cout << "parameters ___________________________" << std::endl;
                for(const auto& it : parameters)
                {
                    std::cout << it << std::endl;
                }

                auto* typeIdentNode = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0));
                addGlobalFunction ( (
                        (typeIdentNode != nullptr) ? 
                        typeIdentNode->m_Identifier //get return type
                        : "void"
                    ),
                    functionName,
                    functionIdent,
                    true,
                    parameters
                );

                functionIdentNode->m_MethodIdentifier = functionIdent;
                break;
            }
        }
    }

    void TypeCheckerVisitor::visit(ASTPommeInstrs *node, void * data)
    {
        instrs_context = true;
        node->jjtChildrenAccept(this, data);
        instrs_context = false;
    }

    void TypeCheckerVisitor::visit(ASTPommeInil *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeIncrPre *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeDecrPre *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeDelete *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeReturn *node, void * data)
    {
        std::string type;
        node->jjtChildrenAccept(this, &type);

        //TODO: check if it's equal to the return type of the current function
    }

    void TypeCheckerVisitor::visit(ASTPommeWhile *node, void * data)
    {
        current_scopes++;

        current_scopes--;
    }

    void TypeCheckerVisitor::visit(ASTPommeBreak *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeIf *node, void * data)
    {
        std::string type;
        node->jjtChildAccept(0, this, &type);

        node->convert = false;
        node->testNull = false;

        if (type != "bool")
        {
            auto it = classMap.find(type);
            if (it == classMap.end())
            {
                errors.push_back("Can't find class name : " + type);
                return;
            }

            if (FunctionClass* fnc = it->second.getMethod(std::string("operatorbool") + NAME_FUNC_SEPARATOR))
            {
                node->convert = true;
                node->index = fnc->index;
                node->native = fnc->native;
            }
            else
            {
                node->testNull = true;
            }
        }

        current_scopes++;
        node->jjtChildAccept(1, this, data);
        current_scopes--;

        current_scopes++;
        node->jjtChildAccept(2, this, data);
        current_scopes--;
    }

    void TypeCheckerVisitor::visit(ASTPommePrint *node, void * data)
    {
        std::string type;
        node->jjtChildrenAccept(this, &type);
    }

    void TypeCheckerVisitor::visit(ASTPommeSwitch *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeAssign *node, void * data)
    {
        std::string leftType = "";
        node->jjtChildAccept(0, this, &leftType);

        std::string rightType = "";
        node->jjtChildAccept(1, this, &rightType);

        std::cout << "path_number : " << unsigned(path_number) << " leftType : " << leftType << " rightType : " << rightType << std::endl;

        if (leftType == "")
        {
            errors.push_back("Can't find variable type of left expression");
            return;
        }

        if (rightType == "")
        {
            errors.push_back("Can't find variable type of right expression");
            return;
        }

        if (leftType != rightType)
        {
            errors.push_back("Can't assign class " + rightType + " to class " + leftType);
            return;
        }

    }

    void TypeCheckerVisitor::visit(ASTPommeAddEq *node, void * data)
    {
        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator+=", nullptr, types);
    }

    void TypeCheckerVisitor::visit(ASTPommeMinusEq *node, void * data)
    {
        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator-=", nullptr, types);
    }

    void TypeCheckerVisitor::visit(ASTPommeDivEq *node, void * data)
    {
        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator/=", nullptr, types);
    }

    void TypeCheckerVisitor::visit(ASTPommeMultEq *node, void * data)
    {
        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator*=", nullptr, types);
    }

    void TypeCheckerVisitor::visit(ASTPommeOrEq *node, void * data)
    {
        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator|=", nullptr, types);
    }

    void TypeCheckerVisitor::visit(ASTPommeAndEq *node, void * data)
    {
        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator&=", nullptr, types);
    }

    void TypeCheckerVisitor::visit(ASTPommeShiftLEq *node, void * data)
    {
        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator<<=", nullptr, types);
    }

    void TypeCheckerVisitor::visit(ASTPommeShiftREq *node, void * data)
    {
        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator>>=", nullptr, types);
    }

    void TypeCheckerVisitor::visit(ASTPommeIncrPost *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeDecrPost *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeCases *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeDefault *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeSwinil *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeCase *node, void * data)
    {
        current_scopes++;

        current_scopes--;
    }

    void TypeCheckerVisitor::visit(ASTPommeListExp *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeExnil *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeConstant *node, void * data)
    {
        switch (path_number)
        {
            case 0u:
            {
                visiteVariable(node, true, {});
                break;
            }

            case 1u:
            {
                visiteVariable(node, false, {});

                checkVariable(node);
                break;
            }
        }
    }

    void TypeCheckerVisitor::visit(ASTPommeOmega *node, void * data)
    {
        if (data == nullptr) return;
        
        auto* variableType = static_cast<std::string*>(data);
        *variableType = "null";
    }

    void TypeCheckerVisitor::visit(ASTPommeHeaders *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }

    void TypeCheckerVisitor::visit(ASTPommeEnil *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeConstHeader *node, void * data)
    {
        std::string &localType = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1))->m_Identifier;
        std::string &localName = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(2))->m_Identifier;

        auto it = locals.find(current_scopes);
        if(it == locals.end())
        {
            std::vector<VariableClass> locals_current_scopes;
            locals_current_scopes.emplace_back(localType, localName, -1, true);
            locals.emplace(current_scopes, std::move(locals_current_scopes));
        }
        else
        {
            it->second.emplace_back(localType, localName, -1, true);
        }
    }

    void TypeCheckerVisitor::visit(ASTPommeHeader *node, void * data)
    {
        std::string &localType = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
        std::string &localName = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1))->m_Identifier;

        auto it = locals.find(current_scopes);
        if(it == locals.end())
        {
            std::vector<VariableClass> locals_current_scopes;
            locals_current_scopes.emplace_back(localType, localName, -1, false);
            locals.emplace(current_scopes, std::move(locals_current_scopes));
        }
        else
        {
            it->second.emplace_back(localType, localName, -1, false);
        }
    }

    void TypeCheckerVisitor::visit(ASTPommeVoidType *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeConstructor *node, void * data)
    {
        switch (path_number)
        {
            case 0u:
            {
                std::string functionType = "void";
                auto* name = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0));
                std::string &functionName = name->m_Identifier;
                if (modded_context)
                {
                    functionName = class_name;
                }

                const std::string &context = class_name;

                auto it = classMap.find(context);
                if(it == classMap.end()){
                    errors.push_back("class" + context + "not defined");
                }

                if (functionName != context)
                {
                    errors.push_back("Can't define a constructor with not the same identifier as class. (" + functionName + " expected " + context + ")");
                    return;
                }

                auto* headers = dynamic_cast<ASTPommeHeaders*>(node->jjtGetChild(1)); // headers
                std::unordered_set<std::string> parameters = buildSignature(headers);
                std::string signatureParameter = CommonVisitorFunction::getParametersType(headers);
                std::string functionIdent = functionName + NAME_FUNC_SEPARATOR + signatureParameter;

                it->second.addFunction(node, functionType, functionIdent, parameters, {}, false, false, this);
                name->m_MethodIdentifier = functionIdent;
                node->generateSuperCall = child_context && functionIdent == (class_name + NAME_FUNC_SEPARATOR);
                std::cout << "generateSuperCall " << node->generateSuperCall << " for " << functionIdent << std::endl;
                break;
            }

            case 1u:
            {
                node->jjtChildAccept(1, this, data); // headers
                node->jjtChildAccept(2, this, data); // instrs
                break;
            }
        }

    }

    void TypeCheckerVisitor::visit(ASTPommeDestructor *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeAnd *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeOr *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeEQ *node, void * data)
    {
        assert(data != nullptr);

        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator==", static_cast<std::string*>(data), types);
    }

    void TypeCheckerVisitor::visit(ASTPommeNEQ *node, void * data)
    {
        assert(data != nullptr);

        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator!=", static_cast<std::string*>(data), types);
    }

    void TypeCheckerVisitor::visit(ASTPommeGT *node, void * data)
    {
        assert(data != nullptr);

        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator>", static_cast<std::string*>(data), types);
    }

    void TypeCheckerVisitor::visit(ASTPommeGET *node, void * data)
    {
        assert(data != nullptr);

        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator>=", static_cast<std::string*>(data), types);
    }

    void TypeCheckerVisitor::visit(ASTPommeLT *node, void * data)
    {
        assert(data != nullptr);

        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator<", static_cast<std::string*>(data), types);

        if (types[0] == "int")
        {
            if (types[1] == "int")
            {
                node->primitive = true;
                node->opCode = OpCode::OP_LT_INT_INT;
            }
            else if (types[1] == "float")
            {
                node->primitive = true;
                node->opCode = OpCode::OP_LT_INT_FLOAT;
            }
        }
        else if (types[0] == "float")
        {
            if (types[1] == "int")
            {
                node->primitive = true;
                node->opCode = OpCode::OP_LT_FLOAT_INT;
            }
            else if (types[1] == "float")
            {
                node->primitive = true;
                node->opCode = OpCode::OP_LT_FLOAT_FLOAT;
            }
        }
    }

    void TypeCheckerVisitor::visit(ASTPommeLET *node, void * data)
    {
        assert(data != nullptr);

        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator<=", static_cast<std::string*>(data), types);
    }

    void TypeCheckerVisitor::visit(ASTPommeAdd *node, void * data)
    {
        assert(data != nullptr);

        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator+", static_cast<std::string*>(data), types);

        if (types[0] == "int")
        {
            if (types[1] == "int")
            {
                node->primitive = true;
                node->opCode = OpCode::OP_ADD_INT_INT;
            }
            else if (types[1] == "float")
            {
                node->primitive = true;
                node->opCode = OpCode::OP_ADD_INT_FLOAT;
            }
        }
        else if (types[0] == "float")
        {
            if (types[1] == "int")
            {
                node->primitive = true;
                node->opCode = OpCode::OP_ADD_FLOAT_INT;
            }
            else if (types[1] == "float")
            {
                node->primitive = true;
                node->opCode = OpCode::OP_ADD_FLOAT_FLOAT;
            }
        }
    }

    void TypeCheckerVisitor::visit(ASTPommeMinus *node, void * data)
    {
        assert(data != nullptr);

        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator-", static_cast<std::string*>(data), types);

        if (types[0] == "int")
        {
            if (types[1] == "int")
            {
                node->primitive = true;
                node->opCode = OpCode::OP_MINUS_INT_INT;
            }
            else if (types[1] == "float")
            {
                node->primitive = true;
                node->opCode = OpCode::OP_MINUS_INT_FLOAT;
            }
        }
        else if (types[0] == "float")
        {
            if (types[1] == "int")
            {
                node->primitive = true;
                node->opCode = OpCode::OP_MINUS_FLOAT_INT;
            }
            else if (types[1] == "float")
            {
                node->primitive = true;
                node->opCode = OpCode::OP_MINUS_FLOAT_FLOAT;
            }
        }
    }

    void TypeCheckerVisitor::visit(ASTPommeShiftR *node, void * data)
    {
        assert(data != nullptr);

        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator>>", static_cast<std::string*>(data), types);
    }

    void TypeCheckerVisitor::visit(ASTPommeShiftL *node, void * data)
    {
        assert(data != nullptr);

        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator<<", static_cast<std::string*>(data), types);
    }

    void TypeCheckerVisitor::visit(ASTPommeMult *node, void * data)
    {
        assert(data != nullptr);

        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator*", static_cast<std::string*>(data), types);
    }

    void TypeCheckerVisitor::visit(ASTPommeDiv *node, void * data)
    {
        assert(data != nullptr);

        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator/", static_cast<std::string*>(data), types);
    }

    void TypeCheckerVisitor::visit(ASTPommeModulo *node, void * data)
    {
        assert(data != nullptr);

        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator%", static_cast<std::string*>(data), types);
    }

    void TypeCheckerVisitor::visit(ASTPommeUnary *node, void * data)
    {
        visitUnaryOperator(node, "operator-", static_cast<std::string*>(data));
    }

    void TypeCheckerVisitor::visit(ASTPommeNot *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeTilde *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeNew *node, void * data)
    {
        std::string& className = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
        std::string defaultName = className;

        if (CommonVisitorFunction::isNativeType(className))
        {
            errors.push_back("can't use new on primitive types");
            return;
        }

        className = getVariableType(className);

        auto it = classMap.find(className);
        if (it == classMap.end())
        {
            errors.push_back("Can't find class name : " + className);
            return;
        }

        std::string constructorName = className + NAME_FUNC_SEPARATOR;
        std::string parameters = "";

        if (!getExpType(dynamic_cast<ASTPommeListExp*>(node->jjtGetChild(1)), nullptr, nullptr, constructorName, parameters, className))
        {
            errors.push_back("Can't find constructor with correct parameters");
            return;
        }

        auto ot = it->second.methods.find(constructorName);
        if (ot != it->second.methods.end())
        {
            node->foundConstructor = true;
            node->index = ot->second.index;
        }

        if (data == nullptr) return;
            
        auto* variableType = static_cast<std::string*>(data);
        *variableType = className;
    }

    void TypeCheckerVisitor::visit(ASTPommeTrue *node, void * data)
    {
        if (data == nullptr) return;
        
        auto* variableType = static_cast<std::string*>(data);
        *variableType = "bool";
    }

    void TypeCheckerVisitor::visit(ASTPommeFalse *node, void * data)
    {
        if (data == nullptr) return;
        
        auto* variableType = static_cast<std::string*>(data);
        *variableType = "bool";
    }

    void TypeCheckerVisitor::visit(ASTPommeNull *node, void * data)
    {
        if (data == nullptr) return;
        
        auto* variableType = static_cast<std::string*>(data);
        *variableType = "";
    }

    void TypeCheckerVisitor::visit(ASTPommeListAccess *node, void * data)
    {
        auto acceptListAccess = [&node, this] (void* dataPtr)
        {
            node->jjtChildAccept(0, this, dataPtr);

            if (super_call && dynamic_cast<ASTPommeAccessMethode*>(node->jjtGetChild(1)) == nullptr)
            {
                errors.push_back("Can't user super without a method after the '.'");
            }

            node->jjtChildAccept(1, this, dataPtr);
            super_call = false;

            node->jjtChildAccept(2, this, dataPtr);
        };

        if (data == nullptr)
        {
            std::string type = "";
            acceptListAccess(&type);
            return;
        }

        acceptListAccess(data);
    }

    void TypeCheckerVisitor::visit(ASTPommeListAccessP *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }

    void TypeCheckerVisitor::visit(ASTPommeAcnil *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTPommeAccessMethode *node, void * data)
    {
        auto* variableType = static_cast<std::string*>(data);

        auto *identNode = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0));
        std::string functionName = identNode->m_Identifier;
        std::string functionIdent = identNode->m_Identifier + NAME_FUNC_SEPARATOR;

        std::string className = [&] () {
            if(variableType != nullptr && *variableType != "")
            {
                return (*variableType).c_str();
            }
            
            if (class_context)
            {
                return class_name.c_str();
            }

            return "";
        }();

        if (!getMethodType(node, variableType, functionIdent, className))
        {
            //TODO: error
            errors.push_back("can't find method");
        }
    }

    void TypeCheckerVisitor::visit(ASTPommeAccessTab *node, void * data)
    {
        assert(data != nullptr);

        std::array<std::string, 2> types;
        visitBinaryOperator(node, "operator[]", static_cast<std::string*>(data), types);

        node->jjtChildAccept(2, this, data);
    }

    std::string TypeCheckerVisitor::getVariableType(const std::string& type)
    {
        return moddedMap[type];
    }
}