#pragma once

#include "PommeLexerVisitor.h"
#include "VM/Chunk.h"
#include "VM/Object.h"
#include "VM/Common.h"
#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <set>

namespace Pomme
{
	class VirtualMachine;

	class TypeCheckerVisitor : public PommeLexerVisitor
	{

    public:
        class FunctionClass
        {
        public:

            FunctionClass(std::string returnType, std::string functionName, std::set<std::string> parameters)
            : returnType(std::move(returnType)),
            functionName(std::move(functionName)),
            parameters(std::move(parameters))
            {
            }

            std::string returnType;
            std::string functionName;
            std::set<std::string> parameters;
            std::map<std::string, std::string> variables;

            friend std::ostream & operator<<(std::ostream & str, const FunctionClass & klass){

                str << klass.returnType << " " << klass.functionName << "(";
                for(const auto& it : klass.parameters)
                {
                    str << it << ",";
                }
                str << "\b \b"; // remove last ,
                str << ");";
                return str;
            }
        };

        class ClassClass
        {
           std::map<std::string, std::string> attributes;
           std::map<std::string, FunctionClass> functions;

            public:
            friend std::ostream & operator<<(std::ostream & str, const ClassClass & klass){
                for(const auto& it : klass.attributes)
                {
                    str << "\t" << it.first << " " << it.second << std::endl;
                }
                for(const auto& it : klass.functions)
                {
                    str << "\t" << it.first << " " << it.second << std::endl;
                }
                return str;
            }
            void addAttribute(const std::string& attributeType, const std::string& attributeName, TypeCheckerVisitor* typeCheckerVisitor);
            void addFunction(const std::string& functionType, const std::string& functionName, std::set<std::string> parameters, TypeCheckerVisitor* typeCheckerVisitor);

        };

	public:
        TypeCheckerVisitor();
        std::map<std::string, FunctionClass> globalFunctionsMap;
        std::map<std::string, ClassClass> classMap;
        std::vector<std::string> errors;

        bool class_context;
        int path_number = 0;

        void addGlobalFunction(const std::string& functionType, const std::string& functionName, std::set<std::string> parameters);
        void addClass(const std::string& className);
        std::set<std::string> buildSignature(ASTheaders *headers);

    public:
        // Inherited via TestLexerVisitor
        void visit(const SimpleNode *node, void * data);
        void visit(const ASTinput *node, void * data);
        void visit(const ASTident *node, void * data);
        void visit(const ASTidentOp *node, void * data);
        void visit(const ASTpommeInt *node, void * data);
        void visit(const ASTpommeFloat *node, void * data);
        void visit(const ASTpommeString *node, void * data);
        void visit(const ASTscopes *node, void * data);
        void visit(const ASTscinil *node, void * data);
        void visit(const ASTpommeTypeDef *node, void * data);
        void visit(const ASTpommeClass *node, void * data);
        void visit(const ASTpommeClassChild *node, void * data);
        void visit(const ASTpommeModdedClass *node, void * data);
        void visit(const ASTdecls *node, void * data);
        void visit(const ASTdnil *node, void * data);
        void visit(const ASTpommeMethode *node, void * data);
        void visit(const ASTpommeMethodeNative *node, void * data);
        void visit(const ASTidentFuncs *node, void * data);
        void visit(const ASTpommeStatic *node, void * data);
        void visit(const ASTsnil *node, void * data);
        void visit(const ASTpommePublic *node, void * data);
        void visit(const ASTpommePrivate *node, void * data);
        void visit(const ASTpommeProtected *node, void * data);
        void visit(const ASTvinil *node, void * data);
        void visit(const ASTpommeOverride *node, void * data);
        void visit(const ASTonil *node, void * data);
        void visit(const ASTpommeEnum *node, void * data);
        void visit(const ASTpommeExtendsEnum *node, void * data);
        void visit(const ASTpommeModdedEnum *node, void * data);
        void visit(const ASTdeclenums *node, void * data);
        void visit(const ASTennil *node, void * data);
        void visit(const ASTenumassign *node, void * data);
        void visit(const ASTenumdefault *node, void * data);
        void visit(const ASTpommeGlobalFunction *node, void * data);
        void visit(const ASTpommeGlobalFunctionNative *node, void * data);
        void visit(const ASTinstrs *node, void * data);
        void visit(const ASTinil *node, void * data);
        void visit(const ASTincrementPre *node, void * data);
        void visit(const ASTdecrementPre *node, void * data);
        void visit(const ASTpommeReturn *node, void * data);
        void visit(const ASTpommeWhile *node, void * data);
        void visit(const ASTpommeBreak *node, void * data);
        void visit(const ASTpommeIf *node, void * data);
        void visit(const ASTpommePrint *node, void * data);
        void visit(const ASTpommeSwitch *node, void * data);
        void visit(const ASTassignement *node, void * data);
        void visit(const ASTaddeq *node, void * data);
        void visit(const ASTminuseq *node, void * data);
        void visit(const ASTdiveq *node, void * data);
        void visit(const ASTmulteq *node, void * data);
        void visit(const ASToreq *node, void * data);
        void visit(const ASTandeq *node, void * data);
        void visit(const ASTshiftleq *node, void * data);
        void visit(const ASTshiftreq *node, void * data);
        void visit(const ASTincrementPost *node, void * data);
        void visit(const ASTdecrementPost *node, void * data);
        void visit(const ASTpommeCases *node, void * data);
        void visit(const ASTpommeDefault *node, void * data);
        void visit(const ASTswinil *node, void * data);
        void visit(const ASTpommeCase *node, void * data);
        void visit(const ASTlistexp *node, void * data);
        void visit(const ASTexnil *node, void * data);
        void visit(const ASTpommeVariable *node, void * data);
        void visit(const ASTpommeConstant *node, void * data);
        void visit(const ASTpommeArray *node, void * data);
        void visit(const ASTomega *node, void * data);
        void visit(const ASTheaders *node, void * data);
        void visit(const ASTenil *node, void * data);
        void visit(const ASTheader *node, void * data);
        void visit(const ASTvoidType *node, void * data);
        void visit(const ASTpommeDestructor *node, void * data);
        void visit(const ASTpommeAnd *node, void * data);
        void visit(const ASTpommeOr *node, void * data);
        void visit(const ASTpommeEQ *node, void * data);
        void visit(const ASTpommeNEQ *node, void * data);
        void visit(const ASTpommeGT *node, void * data);
        void visit(const ASTpommeGET *node, void * data);
        void visit(const ASTpommeLT *node, void * data);
        void visit(const ASTpommeLET *node, void * data);
        void visit(const ASTpommeAdd *node, void * data);
        void visit(const ASTpommeMinus *node, void * data);
        void visit(const ASTpommeShiftR *node, void * data);
        void visit(const ASTpommeShiftL *node, void * data);
        void visit(const ASTpommeMult *node, void * data);
        void visit(const ASTpommeDiv *node, void * data);
        void visit(const ASTpommeModulo *node, void * data);
        void visit(const ASTpommeUnary *node, void * data);
        void visit(const ASTpommeNot *node, void * data);
        void visit(const ASTpommeTilde *node, void * data);
        void visit(const ASTpommeNew *node, void * data);
        void visit(const ASTpommeTrue *node, void * data);
        void visit(const ASTpommeFalse *node, void * data);
        void visit(const ASTpommeNull *node, void * data);
        void visit(const ASTlistacces *node, void * data);
        void visit(const ASTacnil *node, void * data);
        void visit(const ASTaccessTab *node, void * data);
        void visit(const ASTaccessMethode *node, void * data);

	};
}