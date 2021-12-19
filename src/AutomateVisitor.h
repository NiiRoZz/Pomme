#pragma once


#include "PommeLexerVisitor.h"
#include "Automate/Automaton.h"
#include "CommonVisitorFunction.h"

namespace Pomme
{
    class AutomateVisitor : public PommeLexerVisitor
    {
    public:
        Automaton dependanceGraph;
        int nbState = 0;
        std::unordered_map<std::string, std::unordered_set<std::string>> classToBeResolved;
        std::unordered_map<std::string, std::vector<Node*>> moddedClassToBeResolved;
        std::unordered_map<std::string, int> lastDefinedModdedClassStateNumber;
        std::string currentClassName;

        void classToResolveCheck(const std::string &className, const std::string& classToResolve);
        void moddedClassToResolveCheck(const std::string &className, Node* node);
        void addState(Node* node);
        void addEnum(Node* node);
        void addGlobal(Node* node);

        void checkTypeDependance(Node* node);
        void checkGlobalDependance(Node* node);
        void checkHeaderDependance(Node* node, const std::string& functionCompleteName);

        void findDependingObject(Node* node);
        bool resolved(Node* node, bool isClass);
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
