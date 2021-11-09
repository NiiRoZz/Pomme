
#ifndef POMME_COMMONVISITORFUNCTION_H
#define POMME_COMMONVISITORFUNCTION_H


#include <string>
#include <Node.h>

class CommonVisitorFunction {
public:
    static std::string getParametersType(Pomme::Node* node);
    static std::string getTypeName(Pomme::Node* node);
};


#endif //POMME_COMMONVISITORFUNCTION_H
