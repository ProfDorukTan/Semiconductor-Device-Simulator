//
// Created by Doruk Tan Atila on 10/29/23.
//

#ifndef MAIN_CPP_LEVEL3CALCULATION_H
#define MAIN_CPP_LEVEL3CALCULATION_H

#include <cmath>
#include <unordered_map>
#include <vector>
#include "../Support/DrawPlot.h"
#include "../Parameters/Parameters.h"
#include "../MOSFET/MOSFET.h"

void Vth_calc(MOSFET &mosfet);
void Cox_calc(MOSFET &mosfet);
double level3_calc(MOSFET &mosfet , double Vgs , double Vds , double Vt);
void level3_sweep_output(MOSFET &mosfet , std::unordered_map<double , std::vector<double>>& Vgs_Ids_vector , std::vector<double> Vds_vector);
void level3_sweep_transfer(MOSFET &mosfet , std::unordered_map<double , std::vector<double>>& Vds_Ids_vector , std::vector<double> Vgs_vector);

#endif //MAIN_CPP_LEVEL3CALCULATION_H
