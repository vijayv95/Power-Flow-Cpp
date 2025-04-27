#include "Bus.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <numbers>
#include <cmath>
#include <iomanip>


std::vector<Bus> Bus::readFile (std::string name) {
    std::vector<Bus> bus;

    std::ifstream file(name);
    std::string line;
    int count = 0;

    if(!file.is_open()) {
        std::cout << "Unable to open file: " << name;
    } else {
        while(file.good()) {
            std::getline(file, line);
            std::string sectionStart = line.substr(0,3);
            if (sectionStart == "BUS") {
                while(file.good()) {
                    Bus b;
                    std::getline(file, line);
                    try {
                        b.busNumber = std::stoi(line.substr(0,4));
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing busNumber: " << e.what() << "\n";
                        continue;
                    }
                    if (b.busNumber == -999) {
                        break;
                    }
                    b.busName = line.substr(5,12);
                    try {
                        b.busType = std::stoi(line.substr(25,1));
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing busType: " << e.what() << "\n";
                        continue;
                    }
                    try {
                        b.loadFlowArea = std::stoi(line.substr(18, 2));
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing loadFlowArea: " << e.what() << "\n";
                        continue;
                    }
                    try {
                        b.lossZone = std::stoi(line.substr(20, 3));
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing lossZone: " << e.what() << "\n";
                        continue;
                    }
                    try {
                        b.finalVoltage = std::stod(line.substr(27, 6));
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing finalVoltage: " << e.what() << "\n";
                        continue;
                    }
                    try {
                        b.finalAngle = std::stod(line.substr(33, 7));
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing finalAngle: " << e.what() << "\n";
                        continue;
                    }
                    if (b.busType ==  3) {
                        b.e = b.finalVoltage;
                        b.f = 0.0;
                    } else {
                        b.e = 1.0;
                        b.f = 0.0;
                    }
                    try {
                        b.loadMW = std::stod(line.substr(40, 9));
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing loadMW: " << e.what() << "\n";
                        continue;
                    }
                    try {
                        b.loadMVAR = std::stod(line.substr(49, 10));
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing loadMVAR: " << e.what() << "\n";
                        continue;
                    }
                    try {
                        b.generationMW = std::stod(line.substr(59, 8));
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing generationMW: " << e.what() << "\n";
                        continue;
                    }
                    try {
                        b.generationMVAR = std::stod(line.substr(67, 8));
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing generationMVAR: " << e.what() << "\n";
                        continue;
                    }
                    try {
                        b.baseKV = std::stod(line.substr(76, 7));
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing baseKV: " << e.what() << "\n";
                        continue;
                    }
                    try {
                        b.desiredVoltage = std::stod(line.substr(84, 6));
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing desiredVoltage: " << e.what() << "\n";
                        continue;
                    }
                    try {
                        b.maxLimit = std::stod(line.substr(90, 8));
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing maxLimit: " << e.what() << "\n";
                        continue;
                    }
                    try {
                        b.minLimit = std::stod(line.substr(98, 8));
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing minLimit: " << e.what() << "\n";
                        continue;
                    }
                    try {
                        b.shuntConductance = std::stod(line.substr(106, 8));
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing shuntConductance: " << e.what() << "\n";
                        continue;
                    }
                    try {
                        b.shuntSusceptance = std::stod(line.substr(114, 8));
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing shuntSusceptance: " << e.what() << "\n";
                        continue;
                    }
                    try {
                        b.remoteControlledBusNumber = std::stoi(line.substr(123, 4));
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing remoteControlledBusNumber: " << e.what() << "\n";
                        continue;
                    }
                    bus.push_back(b);
                }
            }
        }
    }
    return bus;
}


std::vector<double> Bus::gauss(std::vector<std::vector<double> >& A) {
    int n = A.size();

    for (int i=0; i<n; i++) {
        // Search for maximum in this column
        double maxEl = std::abs(A[i][i]);
        int maxRow = i;
        for (int k=i+1; k<n; k++) {
            if (std::abs(A[k][i]) > maxEl) {
                maxEl = std::abs(A[k][i]);
                maxRow = k;
            }
        }

        // Swap maximum row with current row (column by column)
        if (maxRow!=i) {
            for (int k=i; k<n+1;k++) {
            double tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k] = tmp;
            }
        }
        

        // Make all rows below this one 0 in current column
        for (int k=i+1; k<n; k++) {
            double c = -A[k][i]/A[i][i];
            for (int j=i; j<n+1; j++) {
                if (i==j) {
                    A[k][j] = 0;
                } else {
                    A[k][j] += c * A[i][j];
                }
            }
        }
        // std::cout<< " during gauss step: " << i+1 << "\n";
        // Bus::displayMatrix(A);
    }

    // Solve equation Ax=b for an upper triangular matrix A
    std::vector<double> x(n,0);
    for (int i=n-1; i>=0; i--) {
        x[i] = A[i][n]/A[i][i];
        for (int k=i-1;k>=0; k--) {
            A[k][n] -= A[k][i] * x[i];
        }
    }
    return x;

}


void Bus::displayBinaryMatrix (std::vector<std::vector<double>>& Mat) {
    for(int i= 0; i<Mat.size();i++) {
        for(int j =0; j<Mat[i].size();j++) {
            if(Mat[i][j]==0) {
                std::cout<<"0 ";
            } else {
                std::cout<<"1 ";
            }
            
        }
        std::cout<<std::endl;
    }
}


void Bus::displayMatrix (std::vector<std::vector<double>>& Mat) {
    for(int i= 0; i<Mat.size();i++) {
        for(int j =0; j<Mat[i].size();j++) {
            std::cout<<Mat[i][j]<<" ";            
        }
        std::cout<<std::endl;
    }
}

int Bus::loadFlow(std::vector<Bus> bus, std::vector<std::vector<double>> G, std::vector<std::vector<double>> B, double convergenceCriterion) {
    int size = bus.size();
    double maxChange = convergenceCriterion;
    int interationCount = 0;

    double Gtemp = 0, Btemp = 0;
    std::vector<double> GtempVector(size-1), BtempVector(size-1);
    std::vector<double> var;
    

    std::vector<std::vector<double>> Jaugmented(2*size-2, std::vector<double>(2*size-1));

    while(maxChange >= convergenceCriterion) {

        /*
        Calculate residues P, Q, and V^2
        */
       int VbusCount = 0;
       int QbusCount = 0;
        for(int i = 0; i < size; i++) {
            bus[i].deltaV2flag = false;
            if(bus[i].busType == 3) {       //Check for slack bus
                continue;
            }
            bus[i].P = 0;
            bus[i].Q = 0;
            for(int j=0; j < size; j++) {
                bus[i].P += (bus[i].e * (bus[j].e * G[i][j] + bus[j].f * B[i][j])
                             + bus[i].f * (bus[j].f * G[i][j] - bus[j].e * B[i][j]));
                bus[i].Q += (bus[i].f * (bus[j].e * G[i][j] + bus[j].f * B[i][j])
                             - bus[i].e * (bus[j].f * G[i][j] - bus[j].e * B[i][j]));
            }
            bus[i].deltaP = (bus[i].generationMW - bus[i].loadMW) - bus[i].P;

            if(bus[i].busType == 2) {       //Check for Voltage controlled bus
                if(bus[i].Q <= bus[i].minLimit) {
                    bus[i].deltaQ = bus[i].minLimit - bus[i].Q;
                    QbusCount++;
                } else if(bus[i].Q >= bus[i].maxLimit) {
                    bus[i].deltaQ = bus[i].maxLimit - bus[i].Q;
                    QbusCount++;
                } else {
                    bus[i].deltaV2 = bus[i].finalVoltage*bus[i].finalVoltage - (bus[i].e * bus[i].e + bus[i].f * bus[i].f);
                    VbusCount++;
                    bus[i].deltaV2flag = true;
                }
            } else {
                bus[i].deltaQ = (bus[i].generationMVAR - bus[i].loadMVAR) - bus[i].Q;
                QbusCount++;
            }       
        
        }

        /*
        Comparison of residues
        */
        maxChange = convergenceCriterion;

        for(int i=0; i< bus.size(); i++) {
            if (maxChange < std::abs(bus[i].deltaP)) {
                maxChange = std::abs(bus[i].deltaP); 
            }
            if (maxChange < std::abs(bus[i].deltaQ)) {
                maxChange = std::abs(bus[i].deltaQ);
            }
            if (maxChange < std::abs(bus[i].deltaV2)) {
                maxChange = std::abs(bus[i].deltaV2);
            }
        }
        if(maxChange < convergenceCriterion) {
            break;
        }

         /* 
        The following segment are intermediate steps to build the Jacobian matrices.
        */

        for(int i=1; i< size; i++) {
            Gtemp = 0;
            Btemp = 0;
            for (int j = 0; j < size; j++) {
                if (i!=j) {
                    Gtemp += bus[j].e * G[i][j] + bus[j].f * B[i][j]; 
                    Btemp += bus[j].f * G[i][j] - bus[j].e * B[i][j]; 
                }
            }
            GtempVector[i-1] = Gtemp;
            BtempVector[i-1] = Btemp;
        }

         /* 
        The following segment builds the Jacobian matrix.
        */


        int k = 0;
        int l = 0;
        for(int i = 1; i < size; i++) {
            for(int j = 1; j < size; j++) {
                if( i == j ) {
                    Jaugmented[i-1][j-1] = 2*bus[i].e*G[i][i] + GtempVector[i-1];
                    Jaugmented[i-1][size -1 + j-1] = 2*bus[i].f*G[i][i] + BtempVector[i-1];
                    if (bus[i].deltaV2flag) {
                        Jaugmented[QbusCount + size -1 + k][j-1] = 2*bus[i].e;
                        Jaugmented[QbusCount + size -1 + k][size -1 + j-1] = 2*bus[i].f;
                    } else {
                        Jaugmented[size -1 + l][j-1] = 2*bus[i].e*B[i][i] - BtempVector[i-1];
                        Jaugmented[size -1 + l][size -1 + j-1] = 2*bus[i].f*B[i][i] + GtempVector[i-1];
                    }
                } else {
                    Jaugmented[i-1][j-1] = bus[i].e*G[i][j] - bus[i].f*B[i][j];
                    Jaugmented[i-1][size -1 + j-1] = bus[i].e*B[i][j] + bus[i].f*G[i][j];
                    if (bus[i].deltaV2flag) {
                        Jaugmented[QbusCount + size -1 + k][j-1] = 0.0;
                        Jaugmented[QbusCount + size -1 + k][size -1 + j-1] = 0.0;
                    } else {
                        Jaugmented[size -1 + l][j-1] = bus[i].e*B[i][j] + bus[i].f*G[i][j];
                        Jaugmented[size -1 + l][size -1 + j-1] = bus[i].f*B[i][j] - bus[i].e*G[i][j];
                    }
                }
            }
            Jaugmented[i-1][2*size-2] = bus[i].deltaP;
            if (bus[i].deltaV2flag) {
                Jaugmented[QbusCount + size -1 + k][2*size-2] = bus[i].deltaV2;
                k++;
            } else {
                Jaugmented[size -1 + l][2*size-2] = bus[i].deltaQ;
                l++;
            }
        }

        // std::cout<< " Before gauss \n";
        // Bus::displayBinaryMatrix(Jaugmented);
        
        std::cout<< " Before gauss \n";
        Bus::displayMatrix(Jaugmented);

        var = Bus::gauss (Jaugmented);

        std::cout<< " After gauss \n";
        Bus::displayBinaryMatrix(Jaugmented);

        /* 
        The following segment finds the values of (delta)e and (delta)f.
        */
    
        for(int i = 1; i< size; i++) {
            bus[i].deltae = var[i-1];
            bus[i].deltaf = var[size + i-1];
            bus[i].e += bus[i].deltae;
            bus[i].f += bus[i].deltaf;
            bus[i].calculatedVoltage = std::sqrt(bus[i].e*bus[i].e + bus[i].f*bus[i].f);
            bus[i].calculatedAngle = std::atan(bus[i].f/bus[i].e)*180/(std::atan(1)*4);
        }
      interationCount++;
    
    }
    
    return interationCount;
}

void Bus::displayResult(std::vector<Bus> bus) {
    std::cout<< "\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n";
    for(int i=0; i< bus.size(); i++) {
        std::cout<< "\nBus number: " << bus[i].busNumber;
        std::cout<< "\nSpecified final Voltage (pu)    : " << bus[i].finalVoltage;
        std::cout<< "\nCalculated final voltage (pu)   : " << bus[i].calculatedVoltage;
        std::cout<< "\nSpecified phase angle (degree)  : " << bus[i].finalVoltage;
        std::cout<< "\nCalculated phase angle (degree) : " << bus[i].calculatedVoltage;
        std::cout<< "\n------------------------------------------------";
    }
    std::cout<< "\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n";
}