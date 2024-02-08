//
// Created by Doruk Tan Atila on 10/29/23.
//

#include "Level2Calculation.h"

double level2_calc(double Vgs, double Vds, MOSFET mosfet){
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