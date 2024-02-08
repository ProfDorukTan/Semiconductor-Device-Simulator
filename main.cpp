#include "SemiconductorDeviceSimulatorDTA.h"
#include <QtWidgets/QApplication>
#include "Helpers/MOSFET/MOSFET.h"
#include "Helpers/Simulations/OutputSimulation.h"
int main(int argc, char *argv[])
{

//  MOSFET doruk("M1", 'N', 0.7, 0.1, 1.0, 1.0, 1.0);  
//  std::vector<double> vgs = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
//  OutputSimulation outputSimulation(doruk, 0, 10, 0.1, vgs);
//  outputSimulation.GraphOutputCurve(1);

    QApplication a(argc, argv);
    SemiconductorDeviceSimulatorDTA w;
    w.show();
    return a.exec();
}
