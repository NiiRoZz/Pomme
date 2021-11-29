#include "AutomateVisitor.h"


namespace Pomme
{

    bool AutomateVisitor::resolved(Node* node)
    {
        bool resolved = false;
        std::string ident = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
        std::vector<std::string> toDelete;
        for(const auto& it : classToBeResolved)
        {
            for(const auto& ot : it.second)
            {
                if(ot == ident)
                {
                    addState(node);
                    int stateNumber = dependanceGraph.getState(it.first);
                    toDelete.push_back(dynamic_cast<ASTident*>(dependanceGraph.getState(stateNumber)->node->jjtGetChild(0))->m_Identifier);
                    dependanceGraph.addTransition(stateNumber , nbState - 1);
                    resolved = true;
                }
            }
        }

        if(resolved)
        {
            for(const auto& it : toDelete)
            {
                auto ut = classToBeResolved.find(it);
                if(ut != classToBeResolved.end())
                {
                    ut->second.erase(ident);
                    if(ut->second.empty())
                    {
                        classToBeResolved.erase(ut);
                    }
                }
            }
        }

        return resolved;
    }

    void AutomateVisitor::addState(Node* node)
    {
        dependanceGraph.addState(nbState);
        State* state = dependanceGraph.getState(nbState);
        if(state != nullptr)
        {
            std::cout << "!nullptr" << std::endl;
            state->node = node;
            auto nType = dynamic_cast<ASTpommeClass*>(node);
            if(nType == nullptr)
            {
                std::cout << "!nType" << std::endl;
                auto nTypeModded = dynamic_cast<ASTpommeModdedClass*>(node);
                if(nTypeModded != nullptr)
                {
                    std::cout << "!nTypeModded" << std::endl;
                    state->modded = true;
                } else
                {
                    state->extend = true;

                    std::string dependingClassName = dynamic_cast<ASTident*>(node->jjtGetChild(1))->m_Identifier;
                    int dependingStateNumber = dependanceGraph.getState(dependingClassName);
                    std::cout << "dependingStateNumber ? " << dependingStateNumber << std::endl;
                    if(dependingStateNumber != -1)
                    {
                        dependanceGraph.addTransition(nbState , dependingStateNumber);
                    }else
                    {
                        std::string className = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
                        auto ut = classToBeResolved.find(className);
                        if(ut != classToBeResolved.end())
                        {
                            ut->second.insert(dependingClassName);
                        }else
                        {
                            classToBeResolved.insert(std::pair<std::string, std::unordered_set<std::string>>(className,{dependingClassName}));
                        }
                    }
                }
            }
        }else
        {
            std::cout << "ERROR STATE NULL" << std::endl;
            return;
        }
        nbState++;
    }

    void AutomateVisitor::visit(SimpleNode *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void AutomateVisitor::visit(ASTinput *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void AutomateVisitor::visit(ASTident *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTidentOp *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeInt *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeFloat *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeString *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTscopes *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void AutomateVisitor::visit(ASTscinil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeTypeDef *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeClass *node, void * data)
    {
        if(!resolved(node))
        {
            addState(node);
        }
        std::string ident = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
        node->jjtChildrenAccept(this, &ident);
    }
    void AutomateVisitor::visit(ASTpommeClassChild *node, void * data)
    {
        if(!resolved(node))
        {
            addState(node);
        }
        std::string ident = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
        node->jjtChildrenAccept(this, &ident);
    }
    void AutomateVisitor::visit(ASTpommeModdedClass *node, void * data)
    {
        if(!resolved(node))
        {
            addState(node);
        }
        std::string ident = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
        node->jjtChildrenAccept(this, &ident);
    }
    void AutomateVisitor::visit(ASTdecls *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void AutomateVisitor::visit(ASTpommeVariable *node, void * data)
    {
        std::string ident = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
        std::cout << ident << std::endl;

        if(CommonVisitorFunction::isNativeType(ident))
        {
            std::cout << "NATIVE TYPE" << std::endl;
        }else
        {
            std::string* className = static_cast<std::string*>(data);
            bool depandanceNodeAlreadyDefined = false;
            int numStateDepandance = -1;

            for(int i = 0; i < nbState; i++)
            {
                State* state = dependanceGraph.getState(i);
                if(dynamic_cast<ASTident*>(state->node->jjtGetChild(0))->m_Identifier == ident)
                {
                    depandanceNodeAlreadyDefined = true;
                    numStateDepandance = i;
                }
            }
            // if already defined
            if(depandanceNodeAlreadyDefined)
            {
                std::cout << "Adding Transition between " << nbState - 1 << " -> "<<  numStateDepandance << std::endl;
                dependanceGraph.addTransition(nbState - 1 , numStateDepandance);
            }else
            {
                std::cout << "DEPENDANCE DETECTED WITH CLASS : " << ident << " FOR CLASS " << *className << std::endl;
                auto it = classToBeResolved.find(*className);
                if(it != classToBeResolved.end())
                {
                    it->second.insert(ident);
                }else
                {
                    classToBeResolved.insert(std::pair<std::string, std::unordered_set<std::string>>(*className,{ident}));
                }
            }
        }
    }
    void AutomateVisitor::visit(ASTdnil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeMethode *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeMethodeNative *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTidentFuncs *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeStatic *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTsnil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommePublic *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommePrivate *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeProtected *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTvinil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeOverride *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTonil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeEnum *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeExtendsEnum *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeModdedEnum *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTdeclenums *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTennil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTenumassign *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTenumdefault *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeGlobalFunction *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeGlobalFunctionNative *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTinstrs *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTinil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTincrementPre *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTdecrementPre *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeReturn *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeWhile *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeBreak *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeIf *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommePrint *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeSwitch *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTassignement *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTaddeq *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTminuseq *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTdiveq *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTmulteq *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASToreq *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTandeq *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTshiftleq *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTshiftreq *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTincrementPost *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTdecrementPost *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeCases *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeDefault *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTswinil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeCase *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTlistexp *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTexnil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTomega *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTheaders *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTenil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTheader *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTvoidType *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeDestructor *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeAnd *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeOr *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeEQ *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeNEQ *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeGT *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeGET *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeLT *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeLET *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeAdd *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeMinus *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeShiftR *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeShiftL *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeMult *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeDiv *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeModulo *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeUnary *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeNot *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeTilde *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeNew *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeTrue *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeFalse *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTpommeNull *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTlistaccess *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTacnil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTaccessMethode *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTaccessTab *node, void * data)
    {
    }

    void AutomateVisitor::visit(ASTpommeConstructor *node, void *data)
    {
    }

    void AutomateVisitor::visit(ASTpommeConstant *node, void *data)
    {
    }

    void AutomateVisitor::visit(ASTvarDecls *node, void *data)
    {
        node->jjtChildrenAccept(this, data);
    }

    void AutomateVisitor::visit(ASTlistaccessP *node, void *data)
    {
    }
}