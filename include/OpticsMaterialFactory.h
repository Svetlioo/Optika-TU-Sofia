#ifndef OPTICSMATERIALFACTORY_H
#define OPTICSMATERIALFACTORY_H

#include "OpticsMaterial.h"

class OpticsMaterialFactory {
public:
    static OpticsMaterial createOpticsMaterial(const std::string &type, double thickness, double diopter, const std::string &materialName);
};

#endif //OPTICSMATERIALFACTORY_H