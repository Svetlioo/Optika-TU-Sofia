#include "../include/Supplier.h"
#include <stdexcept>
#include <ostream>

Supplier::Supplier(const std::string &bulstat, const std::string &name, const std::string &location,
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

const std::string &Supplier::getBulstat() const {
    return bulstat;
}

const std::string &Supplier::getName() const {
    return name;
}

const std::string &Supplier::getLocation() const {
    return location;
}

const std::string &Supplier::getPhoneNumber() const {
    return phoneNumber;
}

void Supplier::setBulstat(const std::string &bulstat) {
    if (bulstat.empty() || bulstat.length() != 9) {
        throw std::invalid_argument("Invalid Bulstat");
    }
    this->bulstat = bulstat;
}

void Supplier::setName(const std::string &name) {
    if (name.empty()) {
        throw std::invalid_argument("Name cannot be empty");
    }
    this->name = name;
}

void Supplier::setLocation(const std::string &location) {
    if (location.empty()) {
        throw std::invalid_argument("Location cannot be empty");
    }
    this->location = location;
}

void Supplier::setPhoneNumber(const std::string &phoneNumber) {
    if (phoneNumber.empty()) {
        throw std::invalid_argument("Phone number cannot be empty");
    }
    this->phoneNumber = phoneNumber;
}

std::ostream &operator<<(std::ostream &os, const Supplier &supplier) {
    os << "Bulstat: " << supplier.bulstat << ", Name: " << supplier.name
       << ", Location: " << supplier.location << ", Phone: " << supplier.phoneNumber;
    return os;
}