#include "../include/OpticsMaterialFactory.h"

OpticsMaterial OpticsMaterialFactory::createOpticsMaterial(const std::string &type, double thickness, double diopter, const std::string &materialName) {
    return {type, thickness, diopter, materialName};
}