#pragma once

#include <QMessageBox>
#include <QCloseEvent>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <fstream>

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QSettings>

#include "ui_SemiconductorDeviceSimulatorDTA.h"

#include "Helpers/MOSFET/MOSFET.h"
#include "Helpers/Simulations/OutputSimulation.h"
#include "Helpers/Support/json.hpp"

class SemiconductorDeviceSimulatorDTA : public QMainWindow
{
    Q_OBJECT

public:
    SemiconductorDeviceSimulatorDTA(QWidget *parent = nullptr);
    ~SemiconductorDeviceSimulatorDTA();

private:
    Ui::SemiconductorDeviceSimulatorDTAClass *ui;

    QList<MOSFET*> loadMosfets(const QString& level);
    void saveMosfets(const QString& level);
    void saveMosfet(const MOSFET& mosfet, const QString& level);

    void on_SaveMOSFETs_clicked();
    void on_LoadMOSFETs_clicked();
    void updateUIWithLoadedMOSFETs();
    void on_DeleteMosfetButton_clicked();

    void on_SaveMosfetLevel1_clicked();
    void on_SaveMosfetLevel2_clicked();
    void on_SaveMosfetLevel3_clicked();

    //Output Simulation
    void on_AddVgs_clicked();
    void on_DeleteVgs_clicked();
    void on_OutputSimulateButton_clicked();
};
