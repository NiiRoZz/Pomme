
#ifndef POMME_COMMONVISITORFUNCTION_H
#define POMME_COMMONVISITORFUNCTION_H


#include <string>
#include <Node.h>

namespace Pomme
{
    class CommonVisitorFunction
    {
    public:
        static std::string getParametersType(Pomme::Node* node);
        static std::string getMethodeIdentFromListAccess(Pomme::Node* node);
        static std::string getTypeName(Pomme::Node* node);

        static bool isNativeType(const std::string& name);
    };
}

#endif //POMME_COMMONVISITORFUNCTION_H
