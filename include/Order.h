#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include "Supplier.h"
#include "OpticsMaterial.h"

class Order {
    Supplier supplier;
    std::vector<OpticsMaterial> materials;
    double totalPrice;

public:
    explicit Order(Supplier supplier);

    Order();

    void addMaterial(const OpticsMaterial &material, double price);

    [[nodiscard]] double calculateTotalPrice() const;
    [[nodiscard]] const Supplier &getSupplier() const;
    [[nodiscard]] const std::vector<OpticsMaterial> &getMaterials() const;

    void setTotalPrice(double price);

    friend std::ostream &operator<<(std::ostream &os, const Order &order);
};

#endif //ORDER_H