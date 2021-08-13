#include <iostream>
#include <fstream>
#include "../config.hpp"

int main() {
    vs::config cfg;
    std::ifstream infile("config.cfg"); cfg.read_from_stream(infile); infile.close();
    std::ofstream outfile("test.txt"); cfg.write_to_stream(outfile); outfile.close();
    std::string viscLaw = cfg["FluidProperties.ViscosityLaw.type"];
    double Sref = cfg["FluidProperties.ViscosityLaw.Sref"];
    std::cout << viscLaw << std::endl;
    std::cout << Sref << std::endl;
}