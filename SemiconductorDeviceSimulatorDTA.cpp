#include "SemiconductorDeviceSimulatorDTA.h"

SemiconductorDeviceSimulatorDTA::SemiconductorDeviceSimulatorDTA(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::SemiconductorDeviceSimulatorDTAClass())
{
    ui->setupUi(this);

    on_LoadMOSFETs_clicked();
    // Connect the clicked signals with functions
    connect(ui->DeleteMosfetButton, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_DeleteMosfetButton_clicked);
    connect(ui->SaveMosfetLevel1, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_SaveMosfetLevel1_clicked);
    connect(ui->SaveMosfetLevel2, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_SaveMosfetLevel2_clicked);
    connect(ui->LoadMOSFETs, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_LoadMOSFETs_clicked);
    connect(ui->AddVgs, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_AddVgs_clicked);
    connect(ui->OutputSimulate, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_SimulateButton_clicked);

}

SemiconductorDeviceSimulatorDTA::~SemiconductorDeviceSimulatorDTA()
{
    on_SaveMOSFETs_clicked();
    delete ui;
}

void SemiconductorDeviceSimulatorDTA::on_SaveMosfetLevel1_clicked() {
    // Retrieve values from input fields
    QString name = ui->MosfetName->text(); // MOSFET Object Name
    QString architecture = ui->L1_1->currentText();    //MOSFET Architecture
    QString channel = ui->L1_2->currentText();     //MOSFET Channel type
    double vt = ui->L1_3->value(); // Threshold Voltage
    double mobility = ui->L1_4->value(); // Mobility
    double cox = ui->L1_5->value(); // Cox
    double w = ui->L1_6->value(); // W
    double l = ui->L1_7->value(); // L

    // Validate inputs
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Error", "MOSFET name cannot be empty.");
        return; // Stop further processing
    }


    // Create an instance of MOSFET (you need to define the MOSFET class)
    bool isDuplicate = false;
    for (int i = 0; i < ui->MosfetList->count(); ++i) {
        QListWidgetItem* item = ui->MosfetList->item(i);
        if (item && item->text() == name) {
            isDuplicate = true;
            break;
        }
    }
    if (isDuplicate) {
        // Display a message or take appropriate action for duplicate name
        QMessageBox::warning(this, "Duplicate Name", "MOSFET with the same name already exists.");
        return; // Don't proceed with adding the MOSFET
    }

    // Create an instance of MOSFET for Level 1
    MOSFET* mosfet = new MOSFET(name.toStdString(), channel.at(0).toLatin1(), vt, mobility, cox, w, l);
    MOSFET::addMOSFET(mosfet);

    // Add MOSFET name to the list widget
    ui->MosfetList->addItem(name);
    ui->MosfetList_2->addItem(name);

}

void SemiconductorDeviceSimulatorDTA::on_SaveMosfetLevel2_clicked() {
    // Retrieve values from input fields
    QString name = ui->MosfetName->text(); // MOSFET Object Name
    QString architecture = ui->L2_1->currentText();    //MOSFET Architecture
    QString channel = ui->L2_2->currentText();     //MOSFET Channel type
    double vt = ui->L2_3->value(); // Threshold Voltage
    double mobility = ui->L2_4->value(); // Mobility
    double cox = ui->L2_5->value(); // Cox
    double w = ui->L2_6->value(); // W
    double l = ui->L2_7->value(); // L
    double lambda = ui->L2_8->value(); // Lambda

    // Validate inputs
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Error", "MOSFET name cannot be empty.");
        return; // Stop further processing
    }


    // Create an instance of MOSFET (you need to define the MOSFET class)
    bool isDuplicate = false;
    for (int i = 0; i < ui->MosfetList->count(); ++i) {
        QListWidgetItem* item = ui->MosfetList->item(i);
        if (item && item->text() == name) {
            isDuplicate = true;
            break;
        }
    }
    if (isDuplicate) {
        // Display a message or take appropriate action for duplicate name
        QMessageBox::warning(this, "Duplicate Name", "MOSFET with the same name already exists.");
        return; // Don't proceed with adding the MOSFET
    }

    // Create an instance of MOSFET for Level 1
    MOSFET* mosfet = new MOSFET(name.toStdString(), channel.at(0).toLatin1(), vt, mobility, cox, w, l, lambda);
    MOSFET::addMOSFET(mosfet);

    // Add MOSFET name to the list widget
    ui->MosfetList->addItem(name);
    ui->MosfetList_2->addItem(name);

    // You can now use the 'mosfet' object as needed
    // For example, add it to a list, display information, etc.
}

void SemiconductorDeviceSimulatorDTA::on_DeleteMosfetButton_clicked() {
    // Get the selected item from the list widget
    QListWidgetItem* selectedItem = ui->MosfetList->currentItem();

    // Check if an item is selected
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "Please select a MOSFET to delete.");
        return;
    }

    // Get the name of the selected MOSFET
    QString mosfetName = selectedItem->text();

    // Ask for confirmation
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation",
        "Are you sure you want to delete the MOSFET: " + mosfetName + "?",
        QMessageBox::Yes | QMessageBox::No);

    // Check the user's response
    if (reply == QMessageBox::Yes) {
        // User clicked "Yes," so proceed with deleting the MOSFET
        delete selectedItem;
        // Delete instance
        std::string targetName = mosfetName.toStdString();
        MOSFET* targetMOSFET = MOSFET::getMOSFETByName(targetName);
        delete targetMOSFET;

    }
    // If "No" or the dialog is closed, do nothing
}

void SemiconductorDeviceSimulatorDTA::on_AddVgs_clicked() {
    double Vgs = ui->Output_2->value();
    QString VgsSTR = QString::number(Vgs);
    // Create an instance of MOSFET (you need to define the MOSFET class)
    bool isDuplicate = false;
    for (int i = 0; i < ui->VgsList->count(); ++i) {
        QListWidgetItem* item = ui->VgsList->item(i);
        if (item && item->text() == VgsSTR) {
            isDuplicate = true;
            break;
        }
    }
    if (isDuplicate) {
        // Display a message or take appropriate action for duplicate name
        QMessageBox::warning(this, "Duplicate Vgs", "Duplicate Vgs");
        return; // Don't proceed with adding the MOSFET
    }
    ui->VgsList->addItem(VgsSTR);
}



// Simuation functions
//This class is used to display images in a popup dialog - it is used to display the simulation results
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
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

//this class is used to find the latest image in a directory - it is used to display the latest simulation result
#include <QDir>
#include <QFileInfoList>
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

void SemiconductorDeviceSimulatorDTA::on_SimulateButton_clicked() {
    QListWidgetItem* selectedItem = ui->MosfetList_2->currentItem();
    // Check if an item is selected
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "Please select a MOSFET to Simulate.");
        return;
    }
    // Get the name of the selected MOSFET
    QString mosfetName = selectedItem->text();

    // Ask for confirmation
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation",
        "Are you sure you want to Simulate the MOSFET: " + mosfetName + "?",
        QMessageBox::Yes | QMessageBox::No);
    // Check the user's response
    if (reply == QMessageBox::Yes) {
        double Vmin = ui->Output_3->value();
        double Vmax = ui->Output_4->value();
        double Vstep = ui->Output_5->value();
        int level = ui->Output_1->value();
        if (Vmin > Vmax) {
            QMessageBox::warning(this, "Error", "Vmin > Vmax");
            return;
        }
        std::vector<double> vgsValues;
        for (int i = 0; i < ui->VgsList->count(); ++i) {
            QString itemText = ui->VgsList->item(i)->text();
            bool conversionOK;
            double value = itemText.toDouble(&conversionOK);
            // Check if conversion to double was successful
            if (conversionOK) {
                vgsValues.push_back(value);
            }
            else {
                // Handle the case where conversion fails (optional)
                qDebug() << "Failed to convert item text to double: " << itemText;
            }
        }

        std::string targetName = mosfetName.toStdString();
        MOSFET* targetMOSFET = MOSFET::getMOSFETByName(targetName);
        OutputSimulation output(*targetMOSFET, Vmin, Vmax, Vstep, vgsValues);
        output.GraphOutputCurve(level);

    }


    // Specify the directory containing the images
    QString imageDirectory = ".\\GRAPHS";

    QString latestImage = findLatestImage(imageDirectory);
    if (latestImage.isEmpty()) {
        QMessageBox::warning(this, "Error", "No image found in the directory.");
        return;
    }

    // Load the image from file
    QPixmap image(latestImage);
    if (image.isNull()) {
        QMessageBox::warning(this, "Error", "Failed to load the image.");
        return;
    }

    // Create the popup dialog
    ImagePopupDialog* dialog = new ImagePopupDialog(this);
    dialog->setImage(image);
    dialog->exec();
    delete dialog; // Ensure cleanup after the dialog is closed

}

#include <fstream>
#include <QMessageBox>

void SemiconductorDeviceSimulatorDTA::on_LoadMOSFETs_clicked() {
    // Open the JSON file
    std::ifstream file("mosfets.json");

    if (file.is_open()) {
        try {
            // Parse the JSON array from the file
            nlohmann::json mosfetArray;
            file >> mosfetArray;

            // Clear existing MOSFETs
            MOSFET::clearMosfets();

            // Iterate through each JSON object in the array
            for (const auto& mosfetObject : mosfetArray) {
                // Extract parameters from the JSON object
                std::string name = mosfetObject["name"];
                char type = mosfetObject.value("type", ' ');  // Use ' ' as a placeholder
                double vt = mosfetObject.value("vt", NULL);   // Use NULL as a placeholder
                double mobility = mosfetObject.value("mobility", NULL); // Use NULL as a placeholder
                double cox = mosfetObject.value("cox", NULL); // Use NULL as a placeholder
                double channelWidth = mosfetObject.value("channelWidth", NULL); // Use NULL as a placeholder
                double channelLength = mosfetObject.value("channelLength", NULL); // Use NULL as a placeholder
                double lambda = mosfetObject.value("lambda", NULL); // Use NULL as a placeholder

                // Create a MOSFET object using the extracted parameters
                MOSFET* mosfet = new MOSFET(name, type, vt, mobility, cox, channelWidth, channelLength, lambda);

                // Add the MOSFET object to the list
                MOSFET::addMOSFET(mosfet);
            }

            // Update the UI with the loaded MOSFETs
            updateUIWithLoadedMOSFETs();
        }
        catch (const nlohmann::json::exception& e) {
            // Handle JSON parsing errors
            QMessageBox::warning(this, "Error", "Error while parsing MOSFET data: " + QString::fromStdString(e.what()));
        }

        file.close();
    }
    else {
        // Handle the case where the file couldn't be opened
        QMessageBox::warning(this, "Error", "Could not open the file for reading.");
    }
}

void SemiconductorDeviceSimulatorDTA::on_SaveMOSFETs_clicked() {
    // Check if the JSON file already exists
    std::ifstream checkFile("mosfets.json");
    bool fileExists = checkFile.good();
    checkFile.close();

    // Open the JSON file with binary mode to handle potential encoding issues
    std::ofstream file("mosfets.json", std::ios::binary);

    if (file.is_open()) {
        // Create a JSON array
        nlohmann::json mosfetArray;

        // Iterate through each MOSFET
        for (MOSFET* mosfet : MOSFET::getMosfets()) {
            // Create a JSON object for each MOSFET
            nlohmann::json mosfetObject;

            // Add MOSFET parameters to the JSON object
            mosfetObject["name"] = mosfet->getName();
            mosfetObject["type"] = mosfet->getType();
            mosfetObject["vt"] = mosfet->getVt();
            mosfetObject["mobility"] = mosfet->getMobility();
            mosfetObject["cox"] = mosfet->getCox();
            mosfetObject["channelWidth"] = mosfet->getChannelWidth();
            mosfetObject["channelLength"] = mosfet->getChannelLength();
            mosfetObject["lambda"] = mosfet->getLambda();

            // Add the MOSFET JSON object to the array
            mosfetArray.push_back(mosfetObject);
        }

        // Save the JSON array to the file
        file << mosfetArray.dump(4);  // The second argument (4) is for pretty printing
        file.close();

        if (fileExists) {
            QMessageBox::information(this, "Success", "MOSFETs saved successfully!");
        }
        else {
            QMessageBox::information(this, "Success", "MOSFETs file created and saved successfully!");
        }
    }
    else {
        // Handle the case where the file couldn't be opened
        QMessageBox::warning(this, "Error", "Could not open the file for writing.");
    }
}

void SemiconductorDeviceSimulatorDTA::updateUIWithLoadedMOSFETs() {
    // Implement this function to update the UI with loaded MOSFETs
    // For example, you can populate a list widget with MOSFET names
    ui->MosfetList->clear();
    for (const MOSFET* mosfet : MOSFET::getMosfets()) {
        ui->MosfetList->addItem(QString::fromStdString(mosfet->getName()));
        ui->MosfetList_2->addItem(QString::fromStdString(mosfet->getName()));
    }
}
