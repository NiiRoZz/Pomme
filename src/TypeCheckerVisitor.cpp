#include "TypeCheckerVisitor.h"
#include "CompilerVisitor.h"
#include "CommonVisitorFunction.h"
#include "VM/VirtualMachine.h"
#include "VM/Chunk.h"
#include "VM/Memory.h"

#include <iostream>
#include <utility>

namespace Pomme
{

    /*
     *
     * todo
     *
     *
     * instrs : definition + expression*/

    TypeCheckerVisitor::TypeCheckerVisitor()
	{
	}

    void TypeCheckerVisitor::visiteVariable(Node * node, bool isConst, const std::unordered_set<std::string>& keywords)
    {
        const std::string &context = class_name;

        for (const auto& it : classMap)
        {
            std::cout << it.first << std::endl;
        }

        bool isStatic = keywords.count("static");

        if(child_context)
        {
            //TODO: go through the hierarchy instead of just the parent of the class
            auto child = classMap.find(context);
            auto parent = classMap.find(child->second.parent);

            if( parent != classMap.end())
            {
                std::string &attributeType = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
                std::string &attributeName = dynamic_cast<ASTident*>(node->jjtGetChild(1))->m_Identifier;

                auto variable = parent->second.attributes.find(child->second.parent + "::" +attributeName);
                if(variable != parent->second.attributes.end())
                {
                    if(variable->second.variableType != attributeType)
                    {
                        errors.push_back("variable " + attributeName
                        + " is already defined in parent class with a different type. Expected type "
                        + variable->second.variableType + " but got "+ attributeType );
                    }
                }
                else
                {
                    child->second.addAttribute(attributeType, context + "::" + attributeName, isConst, isStatic, this);
                }
            }
        }else if(class_context && !instrs_context)
        {
            auto it = classMap.find(context);
            if( it != classMap.end())
            {
                std::string &attributeType = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
                std::string &attributeName = dynamic_cast<ASTident*>(node->jjtGetChild(1))->m_Identifier;

                it->second.addAttribute(attributeType, context + "::" + attributeName, isConst, isStatic, this);

                auto* constant = dynamic_cast<ASTpommeConstant*>(node);
                if(constant != nullptr)
                {
                    constant->index = isStatic ? it->second.staticAttributes.size() - 1 : it->second.attributes.size() - 1;
                    std::cout << " INDEX FOR VARIABLE "<< attributeName << " = " << constant->index << std::endl;
                }else
                {
                    auto* variable = dynamic_cast<ASTpommeVariable*>(node);
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
            std::string &localType = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
            std::string &localName = dynamic_cast<ASTident*>(node->jjtGetChild(1))->m_Identifier;

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

    void TypeCheckerVisitor::addGlobalFunction(const std::string &functionType, const std::string &functionName, const std::string functionIdent,
                                               std::unordered_set<std::string> parameters)
    {
        std::cout << "Adding global function " << functionName << " with type " << functionType << " with ident " << functionIdent << std::endl;
        auto access = globalFunctionsMap.find(functionIdent);
        if(access != globalFunctionsMap.end())
        {
            if(access->second.functionIdent == functionIdent)
            {
                errors.push_back("Global function "+functionName+" already defined");

            }else if(access->second.returnType != functionType)
            {
                errors.push_back("Global function "+functionName+" already defined with a different type. Expected "+access->second.returnType +" but got " + functionType);
            }
        }else
        {
            FunctionClass function(functionType, functionName, functionIdent, std::move(parameters),
                                   std::unordered_set<std::string>(),globalFunctionsMap.size());
            globalFunctionsMap.emplace(functionIdent, function);
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
            classMap.emplace(className,classClass);
            std::cout << "inserted " << className << std::endl;
        }
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

    void TypeCheckerVisitor::ClassClass::addFunction(std::string &functionType, std::string &functionName,
                                                     std::unordered_set<std::string> parameters, std::unordered_set<std::string> keywords,
                                                     bool isNative, TypeCheckerVisitor *typeCheckerVisitor)
    {

        auto addMethod = [&] (std::unordered_map<std::string, FunctionClass>& methods) {
            auto access = methods.find(functionName);
            if(access == methods.end())
            {
                FunctionClass function(functionType, functionName, std::string(), std::move(parameters),
                                   std::move(keywords), methods.size());
                methods.emplace(functionName, function);
                std::cout << "inserted " << functionName << " with type " << functionType << std::endl;
            }else
            {
                typeCheckerVisitor->errors.push_back("addFunction ERROR : " + functionName + " already defined");
                std::cout << "ERROR DETECTED while adding function " << functionName << " : function already defined" << std::endl;
            }
        };

        if (isNative)
        {
            auto access = methods.find(functionName);
            if (access != methods.end())
            {
                typeCheckerVisitor->errors.push_back("addFunction ERROR : " + functionName + " already defined");
                std::cout << "ERROR DETECTED while adding function " << functionName << " : function already defined" << std::endl;
            }

            addMethod(nativeMethods);
        }
        else
        {
            auto access = nativeMethods.find(functionName);
            if (access != nativeMethods.end())
            {
                typeCheckerVisitor->errors.push_back("addFunction ERROR : " + functionName + " already defined");
                std::cout << "ERROR DETECTED while adding function " << functionName << " : function already defined" << std::endl;
            }

            addMethod(methods);
        }
    }

    std::unordered_set<std::string> TypeCheckerVisitor::buildSignature(ASTheaders *headers) {
        std::unordered_set<std::string> parameters;
        ASTheader* header;

        std::string parameterName;
        std::string delimiter = " ";

        std::cout << "buildSignature" << std::endl;
        while(headers != nullptr)
        {
            header = dynamic_cast<ASTheader*>(headers->jjtGetChild(0));
            parameterName = dynamic_cast<ASTident*>(header->jjtGetChild(1))->m_Identifier;

            auto it = parameters.emplace(parameterName);
            std::cout << " parameter NAME =+++ ++ ++ ++ ++ ++  + " << parameterName <<std::endl;
            if(!it.second)
            {
                errors.push_back("Parameter " + parameterName + " already defined");
                std::cout << "ERROR DETECTED while adding parameter " << parameterName << " : parameter already defined"
                          << std::endl;
            }
            headers = dynamic_cast<ASTheaders*>(headers->jjtGetChild(1));
        }

        std::cout << "-------------parameters--------------" <<std::endl;
        for(const auto& it : parameters)
        {
            std::cout << it << std::endl;
        }
        return parameters;
    }

    std::string TypeCheckerVisitor::getExpTypes(Pomme::Node* node)
    {
        auto *functionParameters = dynamic_cast<ASTlistexp*>(node);
        std::string typeExp = "";

        while(functionParameters != nullptr)
        {
            std::string type;
            functionParameters->jjtGetChild(0)->jjtAccept(this, &type);
            typeExp += type + HEADER_FUNC_SEPARATOR;
            functionParameters = dynamic_cast<ASTlistexp*>(functionParameters->jjtGetChild(1));
        }

        return typeExp;
    }

    std::unordered_set<std::string> TypeCheckerVisitor::buildKeyword(ASTidentFuncs *node)
    {

        std::unordered_set<std::string> keywords;

        auto* nodeStatic = dynamic_cast<ASTpommeStatic*>(node->jjtGetChild(0));
        if(nodeStatic != nullptr)
        {
            keywords.emplace("static");
        }

        node->jjtChildAccept(1, this, &keywords); // public protected or private
        if(!keywords.count("protected") && !keywords.count("public") && !keywords.count("private"))
        {
            keywords.emplace("private");
        }

        auto* nodeOverride = dynamic_cast<ASTpommeOverride*>(node->jjtGetChild(2));
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
    void TypeCheckerVisitor::visit(ASTinput *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(ASTident *node, void * data)
    {
        auto* variableType = static_cast<std::string*>(data);
        std::string currentClassName = "";
        //Special case, where we had the type of return of left expression
        if (variableType != nullptr && *variableType != "")
        {
            currentClassName = *variableType;
        }
        //Special case, where we don't have the type of return, and we are not in class_context
        else if (class_context)
        {
            currentClassName = class_name;
        }
        
        std::cout << "ASTident identifier : " << node->m_Identifier << " currentClassName : " << currentClassName << std::endl;

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
        }

        //attributes and class
        auto it = classMap.find(currentClassName);
        if(it != classMap.end())
        {
            //non static attributes
            auto ot = it->second.attributes.find(currentClassName + "::" + node->m_Identifier);
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
            auto pt = it->second.staticAttributes.find(currentClassName + "::" + node->m_Identifier);
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

        errors.push_back("Variable "+ node->m_Identifier + " not found in either attribute of class nor locals variables ");
    }
    void TypeCheckerVisitor::visit(ASTidentOp *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeInt *node, void * data)
    {
        if (data == nullptr) return;
        
        auto* variableType = static_cast<std::string*>(data);
        *variableType = "int";
    }
    void TypeCheckerVisitor::visit(ASTpommeFloat *node, void * data)
    {
        if (data == nullptr) return;

        auto* variableType = static_cast<std::string*>(data);
        *variableType = "float";
    }
    void TypeCheckerVisitor::visit(ASTpommeString *node, void * data)
    {
        if (data == nullptr) return;

        auto* variableType = static_cast<std::string*>(data);
        *variableType = "string";
    }
    void TypeCheckerVisitor::visit(ASTscopes *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(ASTscinil *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(ASTpommeTypeDef *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeClass *node, void * data)
    {
        std::string context = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
        addClass(context);
        class_context = true;
        class_name = context;
        node->jjtGetChild(1)->jjtAccept(this, data);
        class_context = false;
    }

    void TypeCheckerVisitor::visit(ASTpommeClassChild *node, void * data)
    {
        /*if(path_number != 2){ // todo
            return;
        }*/
        std::string context = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
        std::string extendedClass = dynamic_cast<ASTident*>(node->jjtGetChild(1))->m_Identifier;

        if(classMap.count(context)){
            errors.push_back("ERROR DETECTED while adding class "+ context +" : Class already defined");
            std::cout << "ERROR DETECTED while adding class " << context << " : Class already defined" <<  std::endl;
        }


        auto it = classMap.find(extendedClass);
        if(it != classMap.end()){
            ClassClass& classClass = classMap.find(extendedClass)->second;
            classClass.parent = extendedClass;
            classMap.emplace(context, classClass);

            classMap.find(context)->second.keywords.emplace("extends");
        }
        if(it == classMap.end())
        {
            errors.push_back(context + " is extending a non existing class " + extendedClass);
        }

        class_context = true;
        class_name = context;
        child_context = true;
        node->jjtGetChild(2)->jjtAccept(this, data);
        child_context = false;
        class_context = false;
    }
    void TypeCheckerVisitor::visit(ASTpommeModdedClass *node, void * data)
    {
        //todo check modded class existence
    }
    void TypeCheckerVisitor::visit(ASTdecls *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(ASTvarDecls *node, void * data)
    {
        std::unordered_set<std::string> keywords = buildKeyword(dynamic_cast<ASTidentFuncs*>(node->jjtGetChild(0)));
        visiteVariable(node->jjtGetChild(1), dynamic_cast<ASTpommeConstant*>(node->jjtGetChild(1)) != nullptr, keywords);
    }
    void TypeCheckerVisitor::visit(ASTpommeVariable *node, void * data)
    {
        visiteVariable(node, false, {});

        node->jjtChildAccept(2, this, nullptr);
    }
    void TypeCheckerVisitor::visit(ASTdnil *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(ASTpommeMethode *node, void * data)
    {
        std::unordered_set<std::string> keywords = buildKeyword(dynamic_cast<ASTidentFuncs*>(node->jjtGetChild(0)));
        auto* type = dynamic_cast<ASTident*>(node->jjtGetChild(1));
        std::string functionType;
        auto* name = dynamic_cast<ASTident*>(node->jjtGetChild(2));
        std::string &functionName = name->m_Identifier;
        std::string functionIdent = functionName + NAME_FUNC_SEPARATOR;
        const std::string &context = class_name;

        auto it = classMap.find(context);
        if(it == classMap.end()){
            errors.push_back("class" + context + "not defined");
        }

        if (functionName == context && !keywords.count("static"))
        {
            errors.push_back("can't define a method with the same name of the class");
        }

        // todo child_context

        if(keywords.count("override"))
        {
            if(!it->second.keywords.count("extends") && !it->second.keywords.count("modded")){
                errors.push_back("Overriding method " + functionName + " while your class don't extends/mod any other class");
            }
            auto parent = classMap.find(it->second.parent);
            if(parent != classMap.end()){
                auto function = parent->second.methods.find(functionName);
                if(function == parent->second.methods.end())
                {
                    errors.push_back("Overriding method " + functionName + " while your parent class don't have this method defined");
                }
            }
        }

        if(type == nullptr)
        {
            functionType = "void";
        }else
        {
            functionType = type->m_Identifier;
        }

        auto* headers = dynamic_cast<ASTheaders*>(node->jjtGetChild(3)); // headers
        std::unordered_set<std::string> parameters = buildSignature(headers);
        std::string signatureParameter = CommonVisitorFunction::getParametersType(headers);

        if(!parameters.empty())
        {
            functionIdent += signatureParameter;
        }
        it->second.addFunction(functionType, functionIdent, parameters, keywords, false, this);
        node->index = it->second.methods.size() - 1;
        name->m_MethodIdentifier = functionIdent;

        node->jjtGetChild(3)->jjtAccept(this, data); // headers
        node->jjtGetChild(4)->jjtAccept(this, data); // instrs
    }

    void TypeCheckerVisitor::visit(ASTpommeMethodeNative *node, void * data)
    {
        std::unordered_set<std::string> keywords;

        if (dynamic_cast<ASTsnil*>(node->jjtGetChild(0)) == nullptr)
        {
            keywords.emplace("static");
        }

        auto* type = dynamic_cast<ASTident*>(node->jjtGetChild(2));
        std::string functionType;
        auto* name = dynamic_cast<ASTident*>(node->jjtGetChild(3));
        std::string &functionName = name->m_Identifier;
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

        if(type == nullptr)
        {
            functionType = "void";
        }else
        {
            functionType = type->m_Identifier;
        }

        auto* headers = dynamic_cast<ASTheaders*>(node->jjtGetChild(4)); // headers
        std::unordered_set<std::string> parameters = buildSignature(headers);
        std::string signatureParameter = CommonVisitorFunction::getParametersType(headers);

        if(!parameters.empty())
        {
            functionIdent += signatureParameter;
        }

        auto parent = classMap.find(it->second.parent);
        if(parent != classMap.end())
        {
            if (parent->second.nativeMethods.count(functionIdent))
            {
                errors.push_back("you can't override a native method");
                return;
            }
        }

        it->second.addFunction(functionType, functionIdent, parameters, keywords, true, this);
        node->index = it->second.nativeMethods.size() - 1;
        name->m_MethodIdentifier = functionIdent;
    }

    void TypeCheckerVisitor::visit(ASTidentFuncs *node, void * data)
    {
        // delete
    }
    void TypeCheckerVisitor::visit(ASTpommeStatic *node, void * data)
    {
        // delete
    }
    void TypeCheckerVisitor::visit(ASTsnil *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommePublic *node, void * data)
    {
        static_cast<std::unordered_set<std::string>*>(data)->insert("public");
    }
    void TypeCheckerVisitor::visit(ASTpommePrivate *node, void * data)
    {
        static_cast<std::unordered_set<std::string>*>(data)->insert("private");
    }
    void TypeCheckerVisitor::visit(ASTpommeProtected *node, void * data)
    {
        static_cast<std::unordered_set<std::string>*>(data)->insert("protected");
    }
    void TypeCheckerVisitor::visit(ASTvinil *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeOverride *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTonil *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeEnum *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeExtendsEnum *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeModdedEnum *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTdeclenums *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTennil *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTenumassign *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTenumdefault *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeGlobalFunction *node, void * data)
    {
        ASTident* functionIdentNode = dynamic_cast<ASTident*>(node->jjtGetChild(1));
        std::string functionName = functionIdentNode->m_Identifier;
        auto* headers = dynamic_cast<ASTheaders*>(node->jjtGetChild(2));
        std::string signatureParameter = CommonVisitorFunction::getParametersType(headers);
        std::unordered_set<std::string> parameters = buildSignature(headers);

        std::string functionIdent = functionName + NAME_FUNC_SEPARATOR;
        if (!parameters.empty())
        {
            functionIdent += signatureParameter;
        }

        std::cout << "parameters ___________________________" << std::endl;
        for(const auto& it : parameters)
        {
            std::cout << it << std::endl;
        }

        functionIdentNode->m_MethodIdentifier = functionIdent;

        auto* typeIdentNode = dynamic_cast<ASTident*>(node->jjtGetChild(0));
        addGlobalFunction ( (
                                (typeIdentNode != nullptr) ? 
                                typeIdentNode->m_Identifier //get return type
                                : "void"
                            ),
                            functionName,
                            functionIdent,
                            parameters
                        );

        //Define local headers
        node->jjtChildAccept(2, this, data);

        node->jjtChildAccept(3, this, data);
    }
    void TypeCheckerVisitor::visit(ASTpommeGlobalFunctionNative *node, void * data)
    {
        ASTident* functionIdentNode = dynamic_cast<ASTident*>(node->jjtGetChild(1));
        std::string functionName = functionIdentNode->m_Identifier;
        auto* headers = dynamic_cast<ASTheaders*>(node->jjtGetChild(2));
        std::string signatureParameter = CommonVisitorFunction::getParametersType(headers);
        std::unordered_set<std::string> parameters = buildSignature(headers);
        
        std::string functionIdent = functionName + NAME_FUNC_SEPARATOR;
        if (!parameters.empty())
        {
            functionIdent += signatureParameter;
        }

        std::cout << "parameters ___________________________" << std::endl;
        for(const auto& it : parameters)
        {
            std::cout << it << std::endl;
        }

        auto* typeIdentNode = dynamic_cast<ASTident*>(node->jjtGetChild(0));
        addGlobalFunction ( (
                                (typeIdentNode != nullptr) ? 
                                typeIdentNode->m_Identifier //get return type
                                : "void"
                            ),
                            functionName,
                            functionIdent,
                            parameters
                        );

        functionIdentNode->m_MethodIdentifier = functionIdent;
    }
    void TypeCheckerVisitor::visit(ASTinstrs *node, void * data)
    {
        /*if(path_number != 2){
            return;  todo
        }*/
        instrs_context = true;
        node->jjtChildrenAccept(this,data);
        instrs_context = false;
    }
    void TypeCheckerVisitor::visit(ASTinil *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTincrementPre *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTdecrementPre *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeReturn *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeWhile *node, void * data)
    {
        current_scopes++;

        current_scopes--;
    }
    void TypeCheckerVisitor::visit(ASTpommeBreak *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeIf *node, void * data)
    {
        current_scopes++;

        current_scopes--;
    }
    void TypeCheckerVisitor::visit(ASTpommePrint *node, void * data)
    {
        node->jjtChildrenAccept(this, nullptr);
    }
    void TypeCheckerVisitor::visit(ASTpommeSwitch *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTassignement *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(ASTaddeq *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTminuseq *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTdiveq *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTmulteq *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASToreq *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTandeq *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTshiftleq *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTshiftreq *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTincrementPost *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTdecrementPost *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeCases *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeDefault *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTswinil *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeCase *node, void * data)
    {
        current_scopes++;

        current_scopes--;
    }
    void TypeCheckerVisitor::visit(ASTlistexp *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTexnil *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeConstant *node, void * data)
    {
        visiteVariable(node, true, {});
    }
    void TypeCheckerVisitor::visit(ASTomega *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTheaders *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(ASTenil *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTheader *node, void * data)
    {
        std::string &localType = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
        std::string &localName = dynamic_cast<ASTident*>(node->jjtGetChild(1))->m_Identifier;

        auto it = locals.find(current_scopes);
        if(it == locals.end())
        {
            std::vector<VariableClass> locals_current_scopes;
            locals_current_scopes.emplace_back(localType, localName, -1 ,false); // todo const in header
            locals.emplace(current_scopes, std::move(locals_current_scopes));
        }else
        {
            it->second.emplace_back(localType, localName, -1 ,false);
        }
    }
    void TypeCheckerVisitor::visit(ASTvoidType *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeConstructor *node, void * data)
    {
        std::string functionType = "void";
        auto* name = dynamic_cast<ASTident*>(node->jjtGetChild(0));
        std::string &functionName = name->m_Identifier;
        std::string functionIdent = functionName + NAME_FUNC_SEPARATOR;
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

        auto* headers = dynamic_cast<ASTheaders*>(node->jjtGetChild(1)); // headers
        std::unordered_set<std::string> parameters = buildSignature(headers);
        std::string signatureParameter = CommonVisitorFunction::getParametersType(headers);

        if(!parameters.empty())
        {
            functionIdent += signatureParameter;
        }
        it->second.addFunction(functionType, functionIdent, parameters, {}, false, this);
        node->index = it->second.methods.size() - 1;
        name->m_MethodIdentifier = functionIdent;

        node->jjtGetChild(1)->jjtAccept(this, data); // headers
        node->jjtGetChild(2)->jjtAccept(this, data); // instrs
    }
    void TypeCheckerVisitor::visit(ASTpommeDestructor *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeAnd *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeOr *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeEQ *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeNEQ *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeGT *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeGET *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeLT *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeLET *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeAdd *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeMinus *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeShiftR *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeShiftL *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeMult *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeDiv *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeModulo *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeUnary *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeNot *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeTilde *node, void * data)
    {
    }

    void TypeCheckerVisitor::visit(ASTpommeNew *node, void * data)
    {
        const std::string& name = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;

        auto it = classMap.find(name);

        if (it == classMap.end())
        {
            errors.push_back("Can't find class name : " + name);
            return;
        }

        std::string functionIdent = name + NAME_FUNC_SEPARATOR;

        auto *functionParameters = dynamic_cast<ASTlistexp*>(node->jjtGetChild(1));
        std::string typeExp = getExpTypes(functionParameters);

        if(!typeExp.empty())
        {
            functionIdent += typeExp;
        }

        auto ot = it->second.methods.find(functionIdent);

        if (ot == it->second.methods.end())
        {
            node->foundConstructor = false;
            return;
        }

        node->foundConstructor = true;
        node->index = ot->second.index;
    }

    void TypeCheckerVisitor::visit(ASTpommeTrue *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeFalse *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTpommeNull *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTlistacces *node, void * data)
    {
        // acccess
        std::string className = "";
        node->jjtChildAccept(0, this, &className);

        // access
        node->jjtChildAccept(1, this, &className);

        //acccesP
        node->jjtChildAccept(2, this,  &className);
    }
    void TypeCheckerVisitor::visit(ASTlistaccesP *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(ASTacnil *node, void * data)
    {
    }
    void TypeCheckerVisitor::visit(ASTaccessMethode *node, void * data)
    {
        auto* variableType = static_cast<std::string*>(data);

        auto *identNode = dynamic_cast<ASTident*>(node->jjtGetChild(0));
        std::string functionName = identNode->m_Identifier;
        std::string functionIdent = functionName + NAME_FUNC_SEPARATOR;

        auto *functionParameters = dynamic_cast<ASTlistexp*>(node->jjtGetChild(1));
        std::string typeExp = getExpTypes(functionParameters);

        if(!typeExp.empty())
        {
            functionIdent += typeExp;
        }

        std::cout << "functionIdent : " << functionIdent << " variableType : " << variableType << " class_context : " << class_context << std::endl;

        //std::cout << "class_name_caller : " << class_name_caller << " " << ((class_name_caller != nullptr) ? *class_name_caller : "") << std::endl;

        node->name = functionIdent;

        if(variableType != nullptr && *variableType != "")
        {
            auto it = classMap.find(*variableType);
            if (it != classMap.end())
            {
                auto ot = it->second.methods.find(functionIdent);
                if (ot != it->second.methods.end())
                {
                    node->global = false;
                    node->index = ot->second.index;
                    *variableType = class_name;
                    std::cout << " INDEX  == " << node->index << std::endl;
                }
                else
                {
                    auto pt = it->second.nativeMethods.find(functionIdent);
                    if (pt != it->second.nativeMethods.end())
                    {
                        node->index = pt->second.index;
                        node->native = true;
                        *variableType = class_name;
                        std::cout << " NATIVE INDEX  == " << node->index << std::endl;
                    }
                    else
                    {
                        errors.push_back("No function " + functionName + " implemented in class " + *variableType);
                        return;
                    }
                }
            }
        }
        else if(class_context)
        {
            auto it = classMap.find(class_name);
            if (it != classMap.end())
            {
                auto ot = it->second.methods.find(functionIdent);
                if (ot != it->second.methods.end())
                {
                    node->global = false;
                    node->index = ot->second.index;
                    node->methodCall = true;
                    if( variableType != nullptr)
                    {
                        *variableType = class_name;
                    }
                    std::cout << " INDEX  == " << node->index << std::endl;
                }
                else
                {
                    auto pt = it->second.nativeMethods.find(functionIdent);
                    if (pt != it->second.nativeMethods.end())
                    {
                        node->index = pt->second.index;
                        node->native = true;
                        node->methodCall = true;
                        if( variableType != nullptr)
                        {
                            *variableType = class_name;
                        }
                        std::cout << " NATIVE INDEX  == " << node->index << std::endl;
                    }
                    else
                    {
                        std::cout << "global scope 1 ?" << std::endl;
                        auto ut = globalFunctionsMap.find(functionIdent);
                        if (ut == globalFunctionsMap.end())
                        {
                            errors.push_back("No function " + functionName + " implemented in file ");
                            return;
                        }

                        node->global = true;
                        if( variableType != nullptr)
                        {
                            *variableType = ut->second.returnType;
                        }
                    }
                }
            }
        }
        else // global scope
        {
            std::cout << "global scope 2 ?" << std::endl;

            auto ut = globalFunctionsMap.find(functionIdent);
            if( ut == globalFunctionsMap.end())
            {
                errors.push_back("No global function " + functionName + " implemented in file ");
                return;
            }

            node->global = true;
        }
    }
}