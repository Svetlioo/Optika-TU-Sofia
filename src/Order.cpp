#include "../include/Order.h"
#include <stdexcept>
#include <ostream>

Order::Order(Supplier supplier) : supplier(std::move(supplier)), totalPrice(0.0) {
}

Order::Order() : totalPrice(0.0) {
}

void Order::addMaterial(const OpticsMaterial &material, double price) {
    if (price <= 0) {
        throw std::invalid_argument("Price must be positive");
    }
    materials.push_back(material);
    totalPrice += price;
}

double Order::calculateTotalPrice() const {
    return totalPrice;
}

const Supplier &Order::getSupplier() const {
    return supplier;
}

const std::vector<OpticsMaterial> &Order::getMaterials() const {
    return materials;
}

void Order::setTotalPrice(double price) {
    totalPrice = price;
}

std::ostream &operator<<(std::ostream &os, const Order &order) {
    os << "Supplier: " << order.supplier << "\nMaterials:\n";
    for (const auto &material : order.materials) {
        os << material << "\n";
    }
    os << "Total Price: " << order.totalPrice;
    return os;
}