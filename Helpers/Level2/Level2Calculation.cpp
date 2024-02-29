//
// Created by Doruk Tan Atila on 10/29/23.
//

#include "Level2Calculation.h"

double level2_calc(MOSFET mosfet, double Vgs, double Vds) {
    char type = mosfet.getType();
    double Vt = mosfet.getVt(), mobility = mosfet.getMobility(), Cox = mosfet.getCox(),
            W = mosfet.getChannelWidth(), L = mosfet.getChannelLength(), Lambda = mosfet.getLambda();

    if(Vgs < Vt){
        return 0;
    }else if(Vds <= Vgs - Vt){
        return (mobility*Cox*(W/L)*((Vgs-Vt)*Vds-(pow(Vds,2)/2))*(1+(Lambda*Vds)));
    }else if(Vds > Vgs - Vt){
        return (mobility*Cox*(W/L)/2*(pow((Vgs-Vt),2))*(1+(Lambda*Vds)));
    }
}

void level2_sweep(MOSFET mosfet, std::unordered_map<double, std::vector<double>>& Vgs_Ids_vector, std::vector<double> Vds_vector) {
    // Iterate vgs values
    for (const auto vgs_Ids_pair : Vgs_Ids_vector)
    {
        double vgs = vgs_Ids_pair.first;
        // Iterate vds values
        for (const auto vds : Vds_vector)
        {
            Vgs_Ids_vector[vgs].push_back(level2_calc(mosfet, vgs, vds));
        }
    }
}