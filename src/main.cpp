#include <iostream>
#include <string>
#include "../include/OpticsApp.h"

int main() {
    OpticsApp app;
    const std::string suppliersFilename = "suppliers.txt";
    app.loadSuppliersFromFile(suppliersFilename);
    app.interactiveMenu();
    return 0;
}