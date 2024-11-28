#include "../include/OrderFactory.h"

Order OrderFactory::createOrder(const Supplier &supplier) {
    return Order(supplier);
}