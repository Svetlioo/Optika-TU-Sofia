#ifndef OPTICSAPP_H
#define OPTICSAPP_H

#include <vector>
#include <string>
#include "Supplier.h"
#include "OpticsMaterial.h"
#include "Order.h"

class OpticsApp {
public:
    std::vector<Supplier> suppliers;
    std::vector<Order> orders;

    void addSupplier(const Supplier &supplier);
    void createOrder(const Supplier &supplier);
    void addMaterialToOrder(size_t orderIndex, const OpticsMaterial &material, double price);
    void saveSuppliersToFile(const std::string &filename) const;
    void saveOrdersToFile(const std::string &filename) const;
    void loadSuppliersFromFile(const std::string &filename);
    void printSuppliers() const;
    void printOrders() const;
    void interactiveMenu();
};

#endif //OPTICSAPP_H