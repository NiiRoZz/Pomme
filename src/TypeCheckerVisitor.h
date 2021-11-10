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
#include <unordered_set>

namespace Pomme
{
	class VirtualMachine;

	class TypeCheckerVisitor : public PommeLexerVisitor
	{

    public:
        class FunctionClass
        {
        public:

            FunctionClass(std::string  returnType, std::string  functionName,std::string  functionIdent,
                          std::unordered_set<std::string>  parameters, std::unordered_set<std::string>  keywords)
            : returnType(std::move(returnType)),
            functionName(std::move(functionName)),
            functionIdent(std::move(functionIdent)),
            parameters(std::move(parameters)),
            keywords(std::move(keywords))
            {
            }

            std::string returnType;
            std::string functionName;
            std::string functionIdent;
            std::unordered_set<std::string> parameters;
            std::unordered_set<std::string> keywords;
            std::map<std::string, std::string> variables;

            friend std::ostream & operator<<(std::ostream & str, const FunctionClass & klass)
            {
                str << klass.returnType << " " << klass.functionName << "(";
                for(const auto& it : klass.parameters)
                {
                    str << it << ",";
                }
                if(!klass.parameters.empty())
                {
                    str << "\b \b"; // remove last ,
                }
                str << ");";
                return str;
            }
        };

        class VariableClass
        {
        public:
            VariableClass(std::string  variableType, std::string  variableName, bool isConst)
            : isConst(isConst),
            variableName(std::move(variableName)),
            variableType(std::move(variableType))
            {
            }

            bool isConst;
            std::string variableName;
            std::string variableType;

            friend std::ostream & operator<<(std::ostream & str, const VariableClass & klass)
            {
                if(klass.isConst)
                {
                    str << "const ";
                }
                str <<  klass.variableType << " "<< klass.variableName << std::endl;

                return str;
            }
        };
        class ClassClass
        {
            public:
            std::map<std::string, VariableClass> attributes;
            std::map<std::string, FunctionClass> functions;

            friend std::ostream & operator<<(std::ostream & str, const ClassClass & klass)
            {
                for(const auto& it : klass.attributes)
                {
                    str << "\t" << it.second << std::endl;
                }
                for(const auto& it : klass.functions)
                {
                    str << "\t";
                    for(const auto& keyword : it.second.keywords)
                    {
                        str << keyword << " ";
                    }
                    str << it.second << std::endl;
                }
                return str;
            }
            void addAttribute(std::string &attributeType, std::string attributeName, bool isConst,
                              TypeCheckerVisitor *typeCheckerVisitor);
            void addFunction(std::string& functionType, std::string& functionName, std::unordered_set<std::string> parameters, std::unordered_set<std::string> keywords, TypeCheckerVisitor* typeCheckerVisitor);

        };

	public:
        TypeCheckerVisitor();
        std::map<std::string, FunctionClass> globalFunctionsMap;
        std::map<std::string, ClassClass> classMap;
        std::vector<std::string> errors;

        bool class_context{};
        int path_number = 0;

        void VisiteVariable(Node * node, void* data, bool isConst);
        void addGlobalFunction(const std::string &functionType, const std::string &functionName, std::string functionIdent,
                               std::unordered_set<std::string> parameters);
        void addClass(const std::string& className);
        std::unordered_set<std::string> buildSignature(ASTheaders *headers);
        std::unordered_set<std::string> buildKeyword(ASTidentFuncs *node);

        friend std::ostream & operator<<(std::ostream & str, const TypeCheckerVisitor & klass)
        {
            str << "------------------------" << std::endl;
            str << "----------END----------" << std::endl;
            str << "------------------------" << std::endl;

            str << "--------GLOBAL-----------" << std::endl;
            for(const auto& it : klass.globalFunctionsMap)
            {
                str << "global function "<< it.second << std::endl;
            }

            str << "--------CLASS-----------" << std::endl;
            str << "classMap :" << std::endl;
            for(const auto& it : klass.classMap)
            {
                str << "class " << it.first << "{ \n"
                          << it.second << " };\n "<< std::endl;
            }

            return str;
        }

    public:
        // Inherited via TestLexerVisitor
        void visit(SimpleNode *node, void * data);
        void visit(ASTinput *node, void * data);
        void visit(ASTident *node, void * data);
        void visit(ASTidentOp *node, void * data);
        void visit(ASTpommeInt *node, void * data);
        void visit(ASTpommeFloat *node, void * data);
        void visit(ASTpommeString *node, void * data);
        void visit(ASTscopes *node, void * data);
        void visit(ASTscinil *node, void * data);
        void visit(ASTpommeTypeDef *node, void * data);
        void visit(ASTpommeClass *node, void * data);
        void visit(ASTpommeClassChild *node, void * data);
        void visit(ASTpommeModdedClass *node, void * data);
        void visit(ASTdecls *node, void * data);
        void visit(ASTdnil *node, void * data);
        void visit(ASTpommeMethode *node, void * data);
        void visit(ASTpommeMethodeNative *node, void * data);
        void visit(ASTidentFuncs *node, void * data);
        void visit(ASTpommeStatic *node, void * data);
        void visit(ASTsnil *node, void * data);
        void visit(ASTpommePublic *node, void * data);
        void visit(ASTpommePrivate *node, void * data);
        void visit(ASTpommeProtected *node, void * data);
        void visit(ASTvinil *node, void * data);
        void visit(ASTpommeOverride *node, void * data);
        void visit(ASTonil *node, void * data);
        void visit(ASTpommeEnum *node, void * data);
        void visit(ASTpommeExtendsEnum *node, void * data);
        void visit(ASTpommeModdedEnum *node, void * data);
        void visit(ASTdeclenums *node, void * data);
        void visit(ASTennil *node, void * data);
        void visit(ASTenumassign *node, void * data);
        void visit(ASTenumdefault *node, void * data);
        void visit(ASTpommeGlobalFunction *node, void * data);
        void visit(ASTpommeGlobalFunctionNative *node, void * data);
        void visit(ASTinstrs *node, void * data);
        void visit(ASTinil *node, void * data);
        void visit(ASTincrementPre *node, void * data);
        void visit(ASTdecrementPre *node, void * data);
        void visit(ASTpommeReturn *node, void * data);
        void visit(ASTpommeWhile *node, void * data);
        void visit(ASTpommeBreak *node, void * data);
        void visit(ASTpommeIf *node, void * data);
        void visit(ASTpommePrint *node, void * data);
        void visit(ASTpommeSwitch *node, void * data);
        void visit(ASTassignement *node, void * data);
        void visit(ASTaddeq *node, void * data);
        void visit(ASTminuseq *node, void * data);
        void visit(ASTdiveq *node, void * data);
        void visit(ASTmulteq *node, void * data);
        void visit(ASToreq *node, void * data);
        void visit(ASTandeq *node, void * data);
        void visit(ASTshiftleq *node, void * data);
        void visit(ASTshiftreq *node, void * data);
        void visit(ASTincrementPost *node, void * data);
        void visit(ASTdecrementPost *node, void * data);
        void visit(ASTpommeCases *node, void * data);
        void visit(ASTpommeDefault *node, void * data);
        void visit(ASTswinil *node, void * data);
        void visit(ASTpommeCase *node, void * data);
        void visit(ASTlistexp *node, void * data);
        void visit(ASTexnil *node, void * data);
        void visit(ASTpommeVariable *node, void * data);
        void visit(ASTpommeConstant *node, void * data);
        void visit(ASTomega *node, void * data);
        void visit(ASTheaders *node, void * data);
        void visit(ASTenil *node, void * data);
        void visit(ASTheader *node, void * data);
        void visit(ASTvoidType *node, void * data);
        void visit(ASTpommeDestructor *node, void * data);
        void visit(ASTpommeAnd *node, void * data);
        void visit(ASTpommeOr *node, void * data);
        void visit(ASTpommeEQ *node, void * data);
        void visit(ASTpommeNEQ *node, void * data);
        void visit(ASTpommeGT *node, void * data);
        void visit(ASTpommeGET *node, void * data);
        void visit(ASTpommeLT *node, void * data);
        void visit(ASTpommeLET *node, void * data);
        void visit(ASTpommeAdd *node, void * data);
        void visit(ASTpommeMinus *node, void * data);
        void visit(ASTpommeShiftR *node, void * data);
        void visit(ASTpommeShiftL *node, void * data);
        void visit(ASTpommeMult *node, void * data);
        void visit(ASTpommeDiv *node, void * data);
        void visit(ASTpommeModulo *node, void * data);
        void visit(ASTpommeUnary *node, void * data);
        void visit(ASTpommeNot *node, void * data);
        void visit(ASTpommeTilde *node, void * data);
        void visit(ASTpommeNew *node, void * data);
        void visit(ASTpommeTrue *node, void * data);
        void visit(ASTpommeFalse *node, void * data);
        void visit(ASTpommeNull *node, void * data);
        void visit(ASTlistacces *node, void * data);
        void visit(ASTacnil *node, void * data);
        void visit(ASTaccessMethode *node, void * data);

	};
}