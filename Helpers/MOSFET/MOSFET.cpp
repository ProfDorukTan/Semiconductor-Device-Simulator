//
// Created by Doruk Tan Atila on 10/29/23.
//

#include "MOSFET.h"

MOSFET::MOSFET() {}

MOSFET::MOSFET(std::string Name, char type, double vt, double mobility, double cox, double w, double l) :
        name(Name), Vt(vt), Mobility(mobility), Cox(cox), ChannelWidth(w), ChannelLength(l){
    setType(type);
}
MOSFET::MOSFET(std::string Name, char type, double vt, double mobility, double cox, double w, double l, double lambda) :
         name(Name), Vt(vt), Mobility(mobility), Cox(cox), ChannelWidth(w), ChannelLength(l), Lambda(lambda) {
    setType(type);
}

MOSFET::MOSFET(std::string name, char type, double mobility, double w, double l,
    double metalWorkFunction, double semiconductorBandgap, double semiconductorElectronAffinity, double semiconductorDopingConcentration, double semiconductorPermittivity,
    double oxideThickness, double oxidePermittivity, double oxideTrappedCharge,
    double temperature, double effectiveDensityOfStatesInConductionBand, double effectiveDensityOfStatesInValenceBand)
{
	setName(name);
	setType(type);
	setMobility(mobility);
	setChannelWidth(w);
	setChannelLength(l);
   	setMetalWorkFunction(metalWorkFunction);
    setSemiconductorBandgap(semiconductorBandgap);
    setSemiconductorElectronAffinity(semiconductorElectronAffinity);
    setSemiconductorDopingConcentrationn(semiconductorDopingConcentration);
    setSemiconductorPermittivity(semiconductorPermittivity);
    setEffectiveDensityOfStatesInConductionBand(effectiveDensityOfStatesInConductionBand);
    setEffectiveDensityOfStatesInValenceBand(effectiveDensityOfStatesInValenceBand);
    setOxideThickness(oxideThickness);
    setOxidePermittivity(oxidePermittivity);
    setOxideTrappedCharge(oxideTrappedCharge);
    setTemperature(temperature);
}

//GETTER & SETTER FUNCTIONS for the class
std::vector<MOSFET*>& MOSFET::getMosfets() {
    return mosfets;
}
const std::string &MOSFET::getName() const {
    return name;
}
void MOSFET::setName(const std::string &name) {
    MOSFET::name = name;
}
char MOSFET::getType() const {
    return type;
}
void MOSFET::setType(char type) {
    if(type == 'N' || type == 'n'){
        this->type = 'N';
    }else if(type == 'P' || type == 'p') {
        this->type = 'P';
    }else{
        throw std::invalid_argument("Invalid MOSFET type. Type must be 'N' or 'P'.");
    }
}
double MOSFET::getVt() const {
    return MOSFET::Vt;
}
void MOSFET::setVt(double vt) {
    MOSFET::Vt = vt;
}
double MOSFET::getMobility() const {
    return MOSFET::Mobility;
}
void MOSFET::setMobility(double mobility) {
    MOSFET::Mobility = mobility;
}
double MOSFET::getCox() const {
    return MOSFET::Cox;
}
void MOSFET::setCox(double cox) {
    MOSFET::Cox = cox;
}
double MOSFET::getChannelWidth() const {
    return MOSFET::ChannelWidth;
}
void MOSFET::setChannelWidth(double channelWidth) {
    MOSFET::ChannelWidth = channelWidth;
}
double MOSFET::getChannelLength() const {
    return MOSFET::ChannelLength;
}
void MOSFET::setChannelLength(double channelLength) {
    MOSFET::ChannelLength = channelLength;
}
double MOSFET::getLambda() const {
    return MOSFET::Lambda;
}
void MOSFET::setLambda(double lambda) {
    MOSFET::Lambda = lambda;
}
double MOSFET::getMetalWorkFunction() const
{
    return MOSFET::MetalWorkFunction;
}
void MOSFET::setMetalWorkFunction(double MetalWorkFunction)
{
    MOSFET::MetalWorkFunction = MetalWorkFunction;
}
double MOSFET::getSemiconductorBandgap() const
{
	return MOSFET::SemiconductorBandgap;
}
void MOSFET::setSemiconductorBandgap(double SemiconductorBandgap)
{
    MOSFET::SemiconductorBandgap = SemiconductorBandgap;
}
double MOSFET::getSemiconductorElectronAffinity() const
{
	return MOSFET::SemiconductorElectronAffinity;
}
void MOSFET::setSemiconductorElectronAffinity(double SemiconductorElectronAffinity)
{
    MOSFET::SemiconductorElectronAffinity = SemiconductorElectronAffinity;
}
double MOSFET::getSemiconductorDopingConcentration() const
{
	return MOSFET::SemiconductorDopingConcentration;
}
void MOSFET::setSemiconductorDopingConcentrationn(double DopingConcentration)
{
	MOSFET::SemiconductorDopingConcentration = DopingConcentration;
}
double MOSFET::getSemiconductorPermittivity() const
{
	return MOSFET::SemiconductorPermittivity;
}
void MOSFET::setSemiconductorPermittivity(double SemiconductorPermittivity)
{
    MOSFET::SemiconductorPermittivity = SemiconductorPermittivity;
}
double MOSFET::getOxideThickness() const
{
	return MOSFET::OxideThickness;
}
void MOSFET::setOxideThickness(double OxideThickness)
{
	MOSFET::OxideThickness = OxideThickness;
}
double MOSFET::getOxidePermittivity() const
{
	return MOSFET::OxidePermittivity;
}
void MOSFET::setOxidePermittivity(double OxidePermittivity)
{
	MOSFET::OxidePermittivity = OxidePermittivity;
}
double MOSFET::getOxideTrappedCharge() const
{
	return MOSFET::OxideTrappedCharge;
}
void MOSFET::setOxideTrappedCharge(double OxideTrappedCharge)
{
	MOSFET::OxideTrappedCharge = OxideTrappedCharge;
}
double MOSFET::getTemperature() const
{
	return MOSFET::Temperature;
}
void MOSFET::setTemperature(double Temperature)
{
	MOSFET::Temperature = Temperature;
}
double MOSFET::getEffectiveDensityOfStatesInConductionBand() const
{
	return MOSFET::EffectiveDensityOfStatesInConductionBand;
}
void MOSFET::setEffectiveDensityOfStatesInConductionBand(double EffectiveDensityOfStatesInConductionBand)
{
	MOSFET::EffectiveDensityOfStatesInConductionBand = EffectiveDensityOfStatesInConductionBand;
}
double MOSFET::getEffectiveDensityOfStatesInValenceBand() const
{
	return MOSFET::EffectiveDensityOfStatesInValenceBand;
}
void MOSFET::setEffectiveDensityOfStatesInValenceBand(double EffectiveDensityOfStatesInValenceBand)
{
	MOSFET::EffectiveDensityOfStatesInValenceBand = EffectiveDensityOfStatesInValenceBand;
}



// Definition of the static member variable
std::vector<MOSFET*> MOSFET::mosfets;
void MOSFET::addMOSFET(MOSFET *mosfet) {
    mosfets.push_back(mosfet);
}

MOSFET *MOSFET::getMOSFETByName(const std::string &name) {
    for (const auto& mosfet : mosfets) {
        if (mosfet->getName() == name) {
            return mosfet;
        }
    }
    return nullptr;
}

void MOSFET::clearMosfets() {
    for (MOSFET* mosfet : mosfets) {
        delete mosfet;
    }
    mosfets.clear();
}




