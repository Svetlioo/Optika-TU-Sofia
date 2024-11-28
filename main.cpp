#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <unordered_set>
#include <sstream>

class OpticsApp {
public:
    class Supplier {
        std::string bulstat;
        std::string name;
        std::string location;
        std::string phoneNumber;

    public:
        Supplier(const std::string &bulstat, const std::string &name, const std::string &location,
                 const std::string &phoneNumber)
            : bulstat(bulstat), name(name), location(location), phoneNumber(phoneNumber) {
            if (bulstat.empty() || bulstat.length() != 9) {
                throw std::invalid_argument("Invalid Bulstat");
            }
            if (name.empty()) {
                throw std::invalid_argument("Name cannot be empty");
            }
            if (location.empty()) {
                throw std::invalid_argument("Location cannot be empty");
            }
            if (phoneNumber.empty()) {
                throw std::invalid_argument("Phone number cannot be empty");
            }
        }

        Supplier() = default;

        [[nodiscard]] const std::string &getBulstat() const { return bulstat; }
        [[nodiscard]] const std::string &getName() const { return name; }
        [[nodiscard]] const std::string &getLocation() const { return location; }
        [[nodiscard]] const std::string &getPhoneNumber() const { return phoneNumber; }

        void setBulstat(const std::string &bulstat) {
            if (bulstat.empty() || bulstat.length() != 9) {
                throw std::invalid_argument("Invalid Bulstat");
            }
            this->bulstat = bulstat;
        }

        void setName(const std::string &name) {
            if (name.empty()) {
                throw std::invalid_argument("Name cannot be empty");
            }
            this->name = name;
        }

        void setLocation(const std::string &location) {
            if (location.empty()) {
                throw std::invalid_argument("Location cannot be empty");
            }
            this->location = location;
        }

        void setPhoneNumber(const std::string &phoneNumber) {
            if (phoneNumber.empty()) {
                throw std::invalid_argument("Phone number cannot be empty");
            }
            this->phoneNumber = phoneNumber;
        }

        friend std::ostream &operator<<(std::ostream &os, const Supplier &supplier) {
            os << "Bulstat: " << supplier.bulstat << ", Name: " << supplier.name
                    << ", Location: " << supplier.location << ", Phone: " << supplier.phoneNumber;
            return os;
        }
    };

    class OpticsMaterial {
        std::string type;
        double thickness{};
        double diopter{};
        std::string materialName;

    public:
        OpticsMaterial(const std::string &type, double thickness, double diopter, const std::string &materialName)
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

        OpticsMaterial() = default;

        [[nodiscard]] const std::string &getType() const { return type; }
        [[nodiscard]] double getThickness() const { return thickness; }
        [[nodiscard]] double getDiopter() const { return diopter; }
        [[nodiscard]] const std::string &getMaterialName() const { return materialName; }

        void setType(const std::string &type) {
            if (type.empty()) {
                throw std::invalid_argument("Type cannot be empty");
            }
            this->type = type;
        }

        void setThickness(double thickness) {
            if (thickness <= 0) {
                throw std::invalid_argument("Thickness must be positive");
            }
            this->thickness = thickness;
        }

        void setDiopter(double diopter) {
            if (diopter < 0) {
                throw std::invalid_argument("Diopter cannot be negative");
            }
            this->diopter = diopter;
        }

        void setMaterialName(const std::string &materialName) {
            if (materialName.empty()) {
                throw std::invalid_argument("Material name cannot be empty");
            }
            this->materialName = materialName;
        }

        friend std::ostream &operator<<(std::ostream &os, const OpticsMaterial &material) {
            os << "Type: " << material.type << ", Thickness: " << material.thickness
                    << ", Diopter: " << material.diopter << ", Material Name: " << material.materialName;
            return os;
        }
    };

    class Order {
        Supplier supplier;
        std::vector<OpticsMaterial> materials;
        double totalPrice;

    public:
        explicit Order(Supplier supplier) : supplier(std::move(supplier)), totalPrice(0.0) {
        }

        Order() : totalPrice(0.0) {
        }

        void addMaterial(const OpticsMaterial &material, double price) {
            if (price <= 0) {
                throw std::invalid_argument("Price must be positive");
            }
            materials.push_back(material);
            totalPrice += price;
        }

        [[nodiscard]] double calculateTotalPrice() const { return totalPrice; }
        [[nodiscard]] const Supplier &getSupplier() const { return supplier; }
        [[nodiscard]] const std::vector<OpticsMaterial> &getMaterials() const { return materials; }

        void setTotalPrice(double price) {
            totalPrice = price;
        }

        friend std::ostream &operator<<(std::ostream &os, const Order &order) {
            os << "Supplier: " << order.supplier << "\nMaterials:\n";
            for (const auto &material: order.materials) {
                os << material << "\n";
            }
            os << "Total Price: " << order.totalPrice;
            return os;
        }
    };

    std::vector<Supplier> suppliers;
    std::vector<Order> orders;

    void addSupplier(const Supplier &supplier) {
        suppliers.push_back(supplier);
    }

    void createOrder(const Supplier &supplier) {
        orders.emplace_back(supplier);
    }

    void addMaterialToOrder(size_t orderIndex, const OpticsMaterial &material, double price) {
        if (orderIndex >= orders.size()) {
            throw std::out_of_range("Invalid order index");
        }
        orders[orderIndex].addMaterial(material, price);
    }

    void saveSuppliersToFile(const std::string &filename) const {
        std::unordered_set<std::string> existingSuppliers;
        std::ifstream infile(filename);
        std::string line;
        while (std::getline(infile, line)) {
            existingSuppliers.insert(line);
        }
        infile.close();

        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            for (const auto &supplier: suppliers) {
                std::ostringstream oss;
                oss << supplier;
                if (existingSuppliers.find(oss.str()) == existingSuppliers.end()) {
                    file << oss.str() << "\n";
                }
            }
            file.close();
        }
    }

    void saveOrdersToFile(const std::string &filename) const {
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            for (const auto &order: orders) {
                file << order << "\n";
            }
            file.close();
        }
    }

    void loadSuppliersFromFile(const std::string &filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
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

    void printSuppliers() const {
        std::cout << "======== Suppliers ========\n";
        if (suppliers.empty()) {
            std::cout << "No suppliers available.\n";
        } else {
            for (const auto &supplier: suppliers) {
                std::cout << supplier << "\n";
                std::cout << "---------------------------\n";
            }
        }
        std::cout << "===========================\n\n";
    }

    void printOrders() const {
        std::cout << "======== Orders ========\n";
        if (orders.empty()) {
            std::cout << "No orders available.\n";
        } else {
            for (const auto &order: orders) {
                std::cout << order << "\n";
                std::cout << "------------------------\n";
            }
        }
        std::cout << "========================\n\n";
    }
};

void interactiveMenu(OpticsApp &app) {
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
                    app.addSupplier(OpticsApp::Supplier(bulstat, name, location, phoneNumber));
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
                auto it = std::find_if(app.suppliers.begin(), app.suppliers.end(),
                                       [&bulstat](const OpticsApp::Supplier &s) {
                                           return s.getBulstat() == bulstat;
                                       });
                if (it != app.suppliers.end()) {
                    app.createOrder(*it);
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
                std::cin >> orderIndex;
                std::cin.ignore();
                if (orderIndex >= app.orders.size()) {
                    std::cerr << "Invalid order index.\n";
                    break;
                }
                std::cout << "Enter Material Type: ";
                std::getline(std::cin, type);
                std::cout << "Enter Thickness: ";
                std::cin >> thickness;
                std::cin.ignore();
                std::cout << "Enter Diopter: ";
                std::cin >> diopter;
                std::cin.ignore();
                std::cout << "Enter Material Name: ";
                std::getline(std::cin, materialName);
                std::cout << "Enter Price: ";
                std::cin >> price;
                try {
                    app.addMaterialToOrder(
                        orderIndex, OpticsApp::OpticsMaterial(type, thickness, diopter, materialName), price);
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
                app.printSuppliers();
                break;
            case 5:
                std::cout << "\n";
                app.printOrders();
                break;
            case 6:
                app.saveSuppliersToFile(suppliersFilename);
                std::cout << "Suppliers saved to " << suppliersFilename << "\n";
                break;
            case 7:
                app.saveOrdersToFile(ordersFilename);
                std::cout << "Orders saved to " << ordersFilename << "\n";
                break;
            case 8:
                app.loadSuppliersFromFile(suppliersFilename);
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

int main() {
    OpticsApp app;
    const std::string suppliersFilename = "suppliers.txt";
    app.loadSuppliersFromFile(suppliersFilename);
    interactiveMenu(app);
    return 0;
}
