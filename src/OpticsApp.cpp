#include "../include/OpticsApp.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <unordered_set>
#include <sstream>
#include "../include/SupplierFactory.h"
#include "../include/OpticsMaterialFactory.h"
#include "../include/OrderFactory.h"

void OpticsApp::addSupplier(const Supplier &supplier) {
    suppliers.push_back(supplier);
}

void OpticsApp::createOrder(const Supplier &supplier) {
    orders.emplace_back(OrderFactory::createOrder(supplier));
}

void OpticsApp::addMaterialToOrder(size_t orderIndex, const OpticsMaterial &material, double price) {
    if (orderIndex >= orders.size()) {
        throw std::out_of_range("Invalid order index");
    }
    orders[orderIndex].addMaterial(material, price);
}

void OpticsApp::saveSuppliersToFile(const std::string &filename) const {
    std::unordered_set<std::string> existingSuppliers;
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) {
        existingSuppliers.insert(line);
    }
    infile.close();

    if (std::ofstream file(filename, std::ios::app); file.is_open()) {
        for (const auto &supplier : suppliers) {
            std::ostringstream oss;
            oss << supplier;
            if (!existingSuppliers.contains(oss.str())) {
                file << oss.str() << "\n";
            }
        }
        file.close();
    }
}

void OpticsApp::saveOrdersToFile(const std::string &filename) const {
    if (std::ofstream file(filename, std::ios::app); file.is_open()) {
        for (const auto &order : orders) {
            file << order << "\n";
        }
        file.close();
    }
}

void OpticsApp::loadSuppliersFromFile(const std::string &filename) {
    if (std::ifstream file(filename); file.is_open()) {
        suppliers.clear();
        std::string line;
        while (std::getline(file, line)) {
            try {
                if (line.find("Bulstat:") != std::string::npos) {
                    std::string bulstat = line.substr(line.find("Bulstat:") + 9, 9);
                    std::string name = line.substr(line.find("Name:") + 6,
                                                   line.find(", Location:") - (line.find("Name:") + 6));
                    std::string location = line.substr(line.find("Location:") + 10,
                                                       line.find(", Phone:") - (line.find("Location:") + 10));
                    std::string phone = line.substr(line.find("Phone:") + 7);
                    suppliers.emplace_back(bulstat, name, location, phone);
                }
            } catch (const std::out_of_range &e) {
                std::cerr << "Error parsing supplier data: " << e.what() << "\n";
            }
        }
        file.close();
        if (suppliers.empty()) {
            std::cout << "=============================\n";
            std::cout << "== No suppliers available. ==\n";
            std::cout << "=============================\n";
        } else {
            std::cout << "=========================================================\n";
            std::cout << "== Suppliers loaded from \"" << filename << "\" successfully. ==\n";
            std::cout << "=========================================================\n";
        }
    } else {
        std::cerr << "Unable to open file: " << filename << "\n";
    }
}

void OpticsApp::printSuppliers() const {
    std::cout << "======== Suppliers ========\n";
    if (suppliers.empty()) {
        std::cout << "No suppliers available.\n";
    } else {
        for (const auto &supplier : suppliers) {
            std::cout << supplier << "\n";
            std::cout << "---------------------------\n";
        }
    }
    std::cout << "===========================\n\n";
}

void OpticsApp::printOrders() const {
    std::cout << "======== Orders ========\n";
    if (orders.empty()) {
        std::cout << "No orders available.\n";
    } else {
        for (const auto &order : orders) {
            std::cout << order << "\n";
            std::cout << "------------------------\n";
        }
    }
    std::cout << "========================\n\n";
}

void OpticsApp::interactiveMenu() {
    int choice;
    const std::string suppliersFilename = "suppliers.txt";
    const std::string ordersFilename = "orders.txt";
    do {
        std::cout << "======== Menu ========\n";
        std::cout << "1. Add Supplier\n";
        std::cout << "2. Create Order\n";
        std::cout << "3. Add Material to Order\n";
        std::cout << "4. Print Suppliers\n";
        std::cout << "5. Print Orders\n";
        std::cout << "6. Save Suppliers to File\n";
        std::cout << "7. Save Orders to File\n";
        std::cout << "8. Load Suppliers from File\n";
        std::cout << "9. Exit\n";
        std::cout << "======================\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                std::string bulstat, name, location, phoneNumber;
                std::cout << "Enter Bulstat: ";
                std::getline(std::cin, bulstat);
                std::cout << "Enter Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Location: ";
                std::getline(std::cin, location);
                std::cout << "Enter Phone Number: ";
                std::getline(std::cin, phoneNumber);
                try {
                    addSupplier(SupplierFactory::createSupplier(bulstat, name, location, phoneNumber));
                    std::cout << "Supplier added successfully.\n";
                } catch (const std::invalid_argument &e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 2: {
                std::string bulstat;
                std::cout << "Enter Supplier Bulstat: ";
                std::getline(std::cin, bulstat);
                auto it = std::ranges::find_if(suppliers,
                                               [&bulstat](const Supplier &s) {
                                                   return s.getBulstat() == bulstat;
                                               });
                if (it != suppliers.end()) {
                    createOrder(*it);
                    std::cout << "Order created successfully.\n";
                } else {
                    std::cerr << "Supplier not found.\n";
                }
                break;
            }
            case 3: {
                size_t orderIndex;
                std::string type, materialName;
                double thickness, diopter, price;

                std::cout << "Enter Order Index: ";
                if (!(std::cin >> orderIndex)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cerr << "Invalid order index.\n";
                    break;
                }
                std::cin.ignore();
                if (orderIndex >= orders.size()) {
                    std::cerr << "Invalid order index.\n";
                    break;
                }

                std::cout << "Enter Material Type: ";
                std::getline(std::cin, type);

                std::cout << "Enter Thickness: ";
                if (!(std::cin >> thickness) || thickness <= 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cerr << "Thickness must be positive.\n";
                    break;
                }
                std::cin.ignore();

                std::cout << "Enter Diopter: ";
                if (!(std::cin >> diopter)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cerr << "Invalid diopter value.\n";
                    break;
                }
                std::cin.ignore();

                std::cout << "Enter Material Name: ";
                std::getline(std::cin, materialName);

                std::cout << "Enter Price: ";
                if (!(std::cin >> price) || price <= 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cerr << "Price must be positive.\n";
                    break;
                }

                try {
                    addMaterialToOrder(
                        orderIndex, OpticsMaterialFactory::createOpticsMaterial(type, thickness, diopter, materialName), price);
                    std::cout << "Material added successfully.\n";
                } catch (const std::invalid_argument &e) {
                    std::cerr << "Error: " << e.what() << "\n";
                } catch (const std::out_of_range &e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 4:
                std::cout << "\n";
                printSuppliers();
                break;
            case 5:
                std::cout << "\n";
                printOrders();
                break;
            case 6:
                saveSuppliersToFile(suppliersFilename);
                std::cout << "Suppliers saved to " << suppliersFilename << "\n";
                break;
            case 7:
                saveOrdersToFile(ordersFilename);
                std::cout << "Orders saved to " << ordersFilename << "\n";
                break;
            case 8:
                loadSuppliersFromFile(suppliersFilename);
                break;
            case 9:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cerr << "Invalid choice.\n";
        }
        std::cout << "\n";
    } while (choice != 9);
}