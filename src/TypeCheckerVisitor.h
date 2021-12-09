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

        class EnumClass
        {
        public:
            std::string enumName;
            std::unordered_set<std::string> keywords;
            std::string parent;
            std::vector<std::string> members;

            EnumClass(std::string enumName, std::unordered_set<std::string> keywords, std::string parent)
            : enumName(enumName),
            keywords(std::move(keywords)),
            parent(parent)
            {

            }

            friend std::ostream & operator<<(std::ostream & str, const EnumClass & klass)
            {
                str << "Enum " << klass.enumName << " {" << std::endl;
                for(int index = 0; index < klass.members.size(); index++)
                {
                    str << "\t" << klass.members.at(index) << "," << std::endl;
                }
                str << "\b \b"; // remove last ,

                str << "}";
                return str;
            }
        };
        class FunctionClass
        {
        public:

            FunctionClass(std::string  returnType, std::string  functionName,std::string  functionIdent,
                          std::unordered_set<std::string>  parameters, std::unordered_set<std::string>  keywords, int index, bool native)
            : returnType(std::move(returnType)),
            functionName(std::move(functionName)),
            functionIdent(std::move(functionIdent)),
            parameters(std::move(parameters)),
            keywords(std::move(keywords)),
            index(index),
            native(native)
            {
            }

            std::string returnType;
            std::string functionName;
            std::string functionIdent;
            std::unordered_set<std::string> parameters;
            std::unordered_set<std::string> keywords;
            std::unordered_map<std::string, std::string> variables;
            uint16_t index = 0u;
            bool native = false;

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
            VariableClass(std::string  variableType, std::string variableName, int index, bool isConst)
            : isConst(isConst),
            variableName(std::move(variableName)),
            variableType(std::move(variableType)),
            index(index)
            {
            }

            bool isConst;
            std::string variableName;
            std::string variableType;
            int index;

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
            std::unordered_map<std::string, VariableClass> attributes;
            std::unordered_map<std::string, VariableClass> staticAttributes;
            std::unordered_map<std::string, FunctionClass> methods;
            std::unordered_map<std::string, FunctionClass> nativeMethods;
            std::unordered_set<std::string> keywords;
            std::string parent = "";

            FunctionClass* getMethod(const std::string& methodName);
            VariableClass* getAttribute(const std::string& attributeName);

            void addAttribute(std::string &attributeType, std::string attributeName, bool isConst, bool isStatic,
                              TypeCheckerVisitor *typeCheckerVisitor);
            template<typename T>
            void addFunction(T* node, const std::string& functionType, const std::string& functionName, std::unordered_set<std::string> parameters, std::unordered_set<std::string> keywords, bool isNative, bool overriding, TypeCheckerVisitor* typeCheckerVisitor)
            {
                auto addMethod = [&] (std::unordered_map<std::string, FunctionClass>& methods) {
                    auto access = methods.find(functionName);
                    if(access == methods.end())
                    {
                        FunctionClass function(functionType, functionName, std::string(), std::move(parameters),
                                        std::move(keywords), methods.size(), isNative);
                        methods.emplace(functionName, function);
                        std::cout << "inserted " << functionName << " with type " << functionType << std::endl;
                        node->index = function.index;
                    }
                    else if (overriding)
                    {
                        access->second.keywords.emplace("override");
                        node->index = access->second.index;
                    }
                    else
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
                        typeCheckerVisitor->errors.push_back("addFunction nativeMethods ERROR : " + functionName + " already defined");
                        std::cout << "ERROR DETECTED while adding function " << functionName << " : function already defined" << std::endl;
                    }

                    addMethod(methods);
                }
            }

            friend std::ostream & operator<<(std::ostream & str, const ClassClass & klass)
            {
                for(const auto& it : klass.staticAttributes)
                {
                    str << "\tstatic " << it.second << std::endl;
                }

                for(const auto& it : klass.attributes)
                {
                    str << "\t" << it.second << std::endl;
                }

                for(const auto& it : klass.methods)
                {
                    str << "\t";
                    for(const auto& keyword : it.second.keywords)
                    {
                        str << keyword << " ";
                    }
                    str << it.second << std::endl;
                }

                for(const auto& it : klass.nativeMethods)
                {
                    str << "\tnative ";
                    for(const auto& keyword : it.second.keywords)
                    {
                        str << keyword << " ";
                    }
                    str << it.second << std::endl;
                }
                return str;
            }
        };

	public:
        TypeCheckerVisitor();
        std::unordered_map<std::string, FunctionClass> globalFunctionsMap;
        std::unordered_map<std::string, ClassClass> classMap;
        std::unordered_map<std::string, std::string> moddedMap;
        std::unordered_map<std::string, EnumClass> enumMap;
        std::vector<std::string> errors;

        std::unordered_map<int, std::vector<VariableClass>> locals;

        bool class_context = false;
        std::string class_name;
        bool child_context = false;
        std::string parent_name;
        bool child_extend_context = false;

        bool instrs_context = false;
        uint8_t path_number = 0;
        int current_scopes = 0;
        bool super_call = false;

        template<typename T>
        void visitUnaryOperator(T* node, const std::string& name, std::string* returnType)
        {
            std::string type;
            node->jjtChildAccept(0, this, &type);

            if (type == "")
            {
                errors.push_back("Can't find variable type of left expression");
                return;
            }

            auto it = classMap.find(type);
            if (it == classMap.end())
            {
                errors.push_back("Can't find class name : " + type);
                return;
            }

            std::string nameFunc = name + NAME_FUNC_SEPARATOR;

            FunctionClass* functionClass = it->second.getMethod(nameFunc);
            if (functionClass == nullptr)
            {
                errors.push_back("Can't find method " + nameFunc);
                return;
            }

            node->index = functionClass->index;
            node->native = functionClass->native;
            if (returnType != nullptr) *returnType = functionClass->returnType;
        }

        template<typename T>
        void visitBinaryOperator(T* node, const std::string& name, std::string* returnType, std::array<std::string, 2>& array)
        {
            std::string leftType;
            node->jjtChildAccept(0, this, &leftType);

            std::string rightType;
            node->jjtChildAccept(1, this, &rightType);

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

            array[0] = leftType;
            array[1] = rightType;

            auto itLeft = classMap.find(leftType);
            if (itLeft == classMap.end())
            {
                errors.push_back("Can't find class name : " + leftType);
                return;
            }

            auto itRight = classMap.find(rightType);
            if (itRight == classMap.end())
            {
                errors.push_back("Can't find class name : " + rightType);
                return;
            }

            std::string nameFunc = name + NAME_FUNC_SEPARATOR + rightType + HEADER_FUNC_SEPARATOR;

            FunctionClass* functionClass = itLeft->second.getMethod(nameFunc);
            if (functionClass == nullptr)
            {
                errors.push_back("Can't find method " + nameFunc);
                return;
            }

            node->index = functionClass->index;
            node->native = functionClass->native;
            if (returnType != nullptr) *returnType = functionClass->returnType;
        }

        void visiteVariable(Node * node, bool isConst, const std::unordered_set<std::string>& keywords);
        void addGlobalFunction(const std::string &functionType, const std::string &functionName, std::string functionIdent, bool native,
                               std::unordered_set<std::string> parameters);
        void addClass(const std::string& className);
        void addEnum(const std::string& EnumName);
        std::unordered_set<std::string> buildSignature(ASTheaders *headers);
        bool getMethodType(ASTaccessMethode *node, std::string* variableType, std::string& functionIdent, const std::string& className);
        bool getExpType(ASTlistexp* node, ASTaccessMethode *accessNode, std::string* variableType, std::string& functionIdent, std::string& current, const std::string& className);
        std::unordered_set<std::string> buildKeyword(ASTidentFuncs *node);
        void checkNewMember(std::basic_string<char> enumName, std::basic_string<char> memberName);
        std::string getVariableType(const std::string& type);

        bool checkAccessMethod(ASTaccessMethode *node, std::string* variableType, const std::string& functionName, const std::string& functionIdent, bool addError);

        friend std::ostream & operator<<(std::ostream & str, const TypeCheckerVisitor & klass)
        {
            str << "------------------------" << std::endl;
            str << "----------END----------" << std::endl;
            str << "------------------------" << std::endl;

            str << "--------ENUM-----------" << std::endl;
            for(const auto& it : klass.enumMap)
            {
                str << "enum "<< it.second << std::endl;
            }

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
        void visit(ASTvarDecls *node, void * data);
        void visit(ASTpommeVariable *node, void * data);
        void visit(ASTpommeConstant *node, void * data);
        void visit(ASTomega *node, void * data);
        void visit(ASTheaders *node, void * data);
        void visit(ASTenil *node, void * data);
        void visit(ASTheader *node, void * data);
        void visit(ASTvoidType *node, void * data);
        void visit(ASTpommeConstructor *node, void * data);
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
        void visit(ASTlistaccess *node, void * data);
        void visit(ASTlistaccessP *node, void * data);
        void visit(ASTacnil *node, void * data);
        void visit(ASTaccessMethode *node, void * data);
        void visit(ASTaccessTab *node, void * data);
	};
}