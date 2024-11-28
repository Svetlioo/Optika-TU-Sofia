#ifndef SUPPLIERFACTORY_H
#define SUPPLIERFACTORY_H

#include "Supplier.h"

class SupplierFactory {
public:
    static Supplier createSupplier(const std::string &bulstat, const std::string &name, const std::string &location, const std::string &phoneNumber);
};

#endif //SUPPLIERFACTORY_H