#include <iostream>
#include <vector>
#include "Branch.h"
#include "Bus.h"


// class lossZone {
//     public:

//     int lossZoneNumber;
//     std::string lossZoneName;

// };

// class interchange {
//     public:

//     int areaNumber;
//     int slackBusNumber;
//     std::string alternateSwingBusName;
//     double areaInterchangeExport;
//     double areaInterchangeTolerance;
//     std::string areaCode;
//     std::string areaName;

// };

// class tie {
//     public:

//     int meteredBusNumber;
//     int meteredAreaNumber;
//     int nonMeteredBusNumber;
//     int nonMeteredAreaNumber;
//     int circuitNumber;

// };

// std::vector<Bus> bus;
// std::vector<Branch> branch;

// std::vector<std::vector<double>> G, B;

// lossZone LZ;
// interchange Inter;
// tie Tie;


// double interationCount = 0;


// void readFile () {

//     std::ifstream file(name);
//     std::string line;
//     int count = 0;

//     if(!file.is_open()) {
//         std::cout << "Unable to open file: " << name;
//     } else {
//         while(file.good()) {
//             std::getline(file, line);
//             // std::cout << "Title card: \n" << line << std::endl;
//             std::string sectionStart = line.substr(0,3);
//             if (sectionStart == "BUS") {
//                 while(1) {
//                     Bus b;
//                     std::getline(file, line);
//                     b.busNumber = std::stoi(line.substr(0,4));
//                     if (b.busNumber == -999) {
//                         break;
//                     }
//                     b.busName = line.substr(5,12);
//                     b.busType = std::stoi(line.substr(25,1));
                    
//                     b.loadFlowArea = std::stoi(line.substr(18, 2));
//                     b.lossZone = std::stoi(line.substr(20, 3));
//                     b.finalVoltage = std::stod(line.substr(27, 6));
//                     b.finalAngle = std::stod(line.substr(33, 7));
//                     if (b.busType ==  3) {
//                         b.e = b.finalVoltage;
//                         b.f = 0.0;
//                     } else {
//                         b.e = 1.0;
//                         b.f = 0.0;
//                     }
                    
//                     // b.complexVoltage = std::polar(b.finalVoltage, b.finalAngle);
//                     b.loadMW = std::stod(line.substr(40, 9));
//                     b.loadMVAR = std::stod(line.substr(49, 10));
//                     b.generationMW = std::stod(line.substr(59, 8));
//                     b.generationMVAR = std::stod(line.substr(67, 8));
//                     b.baseKV = std::stod(line.substr(76, 7));
//                     b.desiredVoltage = std::stod(line.substr(84, 6));
//                     b.maxLimit = std::stod(line.substr(90, 8));
//                     b.minLimit = std::stod(line.substr(98, 8));
//                     b.shuntConductance = std::stod(line.substr(106, 8));
//                     b.shuntSusceptance = std::stod(line.substr(114, 8));
//                     b.remoteControlledBusNumber = std::stoi(line.substr(123, 4));
//                     bus.push_back(b);
//                 }

//             // } else if (sectionStart == "BRA"){
//             //     while (1) {
//             //         std::getline(file, line);
//             //         Branch b;
//             //         b.tapBusNumber = std::stoi(line.substr(0, 4));
//             //         if (b.tapBusNumber == -999) {
//             //             break;
//             //         }
//             //         b.zBusNumber = std::stoi(line.substr(5, 4));
//             //         b.loadFlowArea = std::stoi(line.substr(10, 2));
//             //         b.lossZone = std::stoi(line.substr(13, 2));
//             //         b.circuit = std::stoi(line.substr(16, 1));
//             //         b.type = std::stoi(line.substr(18, 1));
//             //         b.branchResistance = std::stod(line.substr(19, 10));
//             //         b.branchReactance = std::stod(line.substr(29, 11));
//             //         b.lineCharging = std::stod(line.substr(40, 10));
//             //         b.lineMVARating1 = std::stoi(line.substr(50, 5));
//             //         b.lineMVARating2 = std::stoi(line.substr(56, 5));
//             //         b.lineMVARating3 = std::stoi(line.substr(62, 5));
//             //         b.controlBusNumber = std::stoi(line.substr(68, 4));
//             //         b.side = std::stoi(line.substr(73, 1));
//             //         b.transformerTurnsRatio = std::stod(line.substr(76, 6));
//             //         b.transformerAngle = std::stod(line.substr(83, 7));
//             //         b.minTapOrPhaseShift = std::stod(line.substr(90, 7));
//             //         b.maxTapOrPhaseShift = std::stod(line.substr(97, 7));
//             //         b.stepSize = std::stod(line.substr(105, 6));
//             //         b.minLimit = std::stod(line.substr(112, 7));
//             //         b.maxLimit = std::stod(line.substr(119, 7));

//             //         branch.push_back(b);

//             //         // Process or store the extracted data as needed
//             //     }

//             } else if (sectionStart == "LOS") {
//                 while (1) {
//                     std::getline(file, line);
//                     LZ.lossZoneNumber = std::stoi(line.substr(0, 3));
//                     if (LZ.lossZoneNumber == -99) {
//                         break;
//                     }
//                     LZ.lossZoneName = line.substr(4, 12);
//                     // Process or store the loss zone data as needed
//                 }

//             } else if (sectionStart == "INT") {
//                 while (1) {
//                     std::getline(file, line);
//                     Inter.areaNumber = std::stoi(line.substr(0, 2));
//                     if (Inter.areaNumber == -9) {
//                         break;
//                     }
//                     Inter.slackBusNumber = std::stoi(line.substr(3, 4));
//                     Inter.alternateSwingBusName = line.substr(8, 12);
//                     Inter.areaInterchangeExport = std::stod(line.substr(20, 8));
//                     Inter.areaInterchangeTolerance = std::stod(line.substr(29, 6));
//                     Inter.areaCode = line.substr(37, 6);
//                     Inter.areaName = line.substr(45, 30);
//                     // Process or store the interchange data as needed
//                 }

//             } else if (sectionStart == "TIE") {
//                 while (1) {
//                     std::getline(file, line);
//                     Tie.meteredBusNumber = std::stoi(line.substr(0, 4));
//                     if (Tie.meteredBusNumber == -999) {
//                         break;
//                     }
//                     Tie.meteredAreaNumber = std::stoi(line.substr(6, 2));
//                     Tie.nonMeteredBusNumber = std::stoi(line.substr(10, 4));
//                     Tie.nonMeteredAreaNumber = std::stoi(line.substr(16, 2));
//                     Tie.circuitNumber = std::stoi(line.substr(20, 1));
//                     // Process or store the tie line data as needed
//                 }
//             }
//         }
//     }

// }









int main() {
    std::string name;
    name = "ieee14cdf.txt";
    // std::cout << "Enter name of file (for example: ieee14cdf.txt): ";
    // std::cin >> name; 

    double convergenceCriterion;
    std::cout << "Input convergence criterion: ";
    std::cin >> convergenceCriterion;
    
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
