//
// Created by Doruk Tan Atila on 11/12/23.
//

#ifndef MOSFET_SIMULATION_PROGRAM_1_OUTPUTSIMULATION_H
#define MOSFET_SIMULATION_PROGRAM_1_OUTPUTSIMULATION_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include "../MOSFET/MOSFET.h"
#include "../Level1/Level1Calculation.h"
#include "../Level2/Level2Calculation.h"
#include "../Level3/Level3Calculation.h"
#include "../Level4/Level4Calculation.h"
#include "../Level5/Level5Calculation.h"
#include "../Level6/Level6Calculation.h"
#include "../Support/STRING_TO_WIDECHAR.h"
#include "../Support/Plot/supportLib.h"

class OutputSimulation {
public:
    OutputSimulation(MOSFET &mosfet_par, double Vmin_var, double Vmax_var, double Vstep_var, const std::vector<double> &params_Vgs);
    const std::unordered_map<double,std::vector<double>> &getParams_Vgs_Ids() const;
    //SIMULATION
    void GenerateOutputCurve(int COMPLEXITY);
    void GraphOutputCurve(int COMPLEXITY);

    void writeMapToFile(const std::unordered_map<double, std::vector<double>>& map, const std::string& filename);

private:
    MOSFET mosfet_;
    double Vmin_, Vmax_, Vstep_;
    std::unordered_map<double,std::vector<double>> Params_Vgs_Ids_;
    std::vector<double> Params_Vds_;

};


#endif //MOSFET_SIMULATION_PROGRAM_1_OUTPUTSIMULATION_H
