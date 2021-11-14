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

    TypeCheckerVisitor::TypeCheckerVisitor()
	{
	}

    void TypeCheckerVisitor::visiteVariable(Node * node, void* data, bool isConst)
    {
        std::string &context = *static_cast<std::string*>(data);

        for (const auto& it : classMap)
        {
            std::cout << it.first << std::endl;
        }

        if(child_context)
        {
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
                }else
                {
                    child->second.addAttribute(attributeType, context + "::" + attributeName, isConst, this);
                }
            }
        }else if(class_context)
        {
            auto it = classMap.find(context);
            if( it != classMap.end())
            {

                std::string &attributeType = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
                std::string &attributeName = dynamic_cast<ASTident*>(node->jjtGetChild(1))->m_Identifier;

                it->second.addAttribute(attributeType, context + "::" + attributeName, isConst, this);

                auto* constant = dynamic_cast<ASTpommeConstant*>(node);
                if(constant != nullptr)
                {
                    constant->index = it->second.attributes.size() - 1;
                    std::cout << " INDEX FOR VARIABLE "<< attributeName << " = " << constant->index << std::endl;
                }else
                {
                    auto* variable = dynamic_cast<ASTpommeVariable*>(node);
                    variable->index = it->second.attributes.size() -1;
                    std::cout << " INDEX FOR VARIABLE "<< attributeName << " = " << variable->index << std::endl;
                }
            }else // todo check coverage to remove this branche
            {
                std::cout << "ERRORS DETECTED : class " << context << " not defined " << std::endl;
                errors.push_back("ERRORS DETECTED : class "+ context +" not defined ");
            }
        }else
        { // methode variable
            //todo
        }
    }

    void TypeCheckerVisitor::addGlobalFunction(const std::string &functionType, const std::string &functionName, const std::string functionIdent,
                                               std::unordered_set<std::string> parameters)
    {
        std::cout << "Adding global function " << functionName << " with type " << functionType << std::endl;
        auto access = globalFunctionsMap.find(functionName);
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
                                   std::unordered_set<std::string>());
            globalFunctionsMap.insert(std::pair<std::string,FunctionClass>(functionName, function));
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
            classMap.insert(std::pair<std::string,ClassClass>(className,classClass));
            std::cout << "inserted " << className << std::endl;
        }
    }

    void TypeCheckerVisitor::ClassClass::addAttribute(std::string &attributeType, std::string attributeName,
                                                 bool isConst, TypeCheckerVisitor *typeCheckerVisitor)
    {
        std::cout << "Adding attribute " << attributeName <<  " with type " << attributeType << std::endl;
        auto access = this->attributes.find(attributeName);
        if(access == this->attributes.end())
        {
            VariableClass variable(attributeType,attributeName,isConst);
            this->attributes.insert(std::pair<std::string, VariableClass>(attributeName, variable));
            std::cout << "inserted " << attributeName <<  " with type " << attributeType << std::endl;
        }else
        {
            typeCheckerVisitor->errors.push_back(attributeName+" already defined");
            std::cout << "ERROR DETECTED while adding attribute " << attributeName << " : attribute already defined" <<  std::endl;
        }
    }

    void TypeCheckerVisitor::ClassClass::addFunction(std::string &functionType, std::string &functionName,
                                                     std::unordered_set<std::string> parameters, std::unordered_set<std::string> keywords,
                                                     TypeCheckerVisitor *typeCheckerVisitor)
    {
        std::cout << "Adding function " << functionName << " with type " << functionType << std::endl;
        auto access = this->functions.find(functionName);
        if(access == this->functions.end())
        {
            FunctionClass function(functionType, functionName, std::string(), std::move(parameters),
                                   std::move(keywords));
            this->functions.insert(std::pair<std::string, FunctionClass>(functionName, function));
                std::cout << "inserted " << functionName << " with type " << functionType << std::endl;
        }else
        {
            typeCheckerVisitor->errors.push_back(functionName + " already defined");
            std::cout << "ERROR DETECTED while adding function " << functionName << " : function already defined" << std::endl;
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

            auto it = parameters.insert(parameterName);
            if(!it.second)
            {
                errors.push_back(parameterName + " already defined");
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

    std::unordered_set<std::string> TypeCheckerVisitor::buildKeyword(ASTidentFuncs *node)
    {

        std::unordered_set<std::string> keywords;

        auto* nodeStatic = dynamic_cast<ASTpommeStatic*>(node->jjtGetChild(0));
        if(nodeStatic != nullptr)
        {
            keywords.insert("static");
        }

        node->jjtChildAccept(1, this, &keywords); // public protected or private
        if(!keywords.count("protected") && !keywords.count("public") && !keywords.count("private"))
        {
            keywords.insert("private");
        }

        auto* nodeOverride = dynamic_cast<ASTpommeOverride*>(node->jjtGetChild(2));
        if(nodeOverride != nullptr)
        {
            keywords.insert("override");
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
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(ASTidentOp *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(ASTpommeInt *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(ASTpommeFloat *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(ASTpommeString *node, void * data)
    {

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
        data = &context;
        addClass(context);
        class_context = true;
        node->jjtChildrenAccept(this, data);
        class_context = false;
    }

    void TypeCheckerVisitor::visit(ASTpommeClassChild *node, void * data)
    {
        /*if(path_number != 2){ // todo
            return;
        }*/
        std::string context = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
        std::string extendedClass = dynamic_cast<ASTident*>(node->jjtGetChild(1))->m_Identifier;
        data = &context;

        ClassClass classClass;
        classClass = classMap.find(extendedClass)->second;
        classClass.parent = extendedClass;

        if(classMap.count(context)){
            errors.push_back("ERROR DETECTED while adding class "+ context +" : Class already defined");
            std::cout << "ERROR DETECTED while adding class " << context << " : Class already defined" <<  std::endl;
        }

        classMap.insert(std::pair<std::string,ClassClass>(context, classClass));

        auto it = classMap.find(extendedClass);
        if(it != classMap.end()){
            classMap.find(context)->second.keywords.insert("extends");
        }
        if(it == classMap.end())
        {
            errors.push_back(context + " is extending a non existing class " + extendedClass);
        }
        classMap.find(context) = it;

        class_context = true;
        child_context = true;
        node->jjtChildrenAccept(this, data);
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
    void TypeCheckerVisitor::visit(ASTpommeVariable *node, void * data)
    {
        visiteVariable(node, data, false);
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
        std::string functionIdent = functionName;
        std::string &context = *static_cast<std::string*>(data);

        auto it = classMap.find(context);
        if(it == classMap.end()){
            errors.push_back("method" + functionName + "not defined in class");
        }

        // todo child_context

        if(keywords.count("override"))
        {
            if(!it->second.keywords.count("extends") && !it->second.keywords.count("modded")){
                errors.push_back("Overriding method " + functionName + " while your class don't extends/mod any other class");
            }
            auto parent = classMap.find(it->second.parent);
            if(parent != classMap.end()){
                auto function = parent->second.functions.find(functionName);
                if(function == parent->second.functions.end()){
                    errors.push_back("Overriding method " + functionName + " while your parent class don't have this method defined");
                }
            }
        }

        if(type == nullptr)
        {
            functionType = "void";
        }else
        {
            functionType = dynamic_cast<ASTident *>(node->jjtGetChild(1))->m_Identifier;
        }

        auto* headers = dynamic_cast<ASTheaders*>(node->jjtGetChild(3)); // headers
        std::unordered_set<std::string> parameters = buildSignature(headers);
        std::string signatureParameter = CommonVisitorFunction::getParametersType(headers);

        if(!parameters.empty())
        {
            functionIdent = functionName + NAME_FUNC_SEPARATOR + signatureParameter;
        }
        it->second.addFunction(functionType, functionIdent, parameters, keywords, this);
        node->index = it->second.functions.size() - 1;
        name->m_MethodIdentifier = functionIdent;

    }
    void TypeCheckerVisitor::visit(ASTpommeMethodeNative *node, void * data)
    {

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
        // delete
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
        std::string functionName = dynamic_cast<ASTident*>(node->jjtGetChild(1))->m_Identifier;
        auto* headers = dynamic_cast<ASTheaders*>(node->jjtGetChild(2));
        std::string signatureParameter = CommonVisitorFunction::getParametersType(headers);
        std::unordered_set<std::string> parameters = buildSignature(headers);
        std::string functionIdent = functionName + NAME_FUNC_SEPARATOR + signatureParameter;

        std::cout << "parameters ___________________________" << std::endl;
        for(const auto& it : parameters)
        {
            std::cout << it << std::endl;
        }

        auto* identNode = dynamic_cast<ASTvoidType*>(node->jjtGetChild(0));
        addGlobalFunction ( (
                                (identNode == nullptr) ? 
                                (dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier) //get return type
                                : "void"
                            ),
                            functionName,
                            functionIdent,
                            parameters
                        );

        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(ASTpommeGlobalFunctionNative *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(ASTinstrs *node, void * data)
    {

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

    }
    void TypeCheckerVisitor::visit(ASTpommeBreak *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(ASTpommeIf *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(ASTpommePrint *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(ASTpommeSwitch *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(ASTassignement *node, void * data)
    {

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

    }
    void TypeCheckerVisitor::visit(ASTlistexp *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(ASTexnil *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(ASTpommeConstant *node, void * data)
    {
        visiteVariable(node, data, true);
    }
    void TypeCheckerVisitor::visit(ASTomega *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(ASTheaders *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(ASTenil *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(ASTheader *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(ASTvoidType *node, void * data)
    {

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

    }
    void TypeCheckerVisitor::visit(ASTpommeProperty *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(ASTacnil *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(ASTaccessMethode *node, void * data)
    {

    }

}