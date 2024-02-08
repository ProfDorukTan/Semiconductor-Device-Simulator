//
// Created by Doruk Tan Atila on 10/29/23.
//

#ifndef MAIN_CPP_DRAWPLOT_H
#define MAIN_CPP_DRAWPLOT_H


#include <iomanip>
#include "../Support/Plot/pbPlots.h"
#include "../Parameters/Parameters.h"
#include <wchar.h>
#include <sstream>
#include "../Support/STRING_TO_WIDECHAR.h"
#include "../Support/Plot/supportLib.h"

//The function will read & graph a txt file in columnar format: x|y1|y2|y3...
void TabularReadGraph(std::string filename, std::vector<double> titleVector, std::vector<std::vector<double> > MeasurementData);
//The function will graph data in columnar vector format: x|y1|y2|y3...
void ManualGraph(std::string titlevar, std::vector<std::vector<double> > MeasurementData);


#endif //MAIN_CPP_DRAWPLOT_H