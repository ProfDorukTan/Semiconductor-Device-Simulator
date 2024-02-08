//
// Created by Doruk Tan Atila on 11/15/23.
//

#ifndef MAIN_CPP_COMPARECURVES_H
#define MAIN_CPP_COMPARECURVES_H
#include <math.h>
#include <vector>
#include <iostream>
#include <string.h>

double CompareCurves(const std::vector<std::vector<double>>& x_vector,
                   const std::vector<std::vector<double>>& y1_vector,
                   const std::vector<std::vector<double>>& y2_vector);

double CompareFunction(const std::vector<double>& x, const std::vector<double>& y1, const std::vector<double>& y2);

#endif //MAIN_CPP_COMPARECURVES_H
