//
// Created by Doruk Tan Atila on 29/02/24.
//

#include "Level3Calculation.h"
void Vth_calc(MOSFET mosfet) {
    char type = mosfet.getType();
    double phi_m = mosfet.getMetalWorkFunction(), Eg_s = mosfet.getSemiconductorBandgap(),
		chi_s = mosfet.getSemiconductorElectronAffinity(), N_s = mosfet.getSemiconductorDopingConcentration(),
		epsilon_s = mosfet.getSemiconductorPermittivity(), t_ox = mosfet.getOxideThickness(),
		epsilon_ox = mosfet.getOxidePermittivity(), Q_ox = mosfet.getOxideTrappedCharge();
    double Vth;
    //CONTINUE

}

double level3_calc(double Vgs, double Vds, MOSFET mosfet){
    char type = mosfet.getType();
    double Vt = mosfet.getVt(), mobility = mosfet.getMobility(), Cox = mosfet.getCox(),
        W = mosfet.getChannelWidth(), L = mosfet.getChannelLength();
    if (type == 'n') {
        if (Vgs < Vt) {
            return 0;
        }
        else if (Vds <= Vgs - Vt) {
            return (mobility * Cox * (W / L) * ((Vgs - Vt) * Vds - (pow(Vds , 2) / 2)));
        }
        else if (Vds > Vgs - Vt) {
            return (mobility * Cox * (W / L) / 2 * (pow((Vgs - Vt) , 2)));
        }
    }
}