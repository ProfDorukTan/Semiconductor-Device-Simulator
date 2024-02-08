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




