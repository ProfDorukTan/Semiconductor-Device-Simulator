//
// Created by Doruk Tan Atila on 11/15/23.
//

#include "CompareCurves.h"

double CompareCurves(const std::vector<std::vector<double>> &x_vector, const std::vector<std::vector<double>> &y1_vector,
                   const std::vector<std::vector<double>> &y2_vector) {

    // Iterate through each pair of curves
    size_t i;
    double similarity;
    for (i = 0; i < x_vector.size(); ++i) {
        if (y1_vector[i].size() != x_vector[i].size() || y2_vector[i].size() != x_vector[i].size()) {
//            std::cout << x_vector[i].size() <<" / "<< y1_vector[i].size() << " / "<<y2_vector[i].size() << " / " << std::endl;
            std::cerr << "Error: Mismatch in sizes of x, y1, and y2 vectors for curve " << i << std::endl;
            continue;
        }

        // Call your CompareFunction for each pair of curves
        similarity = CompareFunction(x_vector[i], y1_vector[i], y2_vector[i]);

        // Print or use the similarity measure as needed
        //std::cout << "Similarity measure for curve " << i << ": " << similarity << std::endl;
    }
    return similarity;

}

double CompareFunction(const std::vector<double>& x, const std::vector<double>& y1, const std::vector<double>& y2) {

    // Initialize the total percent difference
    double totalPercentDifference = 0.0;
    double percentDifference;
    // Iterate through each point in the vectors
    for (size_t i = 0; i < x.size(); ++i) {
        // Calculate the percent difference for the current point
        if(y1[i] != 0 || y2[i] != 0){
            percentDifference = std::abs(y1[i] - y2[i]) / ((y1[i] + y2[i]) / 2.0);
        }else{
            percentDifference = 0;
        }


        // Add the percent difference to the total
        totalPercentDifference += percentDifference;
    }

    // Calculate the mean percent difference
    double meanPercentDifference = totalPercentDifference / static_cast<double>(x.size());

    return meanPercentDifference;
}

