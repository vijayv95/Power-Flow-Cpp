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

/* 
Pivoting the matrix.
*/
void Bus::matrixPivot (std::vector<std::vector<double>>& Mat) {
    for(int i = 0; i < Mat.size() - 1; i++) {
        if (Mat[i][i] == 0) {
            bool flag = false;
            for (int j = 1; j < Mat.size() - i; j++) {
            if (Mat[i+j][i] != 0) {
                std::swap(Mat[i],Mat[i+j]);
                flag = true; 
                break;
                } 
            }
            // if(!flag) {
            //     for (int j = 0; j < i; j++) {
            //         if (Mat[j][i] != 0) {
            //             std::swap(Mat[i],Mat[j]);
                        
            //             break;
            //         } 
            //     }
            //     Bus::matrixPivot(Mat);
            // }
        }
            
    }    
}

void Bus::gaussElimination (std::vector<std::vector<double>>& mat) {
    for (int i=0; i< mat.size(); i++) {
        if (mat[i][i] == 0) {
            for (int j = 1; j < mat.size() - i; j++) {
            if (mat[i+j][i] != 0) {
                std::swap(mat[i],mat[i+j]);
                break;
                } 
            }
        }
        if (mat[i][i] != 0) {
        for (int row = i+1; row < mat.size(); row++) {
            for(int col = i; col < mat.size() +1; col++) {
                mat[row][col] -= mat[i][col]*(mat[row][i]/mat[i][i]); 
            }
        }
        }
    
        std::cout<< " during gauss step: " << i+1 << "\n";
        Bus::displayMatrix(mat);
    
    }
}


void Bus::swapMatrixRows (std::vector<std::vector<double>>& A) {
    int n = A.size();
    for (int i = 0; i <= n/2 ; i++) {
        for (int j = 0; j < n+1; j++) {
            double temp = A[i][j];
            A[i][j] = A[n-i-1][j];
            A[n-i-1][j] = temp;
        }
    }
}

std::vector<double> Bus::gauss(std::vector<std::vector<double> >& A) {
    int n = A.size();

    for (int i=0; i<n; i++) {
        // Search for maximum in this column
        double maxEl = abs(A[i][i]);
        int maxRow = i;
        for (int k=i+1; k<n; k++) {
            if (abs(A[k][i]) > maxEl) {
                maxEl = abs(A[k][i]);
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


void Bus::displayMatrix (std::vector<std::vector<double>>& Mat) {
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

int Bus::loadFlow(std::vector<Bus> bus, std::vector<std::vector<double>> G, std::vector<std::vector<double>> B, double convergenceCriterion) {
    int size = bus.size();
    double maxChange = convergenceCriterion + 0.1;
    int interationCount = 0;

    std::vector<std::vector<double>> J1;
    std::vector<std::vector<double>> J2;
    std::vector<std::vector<double>> J3;
    std::vector<std::vector<double>> J4;
    std::vector<std::vector<double>> J5;
    std::vector<std::vector<double>> J6;
    std::vector<std::vector<double>> Jaugmented;
    std::vector<double> J1row,J2row,J3row,J4row,J5row,J6row,Jaugrow;
    double Gtemp = 0, Btemp = 0;
    std::vector<double> GtempVector, BtempVector;
    std::vector<double> var;
    int VbusCount = 0;
    int QbusCount = 0;

    while(maxChange > convergenceCriterion) {
        for(int i = 0; i < bus.size(); i++) {
            if(bus[i].busType == 3) {
                continue;
            }
            bus[i].P = 0;
            bus[i].Q = 0;
            for(int j=0; j < G.size(); j++) {
                bus[i].P += (bus[i].e * (bus[j].e * G[i][j] + bus[j].f * B[i][j])
                             + bus[i].f * (bus[j].f * G[i][j] - bus[j].e * B[i][j]));
                bus[i].Q += (bus[i].f * (bus[j].e * G[i][j] + bus[j].f * B[i][j])
                             - bus[i].e * (bus[j].f * G[i][j] - bus[j].e * B[i][j]));

            }
            bus[i].deltaP = (bus[i].generationMW - bus[i].loadMW) - bus[i].P;
            if(bus[i].busType == 2) {
                if(bus[i].Q <= bus[i].minLimit) {
                    bus[i].Q = bus[i].minLimit;
                    bus[i].deltaQ = (bus[i].generationMVAR - bus[i].loadMVAR) - bus[i].Q;
                    QbusCount++;
                } else if(bus[i].Q >= bus[i].maxLimit) {
                    bus[i].Q = bus[i].maxLimit;
                    bus[i].deltaQ = (bus[i].generationMVAR - bus[i].loadMVAR) - bus[i].Q;
                    QbusCount++;
                } else {
                    bus[i].deltaV2 = std::sqrt(bus[i].finalVoltage*bus[i].finalVoltage - (bus[i].e * bus[i].e + bus[i].f * bus[i].f));
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


        GtempVector = {};
        BtempVector = {};
        for(int i=0; i< bus.size(); i++) {
            Gtemp = 0;
            Btemp = 0;
            for (int j = 0; j < bus.size(); j++) {
                if (i!=j) {
                    Gtemp += bus[i].e * G[i][j] + bus[i].f * B[i][j]; 
                    Btemp += bus[i].f * G[i][j] - bus[i].e * B[i][j]; 
                }
            }
            GtempVector.push_back(Gtemp);
            BtempVector.push_back(Btemp);
        }

         /* 
        The following segment builds the Jacobian matrices.
        */
        J1 = {};
        J2 = {};
        J3 = {};
        J4 = {};
        J5 = {};
        J6 = {};
        
        for(int i=1; i< bus.size(); i++) {
            J1row = {};
            J2row = {};
            J3row = {};
            J4row = {};
            J5row = {};
            J6row = {};
            for(int j=1; j< bus.size(); j++) {
                if (i==j) {
                    J1row.push_back(2*bus[i].e*G[i][i] + GtempVector[i]);
                    J2row.push_back(2*bus[i].f*G[i][i] + BtempVector[i]);
                    if (bus[i].deltaV2flag) {
                        J5row.push_back(2*bus[i].e);
                        J6row.push_back(2*bus[i].f);
                    } else {
                        J3row.push_back(2*bus[i].e*B[i][i] - BtempVector[i]);
                        J4row.push_back(2*bus[i].f*B[i][i] + GtempVector[i]);
                    }            
                } else {
                    J1row.push_back(bus[i].e*G[i][j] - bus[i].f*B[i][j]);
                    J2row.push_back(bus[i].e*B[i][j] + bus[i].f*G[i][j]);
                    if (bus[i].deltaV2flag) {
                        J5row.push_back(0.0);
                        J6row.push_back(0.0);
                    } else {
                        J3row.push_back(bus[i].e*B[i][j] + bus[i].f*G[i][j]);
                        J4row.push_back(bus[i].f*B[i][j] - bus[i].e*G[i][j]);
                    } 
                }
            }
            J1.push_back(J1row);
            J2.push_back(J2row);
            if (bus[i].busType == 2) {
                J5.push_back(J5row);
                J6.push_back(J6row);
            } else {
                J3.push_back(J3row);
                J4.push_back(J4row);               
            }
        }
        

        // std::vector<std::vector<double>> J1(size-1, std::vector<double>(size-1));
        // std::vector<std::vector<double>> J2(size-1, std::vector<double>(size-1));
        // std::vector<std::vector<double>> J3(QbusCount, std::vector<double>(size));
        // std::vector<std::vector<double>> J4(QbusCount, std::vector<double>(size));
        // std::vector<std::vector<double>> J5(VbusCount, std::vector<double>(size));
        // std::vector<std::vector<double>> J6(VbusCount, std::vector<double>(size));
        // std::vector<std::vector<double>> Jaugmented(QbusCount + VbusCount + size, std::vector<double>(2*size));

        // int k = 0;
        // int l = 0;
        // for(int i = 1; i < size; i++) {
        //     for(int j = 1; j < size; j++) {
        //         if( i == j ) {
        //             J1[i-1][j-1] = 2*bus[i].e*G[i][i] + GtempVector[i];
        //             J2[i-1][j-1] = 2*bus[i].f*G[i][i] + BtempVector[i];
        //             Jaugmented[i-1][j-1] = 2*bus[i].e*G[i][i] + GtempVector[i];
        //             Jaugmented[i-1][size + j-1] = 2*bus[i].f*G[i][i] + BtempVector[i];
        //             if (bus[i].deltaV2flag) {
        //                 J5[k][j-1] = 2*bus[i].e;
        //                 J6[k][j-1] = 2*bus[i].f;
        //                 Jaugmented[QbusCount + size + k][j-1] = 2*bus[i].e;
        //                 Jaugmented[QbusCount + size + k][size + j-1] = 2*bus[i].f;
        //             } else {
        //                 J3[l][j-1] = 2*bus[i].e*B[i][i] - BtempVector[i];
        //                 J4[l][j-1] = 2*bus[i].f*B[i][i] + GtempVector[i];
        //                 Jaugmented[size + l][j-1] = 2*bus[i].e*B[i][i] - BtempVector[i];
        //                 Jaugmented[size + l][size + j-1] = 2*bus[i].f*B[i][i] + GtempVector[i];
        //             }
        //         } else {
        //             J1[i-1][j-1] = bus[i].e*G[i][j] - bus[i].f*B[i][j];
        //             J2[i-1][j-1] = bus[i].e*B[i][j] + bus[i].f*G[i][j];
        //             Jaugmented[i-1][j-1] = bus[i].e*G[i][j] - bus[i].f*B[i][j];
        //             Jaugmented[i-1][size + j-1] = bus[i].e*B[i][j] + bus[i].f*G[i][j];
        //             if (bus[i].deltaV2flag) {
        //                 J5[k][j-1] = 0.0;
        //                 J6[k][j-1] = 0.0;
        //                 Jaugmented[QbusCount + size + k][j-1] = 0.0;
        //                 Jaugmented[QbusCount + size + k][size + j-1] = 0.0;
        //             } else {
        //                 J3[l][j-1] = bus[i].e*B[i][j] + bus[i].f*G[i][j];
        //                 J4[l][j-1] = bus[i].f*B[i][j] - bus[i].e*G[i][j];
        //                 Jaugmented[size + l][j-1] = bus[i].e*B[i][j] + bus[i].f*G[i][j];
        //                 Jaugmented[size + l][size + j-1] = bus[i].f*B[i][j] - bus[i].e*G[i][j];
        //             }
        //         }
        //     }
        //     Jaugmented[i-1][2*size] = bus[i].deltaP;
        //     if (bus[i].deltaV2flag) {
        //         Jaugmented[QbusCount + size + k][2*size] = bus[i].deltaV2;
        //         k++;
        //     } else {
        //         Jaugmented[size + l][2*size] = bus[i].deltaQ;
        //         l++;
        //     }
        // }



         /* 
        The following segment compiles individual Jacobian Matrices to form the J augmented matrix.
        */
        Jaugmented = {};
        for (int i=0; i<J1.size()+J3.size()+J5.size(); i++) {
            Jaugrow = {};
            for (int j=0; j<J1row.size()+J2row.size()+1; j++) {
                if (i<J1.size()) {
                    if (j<J1row.size()) {
                        Jaugrow.push_back(J1[i][j]);
                    } else if (j<J1row.size()+J2row.size()) {
                        Jaugrow.push_back(J2[i][j-J1row.size()]);
                    } else {
                        Jaugrow.push_back(bus[i].deltaP);
                    }
                } else if (i<J1.size()+J3.size()) {
                    if (j<J3row.size()) {
                        Jaugrow.push_back(J3[i-J1.size()][j]);
                    } else if (j<J1row.size()+J2row.size()) {
                        Jaugrow.push_back(J4[i-J1.size()][j-J1row.size()]);
                    } else {
                        Jaugrow.push_back(bus[i-J1.size()].deltaQ);
                    }
                } else if (i<J1.size()+J3.size()+J5.size()) {
                    if (j<J1row.size()) {
                        Jaugrow.push_back(J5[i-J1.size()-J3.size()][j]);
                    } else if (j<J1row.size()+J2row.size()) {
                        Jaugrow.push_back(J6[i-J1.size()-J3.size()][j-J1row.size()]);
                    } else {
                        Jaugrow.push_back(bus[i-J1.size()-J3.size()].deltaV2);
                    }
                }
            }
            Jaugmented.push_back(Jaugrow);
        }

        // std::cout<< " Before pivot \n";
        // Bus::displayMatrix(Jaugmented);

        // Bus::matrixPivot(Jaugmented);
        // std::cout<< " After pivot \n";
        // Bus::displayMatrix(Jaugmented);
        
        // std::cout<< " Before gauss \n";
        // Bus::displayMatrix(Jaugmented);
        
        // Bus::gaussElimination (Jaugmented);

        // std::cout<< " After gauss \n";
        // Bus::displayMatrix(Jaugmented);

        // std::cout<< " Before shuffle \n";
        // Bus::displayMatrix(Jaugmented);

        // Bus::swapMatrixRows(Jaugmented);

        std::cout<< " Before gauss \n";
        Bus::displayMatrix(Jaugmented);
        
        var = Bus::gauss (Jaugmented);

        std::cout<< " After gauss \n";
        Bus::displayMatrix(Jaugmented);

        /* 
        The following segment finds the values of (delta)e and (delta)f.
        */
        // double temp;
        // var = {};
        // if(Jaugmented[Jaugmented.size()-1][Jaugmented.size()-1]==0){
        //     var.push_back(0);
        // } else {
        //     var.push_back(Jaugmented[Jaugmented.size()-1][Jaugmented.size()]/Jaugmented[Jaugmented.size()-1][Jaugmented.size()-1]);
        // }
        // for(int i = 0; i < Jaugmented.size(); i++) {
        //     temp = Jaugmented[Jaugmented.size()-i-1][Jaugmented.size()];
        //     for(int j = 0; j < Jaugrow.size(); j++) {
        //     temp -= var[j]*Jaugmented[Jaugmented.size()-i-1][Jaugrow.size()-j-1];
        //     }
        //     var.push_back(temp/Jaugmented[i][i]);
        // }
        // for(int i = 0; i< bus.size(); i++) {
        //     bus[i].deltae = var[2*bus.size()-1-i];
        //     bus[i].deltaf = var[bus.size()-1-i];
        //     bus[i].e += bus[i].deltae;
        //     bus[i].f += bus[i].deltaf;
        //     bus[i].calculatedVoltage = std::sqrt(bus[i].e*bus[i].e + bus[i].f*bus[i].f);
        //     bus[i].calculatedAngle = std::atan(bus[i].f/bus[i].e)*180/(std::atan(1)*4);
        // }

        for(int i = 1; i< bus.size(); i++) {
            bus[i].deltae = var[i-1];
            bus[i].deltaf = var[bus.size()+i-1];
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