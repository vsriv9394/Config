#include <iostream>
#define config_namespace CFG
#include "../config.hpp"

int main() {
    CFG::Config config;
    config.readFromFile("config.cfg");
    config.writeToTerminal();
    std::string viscLaw = config["FluidProperties.ViscosityLaw.type"];
    double Sref = config["FluidProperties.ViscosityLaw.Sref"];
    std::cout << viscLaw << std::endl;
    std::cout << Sref << std::endl;
}