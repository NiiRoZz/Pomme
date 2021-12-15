#include "AutomateVisitor.h"


namespace Pomme
{


    void AutomateVisitor::classToResolveCheck(std::string className, std::string dependingClassName)
    {
        auto ut = classToBeResolved.find(className);
        if(ut != classToBeResolved.end())
        {
            ut->second.insert(dependingClassName);
        }else
        {
            classToBeResolved.insert(std::pair<std::string, std::unordered_set<std::string>>(className,{dependingClassName}));
        }

    }
    bool AutomateVisitor::resolved(Node* node, bool isClass)
    {
        bool resolved = false;
        std::string ident = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
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

                    std::cout << " looking for " << it.first << std::endl;
                    int stateNumber = dependanceGraph.getState(it.first);
                    auto casting = dynamic_cast<ASTPommeIdent*>(dependanceGraph.getState(stateNumber)->node->jjtGetChild(0));
                    if(casting != nullptr)
                    {
                        toDelete.push_back(casting->m_Identifier);
                    }else // globalFunction
                    {
                        toDelete.push_back(dependanceGraph.getState(stateNumber)->globalName);
                    }
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
        std::string dependingClassName = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1))->m_Identifier; // extends
        int dependingStateNumber = dependanceGraph.getState(dependingClassName);
        if(dependingStateNumber != -1)
        {
           dependanceGraph.addTransition(dependingStateNumber, nbState);
        }else
        {
            std::string className = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
            classToResolveCheck(className,dependingClassName);
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
            auto nType = dynamic_cast<ASTPommeClass*>(node);
            if(nType == nullptr)
            {
                std::cout << "!nType" << std::endl;
                auto nTypeModded = dynamic_cast<ASTPommeModdedClass*>(node);
                if(nTypeModded != nullptr)
                {
                    std::cout << "!nTypeModded" << std::endl;
                    state->modded = true;
                    std::string dependingClassName = dynamic_cast<ASTPommeIdent*>(nTypeModded->jjtGetChild(0))->m_Identifier; // extends
                    std::string className = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;

                    int dependingStateNumber = dependanceGraph.getState(dependingClassName);
                    if(dependingStateNumber != -1)
                    {
                        std::cout << "Adding transition found : " << className << " -> " << dependingClassName << std::endl;
                        dependanceGraph.addTransition(dependingStateNumber, nbState);
                    }else
                    {
                        classToResolveCheck(className,dependingClassName);
                    }
                } else
                {
                    state->extend = true;
                    findDependingObject(node);
                }
            }
        }
        nbState++;
        std::cout << "current nbState = " << nbState << std::endl;
    }

    void AutomateVisitor::addEnum(Node* node)
    {
        dependanceGraph.addState(nbState);
        State* state = dependanceGraph.getState(nbState);
        std::string currentEnumName = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
        std::cout << "currentEnumName------- ? " << currentEnumName << std::endl;
        if(state != nullptr)
        {
            std::cout << "!nullptr" << std::endl;
            state->node = node;
            auto nType = dynamic_cast<ASTPommeEnum*>(node);
            if(nType == nullptr)
            {
                std::cout << "!nType" << std::endl;
                auto nTypeModded = dynamic_cast<ASTPommeModdedEnum*>(node);
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
            auto functionIdent = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1));
            auto headers = dynamic_cast<ASTPommeHeaders*>(node->jjtGetChild(2));

            state->globalName = functionIdent->m_Identifier + NAME_FUNC_SEPARATOR;
            state->globalName += CommonVisitorFunction::getParametersType(headers);
        }

        nbState++;
    }

    void AutomateVisitor::checkGlobalDependance(Node* node)
    {
        auto type = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0));
        std::string typeIdent;
        if(type == nullptr) // void type
        {
            typeIdent = "void";
        }else
        {
            typeIdent = type->m_Identifier;
        }

        auto functionIdent = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1));
        auto headers = dynamic_cast<ASTPommeHeaders*>(node->jjtGetChild(2));

        std::string functionCompleteName = functionIdent->m_Identifier + NAME_FUNC_SEPARATOR + CommonVisitorFunction::getParametersType(headers);

        std::cout << " typeIdent " << typeIdent << std::endl;
        if(CommonVisitorFunction::isNativeType(typeIdent) || typeIdent == "void")
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
                    if(functionCompleteName == typeIdent)
                    {
                        depandanceNodeAlreadyDefined = true;
                        numStateDepandance = i;
                    }
                }else
                {
                    if(dynamic_cast<ASTPommeIdent*>(state->node->jjtGetChild(0))->m_Identifier == typeIdent)
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
                classToResolveCheck(functionCompleteName,typeIdent);
            }
        }
        checkHeaderDependance(headers, functionCompleteName);
    };

    void AutomateVisitor::checkHeaderDependance(Node* node, const std::string& functionCompleteName)
    {
        auto* currHeaders = node;
        while (currHeaders != nullptr)
        {
            auto* currHeader = dynamic_cast<Pomme::ASTPommeHeader*>(currHeaders->jjtGetChild(0));
            auto* identHeader = dynamic_cast<Pomme::ASTPommeIdent*>(currHeader->jjtGetChild(0));

            std::string currenHeaderIdent = identHeader->m_Identifier;
            std::cout << " visiting header _____ " << currenHeaderIdent << std::endl;

            if(CommonVisitorFunction::isNativeType(currenHeaderIdent))
            {
                std::cout << "NATIVE TYPE" << std::endl;
            }else
            {
                std::cout << "NOT NATIVE TYPE" << std::endl;
                bool depandanceNodeAlreadyDefined = false;
                int numStateDepandance = -1;

                for(int i = 0; i < nbState; i++)
                {
                    State* state = dependanceGraph.getState(i);
                    if(!state->global)
                    {
                        if(dynamic_cast<ASTPommeIdent*>(state->node->jjtGetChild(0))->m_Identifier == currenHeaderIdent)
                        {
                            depandanceNodeAlreadyDefined = true;
                            numStateDepandance = i;
                            break;
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
                    classToResolveCheck(functionCompleteName,currenHeaderIdent);
                }
            }
            currHeaders = dynamic_cast<Pomme::ASTPommeHeaders*>(currHeaders->jjtGetChild(1));
        }
    }

    void AutomateVisitor::checkTypeDependance(Node* node)
    {
        auto type = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0));
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
                    // todo check line
                    std::string globalName = currentClassName + NAME_FUNC_SEPARATOR + CommonVisitorFunction::getParametersType(node->jjtGetChild(1));

                    std::cout << "currently checking a global : " << globalName << std::endl;
                    if(globalName == typeIdent)
                    {
                        depandanceNodeAlreadyDefined = true;
                        numStateDepandance = i;
                    }
                }else
                {
                    if(dynamic_cast<ASTPommeIdent*>(state->node->jjtGetChild(0))->m_Identifier == typeIdent)
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
                classToResolveCheck(currentClassName,typeIdent);
            }
        }
    }

    void AutomateVisitor::visit(SimpleNode *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void AutomateVisitor::visit(ASTPommeInput *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void AutomateVisitor::visit(ASTPommeIdent *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeIdentOp *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeInt *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeFloat *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeString *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeScopes *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void AutomateVisitor::visit(ASTPommeScinil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeTypeDef *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeClass *node, void * data)
    {
        if(!resolved(node, true))
        {
            addState(node);
        }
        std::string ident = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
        this->currentClassName = ident;
        node->jjtChildrenAccept(this, &ident);
    }
    void AutomateVisitor::visit(ASTPommeClassChild *node, void * data)
    {
        if(!resolved(node, true))
        {
            addState(node);
        }
        std::string ident = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
        node->jjtChildrenAccept(this, &ident);
    }
    void AutomateVisitor::visit(ASTPommeModdedClass *node, void * data)
    {
        if(!resolved(node, true))
        {
            addState(node);
        }
        std::string ident = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
        node->jjtChildrenAccept(this, &ident);
    }
    void AutomateVisitor::visit(ASTPommeDecls *node, void * data)
    {
        node->jjtChildrenAccept(this, data);
    }
    void AutomateVisitor::visit(ASTPommeVariable *node, void * data)
    {
        std::string type = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
        std::cout << type << std::endl;

        checkTypeDependance(node); // check type of pommeVariable

        std::cout << "ASSIGNEMENT DETECTED " << std::endl;

        auto listAccess = dynamic_cast<ASTPommeListAccess*>(node->jjtGetChild(2));
        if(listAccess != nullptr)
        {
            std::cout << "LISTACESS DETECTED " << std::endl;
            node->jjtChildAccept(2, this, data);
            return;
        }

        auto accessMethode = dynamic_cast<ASTPommeAccessMethode*>(node->jjtGetChild(2));
        if(accessMethode != nullptr)
        {
            std::cout << "ACCESSMETHODE DETECTED " << std::endl; // todo get signature
            node->jjtChildAccept(2, this, data);
            return;
        }


    }
    void AutomateVisitor::visit(ASTPommeDnil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeMethode *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeMethodeNative *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeIdentFuncs *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeStatic *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeSnil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommePublic *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommePrivate *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeProtected *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeVinil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeOverride *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeOnil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeEnum *node, void * data)
    {
        if(!resolved(node, false))
        {
            addEnum(node);
        }
        std::string ident = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
        std::cout << "ASTPommeEnum " << ident << std::endl;
        node->jjtChildrenAccept(this, &ident);
    }
    void AutomateVisitor::visit(ASTPommeExtendsEnum *node, void * data)
    {
        if(!resolved(node, false))
        {
            addEnum(node);
        }
        std::string ident = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
        std::cout << "ASTPommeExtendsEnum " << ident << std::endl;
        node->jjtChildrenAccept(this, &ident);
    }
    void AutomateVisitor::visit(ASTPommeModdedEnum *node, void * data)
    {
        if(!resolved(node, false))
        {
            addEnum(node);
        }
        std::string ident = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
        std::cout << "ASTPommeModdedEnum " << ident << std::endl;
        node->jjtChildrenAccept(this, &ident);
    }
    void AutomateVisitor::visit(ASTPommeDeclEnums *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeEnnil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeEnumAssign *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeEnumDefault *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeGlobalFunction *node, void * data)
    {
        this->currentClassName = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(1))->m_Identifier;
        addGlobal(node);
        checkGlobalDependance(node);
    }
    void AutomateVisitor::visit(ASTPommeGlobalFunctionNative *node, void * data)
    {
        // todo visit header to check dependance
    }
    void AutomateVisitor::visit(ASTPommeInstrs *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeInil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeIncrPre *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeDecrPre *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeDelete *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeReturn *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeWhile *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeBreak *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeIf *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommePrint *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeSwitch *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeAssign *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeAddEq *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeMinusEq *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeDivEq *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeMultEq *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeOrEq *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeAndEq *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeShiftLEq *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeShiftREq *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeIncrPost *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeDecrPost *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeCases *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeDefault *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeSwinil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeCase *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeListExp *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeExnil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeOmega *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeHeaders *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeEnil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeConstHeader *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeHeader *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeVoidType *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeDestructor *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeAnd *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeOr *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeEQ *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeNEQ *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeGT *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeGET *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeLT *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeLET *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeAdd *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeMinus *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeShiftR *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeShiftL *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeMult *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeDiv *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeModulo *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeUnary *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeNot *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeTilde *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeNew *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeTrue *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeFalse *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeNull *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeListAccess *node, void * data)
    {
        std::string dependingClass = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
        std::cout << " ident list acess ________________________ == " << dependingClass << std::endl;
        std::cout << " current class ________________________ == " << currentClassName << std::endl;

        int stateNumber = dependanceGraph.getState(currentClassName);
        if(stateNumber != -1)
        {
            int dependingStateNumber = dependanceGraph.getState(dependingClass);
            if(dependingStateNumber != -1)
            {
                dependanceGraph.addTransition(dependingStateNumber, stateNumber);
            }else
            {
                classToResolveCheck(currentClassName,dependingClass);
            }
        }

    }
    void AutomateVisitor::visit(ASTPommeAcnil *node, void * data)
    {
    }
    void AutomateVisitor::visit(ASTPommeAccessMethode *node, void * data)
    {
        std::string dependingGlobal = dynamic_cast<ASTPommeIdent*>(node->jjtGetChild(0))->m_Identifier;
        std::cout << " DEPENDING ON GLOBAL FUNC " << dependingGlobal << std::endl;


        // construct ignature of global to dinf the rigth one
    }
    void AutomateVisitor::visit(ASTPommeAccessTab *node, void * data)
    {
    }

    void AutomateVisitor::visit(ASTPommeConstructor *node, void *data)
    {
    }

    void AutomateVisitor::visit(ASTPommeConstant *node, void *data)
    {
    }

    void AutomateVisitor::visit(ASTPommeVarDecls *node, void *data)
    {
        node->jjtChildrenAccept(this, data);
    }

    void AutomateVisitor::visit(ASTPommeListAccessP *node, void *data)
    {
    }
}