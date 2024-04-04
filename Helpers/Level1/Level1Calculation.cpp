//
// Created by Doruk Tan Atila on 10/29/23.
//


#include "Level1Calculation.h"

double level1_calc(MOSFET mosfet, double Vgs , double Vds) {
    char type = mosfet.getType();
    double Vt = mosfet.getVt() , mobility = mosfet.getMobility() , Cox = mosfet.getCox() ,
    W = mosfet.getChannelWidth() , L = mosfet.getChannelLength();
    if (type == 'N') {
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
	else if (type == 'P') {
		if (Vgs > Vt) {
			return 0;
		}
		else if (Vds >= Vgs - Vt) {
			return (mobility * Cox * (W / L) * ((Vgs - Vt) * Vds - (pow(Vds , 2) / 2)));
		}
		else if (Vds < Vgs - Vt) {
			return (mobility * Cox * (W / L) / 2 * (pow((Vgs - Vt) , 2)));
		}
	}
	return 0;
   
}

void level1_sweep(MOSFET mosfet, std::unordered_map<double, std::vector<double>> &Vgs_Ids_vector, std::vector<double> Vds_vector){
    // Iterate vgs values
    for (const auto vgs_Ids_pair : Vgs_Ids_vector)
    {
        double vgs = vgs_Ids_pair.first;
        // Iterate vds values
        for (const auto vds : Vds_vector)
        {
            Vgs_Ids_vector[vgs].push_back(level1_calc(mosfet, vgs, vds));
        }
    }
}