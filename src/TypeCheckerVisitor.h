#pragma once

#include "PommeLexerVisitor.h"
#include "VM/Chunk.h"
#include "VM/Object.h"
#include "VM/Common.h"
#include "Compiler.h"
#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <set>
#include <unordered_set>
#include "CommonVisitorFunction.h"

#define DEBUG_LOG_TYPE_CHECKERs

namespace Pomme
{
	class VirtualMachine;

	class TypeCheckerVisitor : public PommeLexerVisitor
	{
    private:
        struct VariableType
        {
            std::string nameVar;
            bool constVar;
        };


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
                for(std::size_t index = 0; index < klass.members.size(); index++)
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
            std::unordered_map<std::string, std::string> variables; // todo value = VariableClass
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

            void addAttribute(PommeNode* node, std::string &attributeType, std::string attributeName, bool isConst, bool isStatic,
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
                        node->index = function.index;
                        methods.emplace(functionName, std::move(function));
                        std::cout << "inserted " << functionName << " with type " << functionType << std::endl;
                    }
                    else if (overriding)
                    {
                        access->second.keywords.emplace("override");
                        node->index = access->second.index;
                    }
                    else
                    {
                        typeCheckerVisitor->addError(node, "addFunction ERROR : " + functionName + " already defined");
                    }
                };

                if (isNative)
                {
                    auto access = methods.find(functionName);
                    if (access != methods.end())
                    {
                        typeCheckerVisitor->addError(node, "addFunction ERROR : " + functionName + " already defined");
                    }

                    addMethod(nativeMethods);
                }
                else
                {
                    auto access = nativeMethods.find(functionName);
                    if (access != nativeMethods.end())
                    {
                        typeCheckerVisitor->addError(node, "addFunction ERROR : " + functionName + " already defined");
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
        TypeCheckerVisitor(const std::vector<ErrorFile>& errorFiles);
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
        bool modded_context = false;

        bool instrs_context = false;
        uint8_t path_number = 0;
        int current_scopes = 0;
        bool super_call = false;
        bool firstInstrConstructor = false;

        template<typename T>
        void visitUnaryOperator(T* node, const std::string& name, VariableType* returnType)
        {
            VariableType type;
            node->jjtChildAccept(0, this, &type);

            if (type.nameVar == "")
            {
                addError(node, "Can't find variable type of the left expression");
                return;
            }

            auto it = classMap.find(type.nameVar);
            if (it == classMap.end())
            {
                addError(node, "Can't find class name : " + type.nameVar);
                return;
            }

            std::string nameFunc = name + NAME_FUNC_SEPARATOR;

            FunctionClass* functionClass = it->second.getMethod(nameFunc);
            if (functionClass == nullptr)
            {
                addError(node, "Can't find method " + nameFunc);
                return;
            }

            node->index = functionClass->index;
            node->native = functionClass->native;
            if (returnType != nullptr) returnType->nameVar = functionClass->returnType;
        }

        template<typename T>
        void visitBinaryOperator(T* node, const std::string& name, VariableType* returnType, std::array<VariableType, 2>& array)
        {
            VariableType leftType;
            node->jjtChildAccept(0, this, &leftType);

            VariableType rightType;
            node->jjtChildAccept(1, this, &rightType);

            if (leftType.nameVar == "")
            {
                addError(node, "Can't find variable type of the left expression");
                return;
            }

            if (rightType.nameVar == "")
            {
                addError(node, "Can't find variable type of the right expression");
                return;
            }

            array[0] = leftType;
            array[1] = rightType;

            auto itLeft = classMap.find(leftType.nameVar);
            if (itLeft == classMap.end())
            {
                addError(node, "Can't find class name : " + leftType.nameVar);
                return;
            }

            auto itRight = classMap.find(rightType.nameVar);
            if (itRight == classMap.end())
            {
                addError(node, "Can't find class name : " + rightType.nameVar);
                return;
            }

            std::string nameFunc = name + NAME_FUNC_SEPARATOR + rightType.nameVar + HEADER_FUNC_SEPARATOR;

            FunctionClass* functionClass = itLeft->second.getMethod(nameFunc);
            if (functionClass == nullptr)
            {
                addError(node, "Can't find method " + nameFunc);
                return;
            }

            node->index = functionClass->index;
            node->native = functionClass->native;
            if (returnType != nullptr) returnType->nameVar = functionClass->returnType;
        }

        void visiteVariable(Node * node, bool isConst, const std::unordered_set<std::string>& keywords);
        void addGlobalFunction(PommeNode* node, const std::string &functionType, const std::string &functionName, std::string functionIdent, bool native,
                               std::unordered_set<std::string> parameters);
        void addClass(PommeNode* node, const std::string& className);
        void addEnum(PommeNode* node, const std::string& EnumName);
        std::unordered_set<std::string> buildSignature(ASTPommeHeaders *headers);
        bool getMethodType(ASTPommeAccessMethode *node, VariableType* variableType, std::string& functionIdent, const std::string& className);
        bool getExpType(ASTPommeListExp* node, ASTPommeAccessMethode *accessNode, VariableType* variableType, std::string& functionIdent, std::string& current, const std::string& className);
        std::unordered_set<std::string> buildKeyword(ASTPommeIdentFuncs *node);
        void checkNewMember(PommeNode* node, std::string enumName, std::string memberName);
        std::string getVariableType(const std::string& type);
        
        template<typename T>
        void checkVariable(T* node)
        {
            const std::string &leftType = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
            std::string rightType = "";

            node->jjtChildAccept(2, this, &rightType);

            bool isNull = rightType == "null";

            if (leftType == "")
            {
                addError(node, "Can't find variable type of the left expression");
                return;
            }

            if (rightType == "" && !isNull)
            {
                addError(node, "Can't find variable type of the right expression");
                return;
            }

            if (!isNull && leftType != rightType)
            {
                addError(node, "Can't assign class " + rightType + " to class " + leftType);
                return;
            }
        }

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

        void addError(PommeNode* node, const std::string& tempErrorMessage);

    private:
        const ErrorFile* getErrorFile(std::size_t line) const;

    private:
        const std::vector<ErrorFile>& m_ErrorFiles;
        std::size_t m_Line;

    public:
        // Inherited via TestLexerVisitor
        void visit(SimpleNode *node, void * data);
        void visit(ASTPommeInput *node, void * data);
        void visit(ASTPommeIdent *node, void * data);
        void visit(ASTPommeIdentOp *node, void * data);
        void visit(ASTPommeInt *node, void * data);
        void visit(ASTPommeFloat *node, void * data);
        void visit(ASTPommeString *node, void * data);
        void visit(ASTPommeScopes *node, void * data);
        void visit(ASTPommeScinil *node, void * data);
        void visit(ASTPommeTypeDef *node, void * data);
        void visit(ASTPommeClass *node, void * data);
        void visit(ASTPommeClassChild *node, void * data);
        void visit(ASTPommeModdedClass *node, void * data);
        void visit(ASTPommeDecls *node, void * data);
        void visit(ASTPommeDnil *node, void * data);
        void visit(ASTPommeMethode *node, void * data);
        void visit(ASTPommeMethodeNative *node, void * data);
        void visit(ASTPommeIdentFuncs *node, void * data);
        void visit(ASTPommeStatic *node, void * data);
        void visit(ASTPommeSnil *node, void * data);
        void visit(ASTPommePublic *node, void * data);
        void visit(ASTPommePrivate *node, void * data);
        void visit(ASTPommeProtected *node, void * data);
        void visit(ASTPommeVinil *node, void * data);
        void visit(ASTPommeOverride *node, void * data);
        void visit(ASTPommeOnil *node, void * data);
        void visit(ASTPommeEnum *node, void * data);
        void visit(ASTPommeExtendsEnum *node, void * data);
        void visit(ASTPommeModdedEnum *node, void * data);
        void visit(ASTPommeDeclEnums *node, void * data);
        void visit(ASTPommeEnnil *node, void * data);
        void visit(ASTPommeEnumAssign *node, void * data);
        void visit(ASTPommeEnumDefault *node, void * data);
        void visit(ASTPommeGlobalFunction *node, void * data);
        void visit(ASTPommeGlobalFunctionNative *node, void * data);
        void visit(ASTPommeInstrs *node, void * data);
        void visit(ASTPommeInil *node, void * data);
        void visit(ASTPommeIncrPre *node, void * data);
        void visit(ASTPommeDecrPre *node, void * data);
        void visit(ASTPommeDelete *node, void * data);
        void visit(ASTPommeReturn *node, void * data);
        void visit(ASTPommeWhile *node, void * data);
        void visit(ASTPommeBreak *node, void * data);
        void visit(ASTPommeIf *node, void * data);
        void visit(ASTPommePrint *node, void * data);
        void visit(ASTPommeSwitch *node, void * data);
        void visit(ASTPommeAssign *node, void * data);
        void visit(ASTPommeAddEq *node, void * data);
        void visit(ASTPommeMinusEq *node, void * data);
        void visit(ASTPommeDivEq *node, void * data);
        void visit(ASTPommeMultEq *node, void * data);
        void visit(ASTPommeOrEq *node, void * data);
        void visit(ASTPommeAndEq *node, void * data);
        void visit(ASTPommeShiftLEq *node, void * data);
        void visit(ASTPommeShiftREq *node, void * data);
        void visit(ASTPommeIncrPost *node, void * data);
        void visit(ASTPommeDecrPost *node, void * data);
        void visit(ASTPommeCases *node, void * data);
        void visit(ASTPommeDefault *node, void * data);
        void visit(ASTPommeSwinil *node, void * data);
        void visit(ASTPommeCase *node, void * data);
        void visit(ASTPommeListExp *node, void * data);
        void visit(ASTPommeExnil *node, void * data);
        void visit(ASTPommeVarDecls *node, void * data);
        void visit(ASTPommeVariable *node, void * data);
        void visit(ASTPommeConstant *node, void * data);
        void visit(ASTPommeOmega *node, void * data);
        void visit(ASTPommeHeaders *node, void * data);
        void visit(ASTPommeEnil *node, void * data);
        void visit(ASTPommeConstHeader *node, void * data);
        void visit(ASTPommeHeader *node, void * data);
        void visit(ASTPommeVoidType *node, void * data);
        void visit(ASTPommeConstructor *node, void * data);
        void visit(ASTPommeDestructor *node, void * data);
        void visit(ASTPommeAnd *node, void * data);
        void visit(ASTPommeOr *node, void * data);
        void visit(ASTPommeEQ *node, void * data);
        void visit(ASTPommeNEQ *node, void * data);
        void visit(ASTPommeGT *node, void * data);
        void visit(ASTPommeGET *node, void * data);
        void visit(ASTPommeLT *node, void * data);
        void visit(ASTPommeLET *node, void * data);
        void visit(ASTPommeAdd *node, void * data);
        void visit(ASTPommeMinus *node, void * data);
        void visit(ASTPommeShiftR *node, void * data);
        void visit(ASTPommeShiftL *node, void * data);
        void visit(ASTPommeMult *node, void * data);
        void visit(ASTPommeDiv *node, void * data);
        void visit(ASTPommeModulo *node, void * data);
        void visit(ASTPommeUnary *node, void * data);
        void visit(ASTPommeNot *node, void * data);
        void visit(ASTPommeTilde *node, void * data);
        void visit(ASTPommeNew *node, void * data);
        void visit(ASTPommeTrue *node, void * data);
        void visit(ASTPommeFalse *node, void * data);
        void visit(ASTPommeNull *node, void * data);
        void visit(ASTPommeListAccess *node, void * data);
        void visit(ASTPommeListAccessP *node, void * data);
        void visit(ASTPommeAcnil *node, void * data);
        void visit(ASTPommeAccessMethode *node, void * data);
        void visit(ASTPommeAccessTab *node, void * data);
	};
}