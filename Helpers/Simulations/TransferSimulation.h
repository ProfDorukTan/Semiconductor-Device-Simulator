//
// Created by Doruk Tan Atila on 13/04/24.
//

#ifndef MOSFET_SIMULATION_PROGRAM_1_TRANSFERSIMULATION_H
#define MOSFET_SIMULATION_PROGRAM_1_TRANSFERSIMULATION_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include "../MOSFET/MOSFET.h"
#include "../Level1/Level1Calculation.h"
#include "../Level2/Level2Calculation.h"
#include "../Level3/Level3Calculation.h"
#include "../Level4/Level4Calculation.h"
#include "../Level5/Level5Calculation.h"
#include "../Level6/Level6Calculation.h"
#include "../Support/STRING_TO_WIDECHAR.h"
#include "../Support/Plot/supportLib.h"

class TransferSimulation {
public:
    TransferSimulation(MOSFET& mosfet_par, double Vmin_var, double Vmax_var, double Vstep_var, const std::vector<double>& params_Vds);
    const std::unordered_map<double, std::vector<double>>& getParams_Vds_Ids() const;
    //SIMULATION
    void GenerateTransferCurve(int COMPLEXITY);
    void GraphTransferCurve(int COMPLEXITY);
    void GraphTransferCurveLog(int COMPLEXITY);


private:
    MOSFET mosfet_;
    double Vmin_, Vmax_, Vstep_;
    std::unordered_map<double, std::vector<double>> Params_Vds_Ids_;
    std::vector<double> Params_Vgs_;

};


#endif //MOSFET_SIMULATION_PROGRAM_1_TRANSFERSIMULATION_H
