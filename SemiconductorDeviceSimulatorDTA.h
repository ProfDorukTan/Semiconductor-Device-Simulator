#pragma once

#include <QMessageBox>
#include <QCloseEvent>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QFileInfoList>
#include <QCheckBox>

#include <fstream>

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QSettings>

#include "ui_SemiconductorDeviceSimulatorDTA.h"

#include "Helpers/Parameters/Parameters.h"
#include "Helpers/Support/json.hpp"
#include "Helpers/MOSFET/MOSFET.h"
#include "Helpers/Simulations/OutputSimulation.h"
#include "Helpers/Simulations/TransferSimulation.h"




class SemiconductorDeviceSimulatorDTA : public QMainWindow
{
    Q_OBJECT

public:
    SemiconductorDeviceSimulatorDTA(QWidget *parent = nullptr);
    ~SemiconductorDeviceSimulatorDTA();

private:
    Ui::SemiconductorDeviceSimulatorDTAClass *ui;

    //Functions for external save and loads
    void on_SaveMOSFETs_clicked();
    void on_LoadMOSFETs_clicked();
    void updateUIWithLoadedMOSFETs();
    void on_DeleteMosfetButton_clicked();

    //Functions for MOSFET save and loads in the UI
    void on_SaveMosfetLevel1_clicked();
    void on_SaveMosfetLevel2_clicked();
    void on_SaveMosfetLevel3_clicked();

    //Output Simulation
    void on_AddVgs_clicked();
    void on_DeleteVgs_clicked();
    void on_OutputSimulateButton_clicked();

    //Transfer Simulation
    void on_AddVds_clicked();
    void on_DeleteVds_clicked();
    void on_TransferSimulateButton_clicked();

    //Functions for parameter preloading
    void on_LoadMetal_clicked();
    void on_LoadSemiconductor_clicked();

    //Functions for displaying the simulation results
    //This class is used to display images in a popup dialog - it is used to display the simulation results
    class ImagePopupDialog : public QDialog {
    public:
        ImagePopupDialog(QWidget* parent = nullptr) : QDialog(parent) {
            setWindowTitle("Simulation Result");
            QVBoxLayout* layout = new QVBoxLayout(this);
            imageLabel = new QLabel(this);
            layout->addWidget(imageLabel);
        }

        void setImage(const QPixmap& pixmap) {
            imageLabel->setPixmap(pixmap);
            imageLabel->setScaledContents(true);
            adjustSize();
        }

    private:
        QLabel* imageLabel;
    };

    //This function is used to find the latest image in a directory - it is used to display the latest simulation result
    QString findLatestImage(const QString& directoryPath) {
        QDir directory(directoryPath);
        directory.setFilter(QDir::Files | QDir::NoDotAndDotDot);
        directory.setSorting(QDir::Time);

        QFileInfoList fileList = directory.entryInfoList();
        for (const QFileInfo& fileInfo : fileList) {
            if (fileInfo.suffix().toLower() == "png") {
                return fileInfo.absoluteFilePath();
            }
        }
        return QString();
    }
};
