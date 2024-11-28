#include "../include/SupplierFactory.h"

Supplier SupplierFactory::createSupplier(const std::string &bulstat, const std::string &name, const std::string &location, const std::string &phoneNumber) {
    return {bulstat, name, location, phoneNumber};
}