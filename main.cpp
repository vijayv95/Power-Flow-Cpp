#include <iostream>
#include <vector>
#include "Branch.h"
#include "Bus.h"


int main() {
    std::string name;
    name = "ieee14cdf.txt";
    // std::cout << "Enter name of file (for example: ieee14cdf.txt): ";
    // std::cin >> name; 

    std::vector<std::vector<double>> mat={{2,3,6,},{1,-1,0.5}};
    std::vector<double> x = Bus::gauss(mat);
    std::cout<< " result\n";
    for(double a : x){
        std::cout << a << " ";
    }
    
   
   
    // double convergenceCriterion;
    // std::cout << "Input convergence criterion: ";
    // std::cin >> convergenceCriterion;
    
    // std::vector<Bus> bus = Bus::readFile(name);
    // int size = bus.size();

    // std::vector<Branch> branch = Branch::readFile(name);
    // std::vector<std::vector<double>> G = Branch::matrixG(branch, size);
    // std::vector<std::vector<double>> B = Branch::matrixB(branch, size);
    // Branch::dispayYbus(G,B); 

    // int count = Bus::loadFlow(bus, G, B, convergenceCriterion);

    // std::cout<< "\n\n\nLoad flow anaylsis completed. \nNumber of Iterations: " << count;

    // Bus::displayResult(bus);
     
    
    return 0;
}
