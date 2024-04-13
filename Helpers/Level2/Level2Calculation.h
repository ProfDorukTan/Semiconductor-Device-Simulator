//
// Created by Doruk Tan Atila on 10/29/23.
//

#ifndef MAIN_CPP_LEVEL2CALCULATION_H
#define MAIN_CPP_LEVEL2CALCULATION_H

#include <cmath>
#include <unordered_map>
#include <vector>
#include "../Support/DrawPlot.h"
#include "../Parameters/Parameters.h"
#include "../MOSFET/MOSFET.h"

double level2_calc(MOSFET mosfet, double Vgs, double Vds);
void level2_sweep_output(MOSFET mosfet, std::unordered_map<double, std::vector<double>>& Vgs_Ids_vector, std::vector<double> Vds_vector);
void level2_sweep_transfer(MOSFET mosfet, std::unordered_map<double, std::vector<double>>& Vds_Ids_vector, std::vector<double> Vgs_vector);
#endif //MAIN_CPP_LEVEL2CALCULATION_H
