#pragma once
#include <vector>
#include <string>

class Bus {

    public:

    static std::vector<Bus> readFile (std::string);
    static void displayResult(std::vector<Bus>);
    static int loadFlow(std::vector<Bus>, std::vector<std::vector<double>>, std::vector<std::vector<double>>, double);
    static void matrixPivot (std::vector<std::vector<double>>&);
    static void displayMatrix (std::vector<std::vector<double>>&);
    static void gaussElimination (std::vector<std::vector<double>>&);
    static std::vector<double> gauss(std::vector<std::vector<double>>&);
    static void swapMatrixRows (std::vector<std::vector<double>>&);
        
    private:

    int busNumber;                // Bus number
    std::string busName;          // Name
    int loadFlowArea;             // Load flow area number
    int lossZone;                 // Loss zone number
    int busType;                  // Type
                                    // 0 - Unregulated (load, PQ)
                                    // 1 - Hold MVAR generation within voltage limits, (PQ)
                                    // 2 - Hold voltage within VAR limits (gen, PV)
                                    // 3 - Hold voltage and angle (swing, V-Theta)

    double finalVoltage;          // Final voltage, p.u.
    double finalAngle;            // Final angle, degrees
    double e;                     // Real part of voltage
    double f;                     // Imaginary part of voltage
    double calculatedVoltage;
    double calculatedAngle;
    // std::complex<double> complexVoltage; // Complex form of voltage
    double loadMW;                // Load MW
    double loadMVAR;              // Load MVAR
    double P;                     // Load MW used in iterations
    double Q;                     // Load MVAR used in interations
    double deltaP = 0.0;
    double deltaQ = 0.0;
    double deltaV2 = 0.0;
    bool deltaV2flag = false;
    double deltae = 1.0;
    double deltaf = 0.0;
    double generationMW;          // Generation MW
    double generationMVAR;        // Generation MVAR
    double baseKV;                // Base KV

    double desiredVoltage;        // Desired volts (pu)
    double maxLimit;              // Maximum MVAR or voltage limit
    double minLimit;              // Minimum MVAR or voltage limit
    double shuntConductance;      // Shunt conductance G (per unit)
    double shuntSusceptance;      // Shunt susceptance B (per unit)
    int remoteControlledBusNumber;// Remote controlled bus number
    
        
    
};
