#pragma once
#include <vector>
#include <string>
class Branch {
    public:
    
    static std::vector<std::vector<double>> matrixG(std::vector<Branch> , int );
    static std::vector<std::vector<double>> matrixB(std::vector<Branch> , int );
    static std::vector<std::vector<double>> matrixYmag(std::vector<Branch> , int );
    static std::vector<std::vector<double>> matrixTheta(std::vector<Branch> , int );
    static std::vector<Branch> readFile (std::string );
    static void dispayYbus(std::vector<std::vector<double>> , std::vector<std::vector<double>> );

    private:

    int tapBusNumber; // Tap bus number (non-unity tap side for transformers/phase shifters)
    int zBusNumber;   // Z bus number (impedance side for transformers/phase shifters)
    int loadFlowArea; // Load flow area
    int lossZone;     // Loss zone
    int circuit;      // Circuit 
                      // 1 - Single lines
    int type;         // Type 
                      // 0 - Transmission line
                      // 1 - Fixed tap
                      // 2 - Variable tap (voltage control)
                      // 3 - Variable tap (MVAR control)
                      // 4 - Variable phase angle (MW control)
    double branchResistance; // Branch resistance R (per unit)
    double branchReactance;  // Branch reactance X (per unit, no zero impedance lines)
    double lineCharging;     // Line charging B (per unit, total line charging, +B)
    int lineMVARating1;      // Line MVA rating No 1
    int lineMVARating2;      // Line MVA rating No 2
    int lineMVARating3;      // Line MVA rating No 3
    int controlBusNumber;    // Control bus number
    int side;                // Side 
                             // 0 - Controlled bus is one of the terminals
                             // 1 - Controlled bus near tap side
                             // 2 - Controlled bus near impedance side
    double transformerTurnsRatio; // Transformer final turns ratio
    double transformerAngle;      // Transformer (phase shifter) final angle
    double minTapOrPhaseShift;    // Minimum tap or phase shift
    double maxTapOrPhaseShift;    // Maximum tap or phase shift
    double stepSize;              // Step size
    double minLimit;              // Minimum voltage, MVAR, or MW limit
    double maxLimit;              // Maximum voltage, MVAR, or MW limit

};