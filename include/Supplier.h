#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <string>


class Supplier {
    std::string bulstat;
    std::string name;
    std::string location;
    std::string phoneNumber;

public:
    Supplier(const std::string &bulstat, const std::string &name, const std::string &location,
             const std::string &phoneNumber);

    Supplier() = default;

    [[nodiscard]] const std::string &getBulstat() const;
    [[nodiscard]] const std::string &getName() const;
    [[nodiscard]] const std::string &getLocation() const;
    [[nodiscard]] const std::string &getPhoneNumber() const;

    void setBulstat(const std::string &bulstat);
    void setName(const std::string &name);
    void setLocation(const std::string &location);
    void setPhoneNumber(const std::string &phoneNumber);

    friend std::ostream &operator<<(std::ostream &os, const Supplier &supplier);
};

#endif //SUPPLIER_H