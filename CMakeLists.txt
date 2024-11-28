cmake_minimum_required(VERSION 3.30)
project(Optika)

set(CMAKE_CXX_STANDARD 20)

add_executable(Optika src/main.cpp
        src/Supplier.cpp
        src/OpticsMaterial.cpp
        src/Order.cpp
        src/SupplierFactory.cpp
        src/OpticsMaterialFactory.cpp
        src/OrderFactory.cpp
        src/OpticsApp.cpp
)
