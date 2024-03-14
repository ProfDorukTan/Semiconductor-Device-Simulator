//
// Created by Doruk Tan Atila on 29/02/24.
//

#include "Level3Calculation.h"
double Vth_calc(MOSFET mosfet) {
    char type = mosfet.getType();
    double phi_m = mosfet.getMetalWorkFunction(), Eg_s = mosfet.getSemiconductorBandgap(),
		chi_s = mosfet.getSemiconductorElectronAffinity(), N_s = mosfet.getSemiconductorDopingConcentration(),
		epsilon_s = mosfet.getSemiconductorPermittivity(), t_ox = mosfet.getOxideThickness(),
		epsilon_ox = mosfet.getOxidePermittivity(), Q_ox = mosfet.getOxideTrappedCharge(), 
        temperature = mosfet.getTemperature(), N_c = mosfet.getEffectiveDensityOfStatesInConductionBand(), N_v = mosfet.getEffectiveDensityOfStatesInValenceBand();
    double Vth;

    double n_i = sqrt(N_c * N_v * pow(EULERS_NUMBER, (-1 * Eg_s) / (BOLTZMANN_CONSTANT * temperature)));

    if (type == 'N') {
        double phi_fn = (BOLTZMANN_CONSTANT * temperature / ELEMENTARY_CHARGE) * log(N_s / n_i);
		Vth = phi_m - (Eg_s / (2 * ELEMENTARY_CHARGE) + phi_fn + chi_s) + 2 * phi_fn + ((t_ox / epsilon_ox) * sqrt(ELEMENTARY_CHARGE * N_s * 4 * epsilon_s * phi_fn));
	}
    else if (type == 'P') {
        double phi_fp = (BOLTZMANN_CONSTANT * temperature / ELEMENTARY_CHARGE) * log(N_s / n_i);
        Vth = phi_m - (Eg_s / (2 * ELEMENTARY_CHARGE) + phi_fp + chi_s) + 2 * phi_fp + ((t_ox / epsilon_ox) * sqrt(ELEMENTARY_CHARGE * N_s * 4 * epsilon_s * phi_fp));
    }
    return Vth;
}

double level3_calc(MOSFET mosfet , double Vgs , double Vds, double Vt) {
    char type = mosfet.getType();
    double mobility = mosfet.getMobility(), Cox = mosfet.getCox(),
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

void level3_sweep(MOSFET mosfet , std::unordered_map<double , std::vector<double>>& Vgs_Ids_vector , std::vector<double> Vds_vector) {
    // Iterate vgs values
    double Vth = Vth_calc(mosfet);
    for (const auto vgs_Ids_pair : Vgs_Ids_vector)
    {
        double vgs = vgs_Ids_pair.first;
        // Iterate vds values
        for (const auto vds : Vds_vector)
        {
            Vgs_Ids_vector[vgs].push_back(level3_calc(mosfet , vgs , vds, Vth));
        }
    }
}