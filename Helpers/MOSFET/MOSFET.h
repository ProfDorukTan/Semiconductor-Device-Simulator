//
// Created by Doruk Tan Atila on 10/29/23.
//

#ifndef MAIN_CPP_MOSFET_H
#define MAIN_CPP_MOSFET_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "../Parameters/Parameters.h"
#include "../Support/DataReader.h"
#include "../Support/DrawPlot.h"
#include "../Support/STRING_TO_WIDECHAR.h"

class MOSFET {
public:
    MOSFET();
    MOSFET(std::string name, char type, double vt, double mobility, double cox, double w, double l);
    MOSFET(std::string name, char type, double vt, double mobility, double cox, double w, double l, double lambda);
    MOSFET(std::string name, char type, double mobility, double cox, double w, double l,
        double metalWorkFunction, double semiconductorBandgap, double semiconductorElectronAffinity, double semiconductorDopingConcentration, double semiconductorPermittivity,
        double oxideThickness, double oxidePermittivity, double oxideTrappedCharge);

    //Static methods for managing instances - For multiple objects
    static void addMOSFET(MOSFET* mosfet);
    static MOSFET* getMOSFETByName(const std::string& name);
    static void clearMosfets();

    //GETTER & SETTER FUNCTIONS
    static std::vector<MOSFET*>& getMosfets();
    const std::string &getName() const;
    void setName(const std::string &name);
    char getType() const;
    void setType(char type);
    double getTempK() const;
    void setTempK(double tempK);
    double getVt() const;
    void setVt(double vt);
    double getMobility() const;
    void setMobility(double mobility);
    double getCox() const;
    void setCox(double cox);
    double getChannelWidth() const;
    void setChannelWidth(double channelWidth);
    double getChannelLength() const;
    void setChannelLength(double channelLength);
    double getLambda() const;
    void setLambda(double lambda);
    double getMetalWorkFunction() const;
    void setMetalWorkFunction(double metalWorkFunction);
    double getSemiconductorBandgap() const;
    void setSemiconductorBandgap(double semiconductorBandgap);
    double getSemiconductorElectronAffinity() const;
    void setSemiconductorElectronAffinity(double semiconductorElectronAffinity);
    double getSemiconductorDopingConcentration() const;
    void setSemiconductorDopingConcentrationn(double dopingConcentration);
    double getSemiconductorPermittivity() const;
    void setSemiconductorPermittivity(double semiconductorPermittivity);
    double getOxideThickness() const;
    void setOxideThickness(double oxideThickness);
    double getOxidePermittivity() const;
    void setOxidePermittivity(double oxidePermittivity);
    double getOxideTrappedCharge() const;
    void setOxideTrappedCharge(double oxideTrappedCharge);

private:
    // Static vector to store instances
    static std::vector<MOSFET*> mosfets;
    //Minimum required parameters for level1 simulation
    std::string name;
    char type;
    double tempK;
    double Vt;
    double mobility;
    double Cox;
    double ChannelWidth;
    double ChannelLength;

    //Parameters for Vt calculation
    double metalWorkFunction;
    double semiconductorBandgap;
    double semiconductorElectronAffinity;  
    double semiconductorDopingConcentration;
    double semiconductorPermittivity;
    double oxideThickness;
    double oxidePermittivity;
    double oxideTrappedCharge;
    
    //Additional required parameters for level2 simulation
    double Lambda;  //Channel length modulation parameter - empirical
};


#endif //MAIN_CPP_MOSFET_H
