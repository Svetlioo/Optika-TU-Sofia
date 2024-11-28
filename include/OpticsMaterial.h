#ifndef OPTICSMATERIAL_H
#define OPTICSMATERIAL_H

#include <string>

class OpticsMaterial {
    std::string type;
    double thickness{};
    double diopter{};
    std::string materialName;

public:
    OpticsMaterial(const std::string &type, double thickness, double diopter, const std::string &materialName);

    OpticsMaterial() = default;

    [[nodiscard]] const std::string &getType() const;
    [[nodiscard]] double getThickness() const;
    [[nodiscard]] double getDiopter() const;
    [[nodiscard]] const std::string &getMaterialName() const;

    void setType(const std::string &type);
    void setThickness(double thickness);
    void setDiopter(double diopter);
    void setMaterialName(const std::string &materialName);

    friend std::ostream &operator<<(std::ostream &os, const OpticsMaterial &material);
};

#endif //OPTICSMATERIAL_H