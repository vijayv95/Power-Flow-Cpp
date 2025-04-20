#include "Branch.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

std::vector<std::vector<double>> Branch::matrixG(std::vector<Branch> branch, int size) {
    std::vector<std::vector<double>> G(size,std::vector<double>(size));
    double con;

    for( int i=0; i< size; i++) {
        for (int j=0; j< size; j++) {
            con = 0;
            for(Branch& b : branch) {
                if((b.tapBusNumber == i+1 && b.tapBusNumber == j+1)
                        || (b.zBusNumber == i+1 && b.zBusNumber == j+1)) {
                    
                        con += b.branchResistance / (b.branchResistance*b.branchResistance
                                                        + b.branchReactance*b.branchReactance);
                }
                if((b.tapBusNumber == i+1 && b.zBusNumber == j+1)
                        || (b.tapBusNumber == j+1 && b.zBusNumber == i+1)) {

                        con -= b.branchResistance / (b.branchResistance*b.branchResistance
                                                        + b.branchReactance*b.branchReactance);
                }
        
            }
            G[i][j] = con;
        }
    }
    return G;
}

std::vector<std::vector<double>> Branch::matrixB(std::vector<Branch> branch, int size) {
    std::vector<std::vector<double>> B;
    double sus;
    std::vector<double> rowB;

    for( int i=0; i< size; i++) {
        rowB = {};
        for (int j=0; j< size; j++) {
            sus = 0;
            for(Branch& b : branch) {
                if((b.tapBusNumber == i+1 && b.tapBusNumber == j+1)
                        || (b.zBusNumber == i+1 && b.zBusNumber == j+1)) {
                        sus -= -b.branchReactance / (b.branchResistance*b.branchResistance
                                                        + b.branchReactance*b.branchReactance);
                        sus += b.lineCharging;
                }
                if((b.tapBusNumber == i+1 && b.zBusNumber == j+1)
                        || (b.tapBusNumber == j+1 && b.zBusNumber == i+1)) {
                    sus += -b.branchReactance / (b.branchResistance*b.branchResistance
                                                + b.branchReactance*b.branchReactance);
                }
        
            }

            rowB.push_back(sus);
        }
        B.push_back(rowB);
    }
    return B;
}

std::vector<Branch> Branch::readFile (std::string name) {

    std::ifstream file(name);
    std::string line;
    int count = 0;
    std::vector<Branch> branch;

    if(!file.is_open()) {
        std::cout << "Unable to open file: " << name;
    } else {
        while(file.good()) {
            std::getline(file, line);
            std::string sectionStart = line.substr(0,3);
            
            if (sectionStart == "BRA"){
                while (file.good()) {
                    std::getline(file, line);
                    Branch b;
                    try {
                        b.tapBusNumber = std::stoi(line.substr(0, 4));
                        if (b.tapBusNumber == -999) {
                            break;
                        }
                    } catch (...) {
                        std::cout << "Error parsing tapBusNumber\n";
                        continue;
                    }
                    try {
                        b.zBusNumber = std::stoi(line.substr(5, 4));
                    } catch (...) {
                        std::cout << "Error parsing zBusNumber\n";
                        continue;
                    }
                    try {
                        b.loadFlowArea = std::stoi(line.substr(10, 2));
                    } catch (...) {
                        std::cout << "Error parsing loadFlowArea\n";
                        continue;
                    }
                    try {
                        b.lossZone = std::stoi(line.substr(13, 2));
                    } catch (...) {
                        std::cout << "Error parsing lossZone\n";
                        continue;
                    }
                    try {
                        b.circuit = std::stoi(line.substr(16, 1));
                    } catch (...) {
                        std::cout << "Error parsing circuit\n";
                        continue;
                    }
                    try {
                        b.type = std::stoi(line.substr(18, 1));
                    } catch (...) {
                        std::cout << "Error parsing type\n";
                        continue;
                    }
                    try {
                        b.branchResistance = std::stod(line.substr(19, 10));
                    } catch (...) {
                        std::cout << "Error parsing branchResistance\n";
                        continue;
                    }
                    try {
                        b.branchReactance = std::stod(line.substr(29, 11));
                    } catch (...) {
                        std::cout << "Error parsing branchReactance\n";
                        continue;
                    }
                    try {
                        b.lineCharging = std::stod(line.substr(40, 10));
                    } catch (...) {
                        std::cout << "Error parsing lineCharging\n";
                        continue;
                    }
                    try {
                        b.lineMVARating1 = std::stoi(line.substr(50, 5));
                    } catch (...) {
                        std::cout << "Error parsing lineMVARating1\n";
                        continue;
                    }
                    try {
                        b.lineMVARating2 = std::stoi(line.substr(56, 5));
                    } catch (...) {
                        std::cout << "Error parsing lineMVARating2\n";
                        continue;
                    }
                    try {
                        b.lineMVARating3 = std::stoi(line.substr(62, 5));
                    } catch (...) {
                        std::cout << "Error parsing lineMVARating3\n";
                        continue;
                    }
                    try {
                        b.controlBusNumber = std::stoi(line.substr(68, 4));
                    } catch (...) {
                        std::cout << "Error parsing controlBusNumber\n";
                        continue;
                    }
                    try {
                        b.side = std::stoi(line.substr(73, 1));
                    } catch (...) {
                        std::cout << "Error parsing side\n";
                        continue;
                    }
                    try {
                        b.transformerTurnsRatio = std::stod(line.substr(76, 6));
                    } catch (...) {
                        std::cout << "Error parsing transformerTurnsRatio\n";
                        continue;
                    }
                    try {
                        b.transformerAngle = std::stod(line.substr(83, 7));
                    } catch (...) {
                        std::cout << "Error parsing transformerAngle\n";
                        continue;
                    }
                    try {
                        b.minTapOrPhaseShift = std::stod(line.substr(90, 7));
                    } catch (...) {
                        std::cout << "Error parsing minTapOrPhaseShift\n";
                        continue;
                    }
                    try {
                        b.maxTapOrPhaseShift = std::stod(line.substr(97, 7));
                    } catch (...) {
                        std::cout << "Error parsing maxTapOrPhaseShift\n";
                        continue;
                    }
                    try {
                        b.stepSize = std::stod(line.substr(105, 6));
                    } catch (...) {
                        std::cout << "Error parsing stepSize\n";
                        continue;
                    }
                    try {
                        b.minLimit = std::stod(line.substr(112, 7));
                    } catch (...) {
                        std::cout << "Error parsing minLimit\n";
                        continue;
                    }
                    try {
                        b.maxLimit = std::stod(line.substr(119, 7));
                    } catch (...) {
                        std::cout << "Error parsing maxLimit\n";
                        continue;
                    }

                    branch.push_back(b);
                }

            }
        }

    }
    return branch;
}


void Branch::dispayYbus(std::vector<std::vector<double>> G, std::vector<std::vector<double>> B) {
std::cout << "Nodal admittance Y = G + jB \n";
std::cout << "G matrix follows : \n";
for(auto& row : G) {
    for(auto& col : row){
        std::cout << std::fixed << std::setprecision(4) << col << " ";
    }
    std::cout << "\n";
}
std::cout << "B matrix follows : \n";
for(auto& row : B) {
    for(auto& col : row){
        std::cout << std::fixed << std::setprecision(4) << col << " ";
    }
    std::cout << "\n";
}

}
