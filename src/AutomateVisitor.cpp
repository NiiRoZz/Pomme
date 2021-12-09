#include "AutomateVisitor.h"


namespace Pomme
{

    bool AutomateVisitor::resolved(Node* node, bool isClass)
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
                    if(isClass)
                    {
                        addState(node);
                    }else
                    {
                        addEnum(node);
                    }

                    int stateNumber = dependanceGraph.getState(it.first);
                    toDelete.push_back(dynamic_cast<ASTident*>(dependanceGraph.getState(stateNumber)->node->jjtGetChild(0))->m_Identifier);
                    dependanceGraph.addTransition(nbState - 1, stateNumber);
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

    void AutomateVisitor::findDependingObject(Node* node)
    {
        std::string dependingClassName = dynamic_cast<ASTident*>(node->jjtGetChild(1))->m_Identifier; // extends
        int dependingStateNumber = dependanceGraph.getState(dependingClassName);
        std::cout << "dependingStateNumber ? " << dependingStateNumber << std::endl;
        if(dependingStateNumber != -1)
        {
            dependanceGraph.addTransition(dependingStateNumber, nbState);
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
                    std::string dependingClassName = dynamic_cast<ASTident*>(nTypeModded->jjtGetChild(0))->m_Identifier; // extends
                    int dependingStateNumber = dependanceGraph.getState(dependingClassName);
                    std::cout << "dependingStateNumber ? " << dependingStateNumber << std::endl;
                    if(dependingStateNumber != -1)
                    {
                        dependanceGraph.addTransition(dependingStateNumber, nbState);
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
                } else
                {
                    state->extend = true;
                    findDependingObject(node);
                }
            }
        }
        nbState++;
    }
    void AutomateVisitor::addEnum(Node* node)
    {
        dependanceGraph.addState(nbState);
        State* state = dependanceGraph.getState(nbState);
        std::string currentEnumName = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
        std::cout << "currentEnumName------- ? " << currentEnumName << std::endl;
        if(state != nullptr)
        {
            std::cout << "!nullptr" << std::endl;
            state->node = node;
            auto nType = dynamic_cast<ASTpommeEnum*>(node);
            if(nType == nullptr)
            {
                std::cout << "!nType" << std::endl;
                auto nTypeModded = dynamic_cast<ASTpommeModdedEnum*>(node);
                if(nTypeModded != nullptr)
                {
                    std::cout << "nTypeModded" << std::endl;
                    state->modded = true;
                } else
                {
                    std::cout << "nTypeExtends" << std::endl;
                    state->extend = true;
                    findDependingObject(node);
                }
            }
        }
        nbState++;
    }

    void AutomateVisitor::addGlobal(Node* node)
    {
        dependanceGraph.addState(nbState);
        State* state = dependanceGraph.getState(nbState);
        if(state != nullptr)
        {
            state->node = node;
            state->global = true;
            auto returnTypeNode = dynamic_cast<ASTident*>(node->jjtGetChild(0));
            auto functionIdent = dynamic_cast<ASTident*>(node->jjtGetChild(1));
            if(returnTypeNode != nullptr)
            {
                auto headers = dynamic_cast<ASTheaders*>(node->jjtGetChild(2));
                if(headers != nullptr)
                {
                    headers->jjtAccept( this,&functionIdent->m_Identifier);
                }
            }else // void
            {
                std::cout << "void type detected " << std::endl;
            }
        }
        nbState++;
    }

    void AutomateVisitor::checkTypeDependance(Node* node)
    {
        auto type = dynamic_cast<ASTident*>(node->jjtGetChild(0));
        if(type == nullptr) // void type
        {
            std::cout << "void" << std::endl;
            return;
        }

        std::string typeIdent = type->m_Identifier;
        std::cout << " typeIdent " << typeIdent << std::endl;
        if(CommonVisitorFunction::isNativeType(typeIdent))
        {
            std::cout << "NATIVE TYPE" << std::endl;
        }else
        {
            bool depandanceNodeAlreadyDefined = false;
            int numStateDepandance = -1;

            for(int i = 0; i < nbState; i++)
            {
                State* state = dependanceGraph.getState(i);
                if(state->global)
                {
                    std::cout << "currently checking a global" <<std::endl;
                    if(dynamic_cast<ASTident*>(state->node->jjtGetChild(1))->m_Identifier == typeIdent)
                    {
                        depandanceNodeAlreadyDefined = true;
                        numStateDepandance = i;
                    }
                }else
                {
                    if(dynamic_cast<ASTident*>(state->node->jjtGetChild(0))->m_Identifier == typeIdent)
                    {
                        depandanceNodeAlreadyDefined = true;
                        numStateDepandance = i;
                    }
                }
            }
            // if already defined
            if(depandanceNodeAlreadyDefined)
            {
                std::cout << "Adding Transition between " << nbState - 1 << " -> "<<  numStateDepandance << std::endl;
                if(!dependanceGraph.hasTransition(numStateDepandance, nbState - 1))
                {
                    dependanceGraph.addTransition(numStateDepandance, nbState - 1);
                }
            }else
            {
                std::cout << "DEPENDANCE DETECTED WITH CLASS/ENUM/GLOBAL : " << typeIdent << " FOR CLASS " << currentClassName << std::endl;
                auto it = classToBeResolved.find(currentClassName);
                if(it != classToBeResolved.end())
                {
                    it->second.insert(typeIdent);
                }else
                {
                    classToBeResolved.insert(std::pair<std::string, std::unordered_set<std::string>>(currentClassName,{typeIdent}));
                }
            }
        }
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
        if(!resolved(node, true))
        {
            addState(node);
        }
        std::string ident = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
        this->currentClassName = ident;
        node->jjtChildrenAccept(this, &ident);
    }
    void AutomateVisitor::visit(ASTpommeClassChild *node, void * data)
    {
        if(!resolved(node, true))
        {
            addState(node);
        }
        std::string ident = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
        node->jjtChildrenAccept(this, &ident);
    }
    void AutomateVisitor::visit(ASTpommeModdedClass *node, void * data)
    {
        if(!resolved(node, true))
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
        std::string type = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
        std::cout << type << std::endl;


        checkTypeDependance(node);
        auto assignement = dynamic_cast<ASTomega*>(node->jjtGetChild(1));
        if(assignement == nullptr)
        {
            std::cout << " ASSIGNEMENT DETECTED " << std::endl;

            // todo if global -> dependance
            // todo if not -> check static -> if static dependance
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
        if(!resolved(node, false))
        {
            addEnum(node);
        }
        std::string ident = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
        std::cout << "ASTpommeEnum " << ident << std::endl;
        node->jjtChildrenAccept(this, &ident);
    }
    void AutomateVisitor::visit(ASTpommeExtendsEnum *node, void * data)
    {
        if(!resolved(node, false))
        {
            addEnum(node);
        }
        std::string ident = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
        std::cout << "ASTpommeExtendsEnum " << ident << std::endl;
        node->jjtChildrenAccept(this, &ident);
    }
    void AutomateVisitor::visit(ASTpommeModdedEnum *node, void * data)
    {
        if(!resolved(node, false))
        {
            addEnum(node);
        }
        std::string ident = dynamic_cast<ASTident*>(node->jjtGetChild(0))->m_Identifier;
        std::cout << "ASTpommeModdedEnum " << ident << std::endl;
        node->jjtChildrenAccept(this, &ident);
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
        this->currentClassName = dynamic_cast<ASTident*>(node->jjtGetChild(1))->m_Identifier;
        checkTypeDependance(node);
        addGlobal(node);
    }
    void AutomateVisitor::visit(ASTpommeGlobalFunctionNative *node, void * data)
    {
        // todo visit header to check dependance
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
        node->jjtChildrenAccept(this,data);
    }
    void AutomateVisitor::visit(ASTenil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTheader *node, void * data)
    {
        checkTypeDependance(node);
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