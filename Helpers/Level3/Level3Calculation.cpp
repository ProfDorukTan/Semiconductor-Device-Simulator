//
// Created by Doruk Tan Atila on 29/02/24.
//

#include "Level3Calculation.h"
void Vth_calc(MOSFET &mosfet) {
    char type = mosfet.getType();
    double phi_m = mosfet.getMetalWorkFunction(), Eg_s = mosfet.getSemiconductorBandgap(),
		chi_s = mosfet.getSemiconductorElectronAffinity(), N_s = mosfet.getSemiconductorDopingConcentration(),
		epsilon_s = mosfet.getSemiconductorPermittivity(), t_ox = mosfet.getOxideThickness(),
		epsilon_ox = mosfet.getOxidePermittivity(), Q_ox = mosfet.getOxideTrappedCharge(), 
        temperature = mosfet.getTemperature(), N_c = mosfet.getEffectiveDensityOfStatesInConductionBand(), N_v = mosfet.getEffectiveDensityOfStatesInValenceBand();
    double Vth;
    
    double n_i = sqrt(N_c * N_v * pow((temperature/ROOM_TEMPERATURE), 3) * pow(EULERS_NUMBER, ((-1 * Eg_s) / ((THERMAL_VOLTAGE_ROOM_TEMPERATURE * (temperature / ROOM_TEMPERATURE))))));

    double phi_f_shift = THERMAL_VOLTAGE_ROOM_TEMPERATURE * log(N_s / n_i);
    if (type == 'P') {
		phi_f_shift = -1 * phi_f_shift;
	}
    double phi_ms = phi_m - ((Eg_s / (2)) + phi_f_shift + chi_s);
    double space_charge = sqrt(abs(4 * epsilon_s * VACUUM_PERMITTIVITY * phi_f_shift / (ELEMENTARY_CHARGE * N_s)));
    double V_ox = ((t_ox / (epsilon_ox * VACUUM_PERMITTIVITY)) * (abs(ELEMENTARY_CHARGE * N_s * space_charge) - (Q_ox * ELEMENTARY_CHARGE)));
    
    Vth = phi_ms + 2 * phi_f_shift + V_ox;
    
    mosfet.setVt(Vth);
}
void Cox_calc(MOSFET &mosfet) {
	double epsilon_ox = mosfet.getOxidePermittivity(), t_ox = mosfet.getOxideThickness();
	mosfet.setCox((epsilon_ox * VACUUM_PERMITTIVITY) / t_ox);
}

double level3_calc(MOSFET &mosfet , double Vgs , double Vds, double Vt) {
    char type = mosfet.getType();
    double mobility = mosfet.getMobility(), Cox = mosfet.getCox(),
        W = mosfet.getChannelWidth(), L = mosfet.getChannelLength();
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
    else if (type == 'P') {// FIXME: Check the equations
		if (Vgs < abs(Vt)) {
			return 0;
		}
		else if (Vds <= abs(Vgs - Vt)) {
			return -1 * (mobility * Cox * (W / L) * ((Vgs - Vt) * Vds - (pow(Vds , 2) / 2)));
		}
		else if (Vds > abs(Vgs - Vt)) {
			return -1 * (mobility * Cox * (W / L) / 2 * (pow((Vgs - Vt) , 2)));
		}
	}
}

void level3_sweep_output(MOSFET &mosfet , std::unordered_map<double , std::vector<double>>& Vgs_Ids_vector , std::vector<double> Vds_vector) {
    // Iterate vgs values
    Vth_calc(mosfet);
    Cox_calc(mosfet);
    for (const auto vgs_Ids_pair : Vgs_Ids_vector)
    {
        double vgs = vgs_Ids_pair.first;
        // Iterate vds values
        for (const auto vds : Vds_vector)
        {
            Vgs_Ids_vector[vgs].push_back(level3_calc(mosfet , vgs , vds, mosfet.getVt()));
        }
    }
}

void level3_sweep_transfer(MOSFET &mosfet , std::unordered_map<double , std::vector<double>>& Vds_Ids_vector , std::vector<double> Vgs_vector) {
    // Iterate vgs values
    Vth_calc(mosfet);
    Cox_calc(mosfet);
    for (const auto vds_Ids_pair : Vds_Ids_vector)
    {
        double vds = vds_Ids_pair.first;
        // Iterate vds values
        for (const auto vgs : Vgs_vector)
        {
            Vds_Ids_vector[vds].push_back(level3_calc(mosfet , vgs , vds, mosfet.getVt()));
        }
    }
}