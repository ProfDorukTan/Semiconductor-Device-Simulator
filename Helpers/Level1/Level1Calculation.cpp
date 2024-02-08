//
// Created by Doruk Tan Atila on 10/29/23.
//

#include "Level1Calculation.h"
double level1_calc(double Vgs, double Vds, MOSFET mosfet){
    char type = mosfet.getType();
    double Vt = mosfet.getVt(), mobility = mosfet.getMobility(), Cox = mosfet.getCox(),
        W = mosfet.getChannelWidth(), L = mosfet.getChannelLength();

    if(Vgs < Vt){
        return 0;
    }else if(Vds <= Vgs - Vt){
        return (mobility*Cox*(W/L)*((Vgs-Vt)*Vds-(pow(Vds,2)/2)));
    }else if(Vds > Vgs - Vt){
        return (mobility*Cox*(W/L)/2*(pow((Vgs-Vt),2)));
    }
}