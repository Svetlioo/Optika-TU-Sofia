#include "../include/OpticsMaterial.h"
#include <stdexcept>
#include <ostream>

OpticsMaterial::OpticsMaterial(const std::string &type, double thickness, double diopter, const std::string &materialName)
    : type(type), thickness(thickness), diopter(diopter), materialName(materialName) {
    if (type.empty()) {
        throw std::invalid_argument("Type cannot be empty");
    }
    if (thickness <= 0) {
        throw std::invalid_argument("Thickness must be positive");
    }
    if (diopter < 0) {
        throw std::invalid_argument("Diopter cannot be negative");
    }
    if (materialName.empty()) {
        throw std::invalid_argument("Material name cannot be empty");
    }
}

const std::string &OpticsMaterial::getType() const {
    return type;
}

double OpticsMaterial::getThickness() const {
    return thickness;
}

double OpticsMaterial::getDiopter() const {
    return diopter;
}

const std::string &OpticsMaterial::getMaterialName() const {
    return materialName;
}

void OpticsMaterial::setType(const std::string &type) {
    if (type.empty()) {
        throw std::invalid_argument("Type cannot be empty");
    }
    this->type = type;
}

void OpticsMaterial::setThickness(double thickness) {
    if (thickness <= 0) {
        throw std::invalid_argument("Thickness must be positive");
    }
    this->thickness = thickness;
}

void OpticsMaterial::setDiopter(double diopter) {
    if (diopter < 0) {
        throw std::invalid_argument("Diopter cannot be negative");
    }
    this->diopter = diopter;
}

void OpticsMaterial::setMaterialName(const std::string &materialName) {
    if (materialName.empty()) {
        throw std::invalid_argument("Material name cannot be empty");
    }
    this->materialName = materialName;
}

std::ostream &operator<<(std::ostream &os, const OpticsMaterial &material) {
    os << "Type: " << material.type << ", Thickness: " << material.thickness
       << ", Diopter: " << material.diopter << ", Material Name: " << material.materialName;
    return os;
}