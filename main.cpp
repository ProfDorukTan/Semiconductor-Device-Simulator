#include "SemiconductorDeviceSimulatorDTA.h"
#include <QtWidgets/QApplication>
#include "Helpers/MOSFET/MOSFET.h"
#include "Helpers/Simulations/OutputSimulation.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SemiconductorDeviceSimulatorDTA w;
    w.show();
    return a.exec();
}
