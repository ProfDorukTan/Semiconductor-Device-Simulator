//
// Created by Doruk Tan Atila on 10/29/23.
//

#include "MOSFET.h"

MOSFET::MOSFET() {}

MOSFET::MOSFET(std::string Name, char type, double vt, double mobility, double cox, double w, double l) :
        name(Name), Vt(vt), mobility(mobility), Cox(cox), ChannelWidth(w), ChannelLength(l){
    setType(type);
}
MOSFET::MOSFET(std::string Name, char type, double vt, double mobility, double cox, double w, double l, double lambda) :
         name(Name), Vt(vt), mobility(mobility), Cox(cox), ChannelWidth(w), ChannelLength(l), Lambda(lambda) {
    setType(type);
}

MOSFET::MOSFET(std::string name, char type, double mobility, double cox, double w, double l,
    double metalWorkFunction, double semiconductorBandgap, double semiconductorElectronAffinity, double semiconductorDopingConcentration, double semiconductorPermittivity,
    double oxideThickness, double oxidePermittivity, double oxideTrappedCharge,
    double temperature, double electronEffectiveMass, double holeEffectiveMass)
{
	setName(name);
	setType(type);
	setMobility(mobility);
	setCox(cox);
	setChannelWidth(w);
	setChannelLength(l);
   	setMetalWorkFunction(metalWorkFunction);
    setSemiconductorBandgap(semiconductorBandgap);
    setSemiconductorElectronAffinity(semiconductorElectronAffinity);
    setSemiconductorDopingConcentrationn(semiconductorDopingConcentration);
    setSemiconductorPermittivity(semiconductorPermittivity);
    setOxideThickness(oxideThickness);
    setOxidePermittivity(oxidePermittivity);
    setOxideTrappedCharge(oxideTrappedCharge);

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
double MOSFET::getTempK() const {
    return tempK;
}
void MOSFET::setTempK(double tempK) {
    MOSFET::tempK = tempK;
}
double MOSFET::getVt() const {
    return Vt;
}
void MOSFET::setVt(double vt) {
    Vt = vt;
}
double MOSFET::getMobility() const {
    return mobility;
}
void MOSFET::setMobility(double mobility) {
    MOSFET::mobility = mobility;
}
double MOSFET::getCox() const {
    return Cox;
}
void MOSFET::setCox(double cox) {
    Cox = cox;
}
double MOSFET::getChannelWidth() const {
    return ChannelWidth;
}
void MOSFET::setChannelWidth(double channelWidth) {
    ChannelWidth = channelWidth;
}
double MOSFET::getChannelLength() const {
    return ChannelLength;
}
void MOSFET::setChannelLength(double channelLength) {
    ChannelLength = channelLength;
}
double MOSFET::getLambda() const {
    return Lambda;
}
void MOSFET::setLambda(double lambda) {
    Lambda = lambda;
}
double MOSFET::getMetalWorkFunction() const
{
    return metalWorkFunction;
}
void MOSFET::setMetalWorkFunction(double MetalWorkFunction)
{
	MetalWorkFunction = metalWorkFunction;
}
double MOSFET::getSemiconductorBandgap() const
{
	return semiconductorBandgap;
}
void MOSFET::setSemiconductorBandgap(double SemiconductorBandgap)
{
	SemiconductorBandgap = semiconductorBandgap;
}
double MOSFET::getSemiconductorElectronAffinity() const
{
	return semiconductorElectronAffinity;
}
void MOSFET::setSemiconductorElectronAffinity(double SemiconductorElectronAffinity)
{
	SemiconductorElectronAffinity = semiconductorElectronAffinity;
}
double MOSFET::getSemiconductorDopingConcentration() const
{
	return semiconductorDopingConcentration;
}
void MOSFET::setSemiconductorDopingConcentrationn(double DopingConcentration)
{
	DopingConcentration = semiconductorDopingConcentration;
}
double MOSFET::getSemiconductorPermittivity() const
{
	return semiconductorPermittivity;
}
void MOSFET::setSemiconductorPermittivity(double SemiconductorPermittivity)
{
	SemiconductorPermittivity = semiconductorPermittivity;
}
double MOSFET::getOxideThickness() const
{
	return oxideThickness;
}
void MOSFET::setOxideThickness(double OxideThickness)
{
	OxideThickness = oxideThickness;
}
double MOSFET::getOxidePermittivity() const
{
	return oxidePermittivity;
}
void MOSFET::setOxidePermittivity(double OxidePermittivity)
{
	OxidePermittivity = oxidePermittivity;
}
double MOSFET::getOxideTrappedCharge() const
{
	return oxideTrappedCharge;
}
void MOSFET::setOxideTrappedCharge(double OxideTrappedCharge)
{
	OxideTrappedCharge = oxideTrappedCharge;
}
double MOSFET::getTemperature() const
{
	return temperature;
}
void MOSFET::setTemperature(double Temperature)
{
	Temperature = temperature;
}
double MOSFET::getElectronEffectiveMass() const
{
	return electronEffectiveMass;
}
void MOSFET::setElectronEffectiveMass(double ElectronEffectiveMass)
{
	ElectronEffectiveMass = electronEffectiveMass;
}
double MOSFET::getHoleEffectiveMass() const
{
	return holeEffectiveMass;
}
void MOSFET::setHoleEffectiveMass(double HoleEffectiveMass)
{
	HoleEffectiveMass = holeEffectiveMass;
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




