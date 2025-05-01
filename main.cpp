#include <iostream>
#include <vector>
#include "Branch.h"
#include "Bus.h"


int main() {
    std::string name;
    // name = "Data/ieee14cdf.txt";
    // name = "Data/JacobianTest1.txt";
    // name = "Data/JacobianTest2.txt";
    name = "Data/JacobianTest3.txt";
    // name = "test.txt";
    // std::cout << "Enter name of file (for example: ieee14cdf.txt): ";
    // std::cin >> name; 


   
   
    double convergenceCriterion = 0.1;
    // std::cout << "Input convergence criterion: ";
    // std::cin >> convergenceCriterion;
    
    std::vector<Bus> bus = Bus::readFile(name);
    int size = bus.size();

    std::vector<Branch> branch = Branch::readFile(name);
    std::vector<std::vector<double>> G = Branch::matrixG(branch, size);
    std::vector<std::vector<double>> B = Branch::matrixB(branch, size);
    Branch::dispayYbus(G,B); 

    int count = Bus::loadFlow(bus, G, B, convergenceCriterion);

    std::cout<< "\n\n\nLoad flow anaylsis completed. \nNumber of Iterations: " << count;

    Bus::displayResult(bus);
     
    
    return 0;
}
