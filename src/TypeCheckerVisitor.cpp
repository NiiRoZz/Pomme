#include "TypeCheckerVisitor.h"
#include "VM/VirtualMachine.h"
#include "VM/Chunk.h"
#include "VM/Memory.h"

#include <iostream>
#include <utility>

namespace Pomme
{
    // todo header function

    TypeCheckerVisitor::TypeCheckerVisitor()
	{
	}

    void TypeCheckerVisitor::addGlobalFunction(const std::string &functionType, const std::string &functionName,
                                               std::set<std::string> parameters)
    {
        std::cout << "Adding global function " << functionName << " with type " << functionType << std::endl;
        auto access = globalFunctionsMap.find(functionName);
        if(access != globalFunctionsMap.end())
        {
            errors.push_back("global function "+functionName+" already defined");
        }else
        {
            FunctionClass function(functionType, functionName, std::move(parameters));
            globalFunctionsMap.insert(std::pair<std::string,FunctionClass>(functionName, function));
        }
    }

    void TypeCheckerVisitor::addClass(const std::string& className){

        std::cout << "Adding class " << className << std::endl;

        auto access = classMap.find(className);
        if(access != classMap.end())
        {
            errors.push_back("ERROR DETECTED while adding class "+ className +" : Class already defined");
            std::cout << "ERROR DETECTED while adding class " << className << " : Class already defined" <<  std::endl;
        }else
        {
            ClassClass classClass;
            classMap.insert(std::pair<std::string,ClassClass>(className,classClass));
            std::cout << "inserted " << className << std::endl;
        }
    }

    void TypeCheckerVisitor::ClassClass::addAttribute(const std::string& attributeType, const std::string& attributeName, TypeCheckerVisitor* typeCheckerVisitor)
    {
        std::cout << "Adding attribute " << attributeName <<  " with type " << attributeType << std::endl;
        auto access = this->attributes.find(attributeName);
        if(access == this->attributes.end())
        {
            this->attributes.insert(std::pair<std::string, std::string>(attributeName, attributeType));
            std::cout << "inserted " << attributeName <<  " with type " << attributeType << std::endl;
        }else
        {
            typeCheckerVisitor->errors.push_back(attributeName+" already defined");
            std::cout << "ERROR DETECTED while adding attribute " << attributeName << " : attribute already defined" <<  std::endl;
        }
    }

    void TypeCheckerVisitor::ClassClass::addFunction(const std::string &functionType, const std::string &functionName,
                                                     std::set<std::string> parameters,
                                                     TypeCheckerVisitor *typeCheckerVisitor) {

        std::cout << "Adding function " << functionName << " with type " << functionType << std::endl;
        auto access = this->functions.find(functionName);
        if(access == this->functions.end())
        {
            FunctionClass function(functionType, functionName, std::move(parameters));
            this->functions.insert(std::pair<std::string, FunctionClass>(functionName, function));
            std::cout << "inserted " << functionName << " with type " << functionType << std::endl;
        }else
        {
            typeCheckerVisitor->errors.push_back(functionName + " already defined");
            std::cout << "ERROR DETECTED while adding attribute " << functionName << " : attribute already defined" << std::endl;
        }

    }

    std::set<std::string> TypeCheckerVisitor::buildSignature(ASTheaders *headers) {
        std::set<std::string> parameters;
        ASTheader* header;

        std::string parameterType;
        std::string parameterName;

        std::cout << "buildSignature" << std::endl;
        while(headers != nullptr){
            header = dynamic_cast<ASTheader*>(headers->jjtGetChild(0));

            parameterType = dynamic_cast<ASTident*>(header->jjtGetChild(0))->m_Identifier;
            parameterName = dynamic_cast<ASTident*>(header->jjtGetChild(1))->m_Identifier;

            auto it = parameters.insert(parameterType.append(" ").append(parameterName));
            if(!it.second){
                errors.push_back(parameterName + " already defined");
                std::cout << "ERROR DETECTED while adding parameter " << parameterName << " : parameter already defined" << std::endl;
            }
            headers = dynamic_cast<ASTheaders*>(headers->jjtGetChild(1));
        }

        std::cout << "-------------parameters--------------" <<std::endl;
        for(auto it : parameters){
            std::cout << it << std::endl;
        }
        return parameters;
    }

    void TypeCheckerVisitor::visit(const SimpleNode *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(const ASTinput *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(const ASTident *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(const ASTidentOp *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeInt *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeFloat *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeString *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTscopes *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(const ASTscinil *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(const ASTpommeTypeDef *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeClass *node, void * data)
    {
        std::string context = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
        data = &context;
        addClass(context);
        class_context = true;
        node->jjtChildrenAccept(this, data);
        class_context = false;
    }
    void TypeCheckerVisitor::visit(const ASTpommeClassChild *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeModdedClass *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTdecls *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(const ASTpommeVariable *node, void * data)
    {
        std::string &context = *static_cast<std::string*>(data);

        for (const auto& it : classMap) {
            std::cout << it.first << std::endl;
        }

        if(class_context){
            auto it = classMap.find(context);
            if( it != classMap.end()){

                std::string &attributeType = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
                std::string &attributeName = dynamic_cast<ASTident*>(node->jjtGetChild(1))->m_Identifier;

                it->second.addAttribute(attributeType,context+"::"+attributeName,this);
            }else
            {

                std::cout << "ERRORS DETECTED : class " << context << " not defined " <<std::endl;
                errors.push_back("ERRORS DETECTED : class "+ context +" not defined ");
            }
        }else{ // methode

            // todo
        }
    }
    void TypeCheckerVisitor::visit(const ASTdnil *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(const ASTpommeMethode *node, void * data)
    {
        // node->indexMethode; //todo

        // std::string &attributeType = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier; // todo static etc
        auto* type = dynamic_cast<ASTident*>(node->jjtGetChild(1));
        std::string functionType;

        if(type == nullptr){
            functionType = "void";
        }else{
            functionType = dynamic_cast<ASTident*>(node->jjtGetChild(1))->m_Identifier;
        }

        std::string &functionIdent = dynamic_cast<ASTident*>(node->jjtGetChild(2))->m_Identifier;

        std::string &context = *static_cast<std::string*>(data);

        auto* headers = dynamic_cast<ASTheaders*>(node->jjtGetChild(3)); // headers

        std::cout <<" ? ?? ? ?? ? ?? ? ?? " << std::endl;
        if(headers != nullptr){

            std::cout <<" headers != nullptr " << std::endl;
            std::set<std::string> parameters = buildSignature(headers);

            auto it = classMap.find(context);
            if( it != classMap.end()){
                std::cout << "it != end() -----------------------------" <<std::endl;
                std::cout << it->first << " = = = = = " << it->second << std::endl;
                std::cout << functionIdent << " ? ," << functionType << std::endl;
                it->second.addFunction(functionType, functionIdent, parameters, this);
                std::cout << "it != end() 2 2 2 2  2 2 2 22 2 2 -----------------------------" <<std::endl;
            }
        }else
        {
            std::cout <<" headers ==== nullptr " << std::endl;
            std::set<std::string> emptyParameters;
            auto it = classMap.find(context);
            if( it != classMap.end()){
                it->second.addFunction(functionType, functionIdent, emptyParameters, this);
            }
        }

    }
    void TypeCheckerVisitor::visit(const ASTpommeMethodeNative *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTidentFuncs *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeStatic *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTsnil *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommePublic *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommePrivate *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeProtected *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTvinil *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeOverride *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTonil *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeEnum *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeExtendsEnum *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeModdedEnum *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTdeclenums *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTennil *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTenumassign *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTenumdefault *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeGlobalFunction *node, void * data)
    {

        std::cout << "before " <<std::endl;
        std::string functionType;
        std::string functionName = dynamic_cast<ASTident*>(node->jjtGetChild(1))->m_Identifier;

        auto* identNode = dynamic_cast<ASTvoidType *>(node->jjtGetChild(0));
        if(identNode == nullptr){

            std::cout << "not void " <<std::endl;
            functionType = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
            auto headers = dynamic_cast<ASTheaders*>(node->jjtGetChild(2));

            std::set<std::string> parameters = buildSignature(headers);

            addGlobalFunction(functionType, functionName, parameters);
        }else{
            std::cout << "void " <<std::endl;

            auto headers = dynamic_cast<ASTheaders*>(node->jjtGetChild(2));
            std::set<std::string> parameters = buildSignature(headers);

            addGlobalFunction("void", functionName,parameters);
        }

        node->jjtChildrenAccept(this, data);
    }
    void TypeCheckerVisitor::visit(const ASTpommeGlobalFunctionNative *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTinstrs *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTinil *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTincrementPre *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTdecrementPre *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeReturn *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeWhile *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeBreak *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeIf *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommePrint *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeSwitch *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTassignement *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTaddeq *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTminuseq *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTdiveq *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTmulteq *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASToreq *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTandeq *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTshiftleq *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTshiftreq *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTincrementPost *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTdecrementPost *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeCases *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeDefault *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTswinil *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeCase *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTlistexp *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTexnil *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeConstant *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeArray *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTomega *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTheaders *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTenil *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTheader *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTvoidType *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeDestructor *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeAnd *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeOr *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeEQ *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeNEQ *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeGT *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeGET *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeLT *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeLET *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeAdd *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeMinus *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeShiftR *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeShiftL *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeMult *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeDiv *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeModulo *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeUnary *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeNot *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeTilde *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeNew *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeTrue *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeFalse *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTpommeNull *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTlistacces *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTacnil *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTaccessTab *node, void * data)
    {

    }
    void TypeCheckerVisitor::visit(const ASTaccessMethode *node, void * data)
    {

    }

}