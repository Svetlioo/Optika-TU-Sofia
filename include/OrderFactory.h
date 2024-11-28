#ifndef ORDERFACTORY_H
#define ORDERFACTORY_H

#include "Order.h"

class OrderFactory {
public:
    static Order createOrder(const Supplier &supplier);
};

#endif //ORDERFACTORY_H