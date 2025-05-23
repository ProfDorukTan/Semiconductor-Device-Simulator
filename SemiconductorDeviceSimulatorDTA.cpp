#include "SemiconductorDeviceSimulatorDTA.h"


SemiconductorDeviceSimulatorDTA::SemiconductorDeviceSimulatorDTA(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::SemiconductorDeviceSimulatorDTAClass())
{
    ui->setupUi(this);
    
    on_LoadMOSFETs_clicked();       // Load MOSFETs from the file in the beginning

    // Signal-Slot connections
    
    // MOSFET Creation Page
    connect(ui->DeleteMosfetButton, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_DeleteMosfetButton_clicked);
    connect(ui->SaveMosfetLevel1, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_SaveMosfetLevel1_clicked);
    connect(ui->SaveMosfetLevel2, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_SaveMosfetLevel2_clicked);
    connect(ui->SaveMosfetLevel3, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_SaveMosfetLevel3_clicked);
        //Parameter preload Functions
        connect(ui->LoadMetalLevel3, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_LoadMetal_clicked);
        connect(ui->LoadSemiconductorLevel3, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_LoadSemiconductor_clicked);


    // Output Simulation Page
    connect(ui->AddVgs, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_AddVgs_clicked);
    connect(ui->DeleteVgs, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_DeleteVgs_clicked);
    connect(ui->OutputSimulate, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_OutputSimulateButton_clicked);

    // Transfer Simulation Page
    connect(ui->AddVds, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_AddVds_clicked);
    connect(ui->DeleteVds, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_DeleteVds_clicked);
    connect(ui->TransferSimulate, &QPushButton::clicked, this, &SemiconductorDeviceSimulatorDTA::on_TransferSimulateButton_clicked);


}

//This function is used to update the UI with the loaded MOSFETs
void SemiconductorDeviceSimulatorDTA::updateUIWithLoadedMOSFETs() {
    // Implement this function to update the UI with loaded MOSFETs
    // For example, you can populate a list widget with MOSFET names
    ui->MosfetList->clear();
    for (const MOSFET* mosfet : MOSFET::getMosfets()) {
        ui->MosfetList->addItem(QString::fromStdString(mosfet->getName()));
        ui->MosfetList_2->addItem(QString::fromStdString(mosfet->getName()));
        ui->MosfetList_3->addItem(QString::fromStdString(mosfet->getName()));
    }
}

SemiconductorDeviceSimulatorDTA::~SemiconductorDeviceSimulatorDTA()
{
    on_SaveMOSFETs_clicked();
    delete ui;
}

//This function is used to load the MOSFETs from a file to the running application
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

//This function is used to save the MOSFETs from the running application to a file
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
            mosfetObject["metalWorkFunction"] = mosfet->getMetalWorkFunction();
            mosfetObject["semiconductorBandgap"] = mosfet->getSemiconductorBandgap();
            mosfetObject["semiconductorElectronAffinity"] = mosfet->getSemiconductorElectronAffinity();
            mosfetObject["semiconductorDopingConcentration"] = mosfet->getSemiconductorDopingConcentration();
            mosfetObject["semiconductorPermittivity"] = mosfet->getSemiconductorPermittivity();
            mosfetObject["oxideThickness"] = mosfet->getOxideThickness();
            mosfetObject["oxidePermittivity"] = mosfet->getOxidePermittivity();
            mosfetObject["oxideTrappedCharge"] = mosfet->getOxideTrappedCharge();
            mosfetObject["temperature"] = mosfet->getTemperature();
            mosfetObject["effectiveDensityOfStatesInConductionBand"] = mosfet->getEffectiveDensityOfStatesInConductionBand();
            mosfetObject["effectiveDensityOfStatesInValenceBand"] = mosfet->getEffectiveDensityOfStatesInValenceBand();

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

// MOSFET Creation Page
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

        // Remove the corresponding items from MosfetList2 and MosfetList3
        for (int i = 0; i < ui->MosfetList_2->count(); ++i) {
            if (ui->MosfetList_2->item(i)->text() == mosfetName) {
                delete ui->MosfetList_2->takeItem(i);
                break;
            }
        }

        for (int i = 0; i < ui->MosfetList_3->count(); ++i) {
            if (ui->MosfetList_3->item(i)->text() == mosfetName) {
                delete ui->MosfetList_3->takeItem(i);
                break;
            }
        }
    }
    // If "No" or the dialog is closed, do nothing
}


void SemiconductorDeviceSimulatorDTA::on_SaveMosfetLevel1_clicked() {
    // Retrieve values from input fields
    QString name = ui->MosfetName->text() + "--(LEVEL1)"; // MOSFET Object Name
    QString architecture = ui->L1_1->currentText();    //MOSFET Architecture
    QString channel = ui->L1_2->currentText();     //MOSFET Channel type
    double vt = ui->L1_3->value(); // Threshold Voltage
    double mobility = ui->L1_4->value(); // Mobility
    double cox = ui->L1_5->value() * pow(10, -12); // Cox
    double w = ui->L1_6->value(); // W
    double l = ui->L1_7->value(); // L

    // Validate inputs
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Error", "MOSFET name cannot be empty.");
        return; // Stop further processing
    }
    if (name.contains(" ")) {
		QMessageBox::warning(this, "Error", "MOSFET name cannot contain spaces.");
		return; // Stop further processing
    }


    // Create an instance of MOSFET
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
    ui->MosfetList_3->addItem(name);

}

void SemiconductorDeviceSimulatorDTA::on_SaveMosfetLevel2_clicked() {
    // Retrieve values from input fields
    QString name = ui->MosfetName->text() + "--(LEVEL2)"; // MOSFET Object Name
    QString architecture = ui->L2_1->currentText();    //MOSFET Architecture
    QString channel = ui->L2_2->currentText();     //MOSFET Channel type
    double vt = ui->L2_3->value(); // Threshold Voltage
    double mobility = ui->L2_4->value(); // Mobility
    double cox = ui->L2_5->value() * pow(10, -12); // Cox
    double w = ui->L2_6->value(); // W
    double l = ui->L2_7->value(); // L
    double lambda = ui->L2_8->value(); // Lambda

    // Validate inputs
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Error", "MOSFET name cannot be empty.");
        return; // Stop further processing
    }
    if (name.contains(" ")) {
        QMessageBox::warning(this, "Error", "MOSFET name cannot contain spaces.");
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

    // Create an instance of MOSFET for Level 2
    MOSFET* mosfet = new MOSFET(name.toStdString(), channel.at(0).toLatin1(), vt, mobility, cox, w, l, lambda);
    MOSFET::addMOSFET(mosfet);

    // Add MOSFET name to the list widget
    ui->MosfetList->addItem(name);
    ui->MosfetList_2->addItem(name);
    ui->MosfetList_3->addItem(name);

}

void SemiconductorDeviceSimulatorDTA::on_SaveMosfetLevel3_clicked() {
    // Retrieve values from input fields
    QString name = ui->MosfetName->text() + "--(LEVEL3)"; // MOSFET Object Name
    QString architecture = ui->L3_1->currentText();    //MOSFET Architecture
    QString channel = ui->L3_2->currentText();     //MOSFET Channel type
    double temperature = ui->L3_3->value(); // Temperature
    double w = ui->L3_4->value(); // W
    double l = ui->L3_5->value(); // L

    double metalWorkFunction = ui->L3_6->value(); // Metal Work Function

    double oxideThickness = (ui->L3_7->value()) * pow(10, -7); // Oxide Thickness -> convert from nm to cm
    double oxidePermittivity = ui->L3_8->value(); // Oxide Permittivity
    double oxideTrappedCharge = (ui->L3_9->value()) * pow(10, 9); // Oxide Trapped Charge

    double mobility = ui->L3_10->value(); // Majority Mobility
    double semiconductorBandgap = ui->L3_11->value(); // Semiconductor Bandgap
    double effectiveDensityOfStatesInConductionBand = (ui->L3_12->value()) * pow(10, 19); // Effective Density of States in Conduction Band
    double effectiveDensityOfStatesInValenceBand = (ui->L3_13->value()) * pow(10, 19); // Effective Density of States in Valence Band
    double semiconductorElectronAffinity = ui->L3_14->value(); // Semiconductor Electron Affinity
    double semiconductorPermittivity = ui->L3_15->value(); // Semiconductor Permittivity
    double semiconductorDopingConcentration = ui->L3_16->value() * pow(10, 14); // Semiconductor Doping Concentration


    // Validate MOSFET Name
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Error", "MOSFET name cannot be empty.");
        return; // Stop further processing
    }
    if (name.contains(" ")) {
        QMessageBox::warning(this, "Error", "MOSFET name cannot contain spaces.");
        return; // Stop further processing
    }

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
    

    // Create an instance of MOSFET for Level 3
    MOSFET* mosfet = new MOSFET(name.toStdString(), channel.at(0).toLatin1(), mobility, w, l, metalWorkFunction,
        semiconductorBandgap, semiconductorElectronAffinity, semiconductorDopingConcentration, semiconductorPermittivity, 
        oxideThickness, oxidePermittivity, oxideTrappedCharge, temperature, effectiveDensityOfStatesInConductionBand, effectiveDensityOfStatesInValenceBand);
    MOSFET::addMOSFET(mosfet);

    // Add MOSFET name to the list widget
    ui->MosfetList->addItem(name);
    ui->MosfetList_2->addItem(name);
    ui->MosfetList_3->addItem(name);
}


// Parameter preload Functions
void SemiconductorDeviceSimulatorDTA::on_LoadMetal_clicked() {
    QString metalChoice = ui->MetalList->currentText();
    if (metalChoice == "Al") {
        ui->L3_6->setValue(ALUMINUM_WORK_FUNCTION);
    }
}

void SemiconductorDeviceSimulatorDTA::on_LoadSemiconductor_clicked() {
    QString semiconductorChoice = ui->SemiconductorList->currentText();
    QString channel = ui->L3_2->currentText();     //MOSFET Channel type to avoid same channel same bulk

    if (semiconductorChoice == "n-Si") {
        if (channel == 'N') {
            QMessageBox::warning(this, "Error", "Channel and bulk must be different");
            return; // Stop further processing
        }
        ui->L3_10->setValue(SILICON_HOLE_MOBILITY);
        ui->L3_11->setValue(SILICON_BANDGAP);
        ui->L3_12->setValue(SILICON_EFFECTIVE_DENSITY_OF_STATES_IN_CONDUCTION_BAND);
        ui->L3_13->setValue(SILICON_EFFECTIVE_DENSITY_OF_STATES_IN_VALANCE_BAND);
        ui->L3_14->setValue(SILICON_ELECTON_AFFINITY);
        ui->L3_15->setValue(SILICON_DIELECTRIC_CONSTANT);
    }
    else if (semiconductorChoice == "p-Si") {
        if (channel == 'P') {
            QMessageBox::warning(this, "Error", "Channel and bulk must be different");
            return; // Stop further processing
        }
        ui->L3_10->setValue(SILICON_ELECTRON_MOBILITY);
        ui->L3_11->setValue(SILICON_BANDGAP);
        ui->L3_12->setValue(SILICON_EFFECTIVE_DENSITY_OF_STATES_IN_CONDUCTION_BAND);
        ui->L3_13->setValue(SILICON_EFFECTIVE_DENSITY_OF_STATES_IN_VALANCE_BAND);
        ui->L3_14->setValue(SILICON_ELECTON_AFFINITY);
        ui->L3_15->setValue(SILICON_DIELECTRIC_CONSTANT);
    }
    else if (semiconductorChoice == "n-Ge") {
        if (channel == 'N') {
            QMessageBox::warning(this, "Error", "Channel and bulk must be different");
            return; // Stop further processing
        }
        ui->L3_10->setValue(GERMANIUM_HOLE_MOBILITY);
        ui->L3_11->setValue(GERMANIUM_BANDGAP);
        ui->L3_12->setValue(GERMANIUM_EFFECTIVE_DENSITY_OF_STATES_IN_CONDUCTION_BAND);
        ui->L3_13->setValue(GERMANIUM_EFFECTIVE_DENSITY_OF_STATES_IN_VALANCE_BAND);
        ui->L3_14->setValue(GERMANIUM_ELECTON_AFFINITY);
        ui->L3_15->setValue(GERMANIUM_DIELECTRIC_CONSTANT);
    }
    else if (semiconductorChoice == "p-Ge") {
        if (channel == 'P') {
            QMessageBox::warning(this, "Error", "Channel and bulk must be different");
            return; // Stop further processing
        }
        ui->L3_10->setValue(GERMANIUM_ELECTRON_MOBILITY);
        ui->L3_11->setValue(GERMANIUM_BANDGAP);
        ui->L3_12->setValue(GERMANIUM_EFFECTIVE_DENSITY_OF_STATES_IN_CONDUCTION_BAND);
        ui->L3_13->setValue(GERMANIUM_EFFECTIVE_DENSITY_OF_STATES_IN_VALANCE_BAND);
        ui->L3_14->setValue(GERMANIUM_ELECTON_AFFINITY);
        ui->L3_15->setValue(GERMANIUM_DIELECTRIC_CONSTANT);
    }
    else if (semiconductorChoice == "n-GaAs") {
        if (channel == 'N') {
            QMessageBox::warning(this, "Error", "Channel and bulk must be different");
            return; // Stop further processing
        }
        ui->L3_10->setValue(GALLIUM_ARSENIDE_HOLE_MOBILITY);
        ui->L3_11->setValue(GALLIUM_ARSENIDE_BANDGAP);
        ui->L3_12->setValue(GALLIUM_ARSENIDE_EFFECTIVE_DENSITY_OF_STATES_IN_CONDUCTION_BAND);
        ui->L3_13->setValue(GALLIUM_ARSENIDE_EFFECTIVE_DENSITY_OF_STATES_IN_VALANCE_BAND);
        ui->L3_14->setValue(GALLIUM_ARSENIDE_ELECTON_AFFINITY);
        ui->L3_15->setValue(GALLIUM_ARSENIDE_DIELECTRIC_CONSTANT);
    }
    else if (semiconductorChoice == "p-GaAs") {
        if (channel == 'P') {
            QMessageBox::warning(this, "Error", "Channel and bulk must be different");
            return; // Stop further processing
        }
        ui->L3_10->setValue(GALLIUM_ARSENIDE_ELECTRON_MOBILITY);
        ui->L3_11->setValue(GALLIUM_ARSENIDE_BANDGAP);
        ui->L3_12->setValue(GALLIUM_ARSENIDE_EFFECTIVE_DENSITY_OF_STATES_IN_CONDUCTION_BAND);
        ui->L3_13->setValue(GALLIUM_ARSENIDE_EFFECTIVE_DENSITY_OF_STATES_IN_VALANCE_BAND);
        ui->L3_14->setValue(GALLIUM_ARSENIDE_ELECTON_AFFINITY);
        ui->L3_15->setValue(GALLIUM_ARSENIDE_DIELECTRIC_CONSTANT);
    }


}

// Output Simulation Page
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

void SemiconductorDeviceSimulatorDTA::on_DeleteVgs_clicked() {
	// Get the selected item from the list widget
	QListWidgetItem* selectedItem = ui->VgsList->currentItem();

    if (!selectedItem) {
		QMessageBox::warning(this, "Error", "Please select a Vgs to delete.");
		return;
	}

	// Get the name of the selected MOSFET
	QString Vgs = selectedItem->text();
	delete selectedItem;
}

void SemiconductorDeviceSimulatorDTA::on_OutputSimulateButton_clicked() {
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
        if (((Vmin > Vmax) && (Vstep > 0)) || (Vmin < Vmax) && (Vstep < 0)) {
            QMessageBox::warning(this, "Error", "Vmin-Vmax-Vstep sign mismatch");
            return;
        }
        std::vector<double> vgsValues;
        for (int i = 0; i < ui->VgsList->count(); ++i) {
            QString itemText = ui->VgsList->item(i)->text();
            double value = itemText.toDouble();
            vgsValues.push_back(value);
        }

        std::string targetName = mosfetName.toStdString();
        MOSFET* targetMOSFET = MOSFET::getMOSFETByName(targetName);
        OutputSimulation output(*targetMOSFET, Vmin, Vmax, Vstep, vgsValues);
        output.GraphOutputCurve(level);
    }
    else {
        return;
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

// Transfer Simulation Page
void SemiconductorDeviceSimulatorDTA::on_AddVds_clicked() {
	double Vds = ui->Output_6->value();
	QString VdsSTR = QString::number(Vds);
	// Create an instance of MOSFET (you need to define the MOSFET class)
	bool isDuplicate = false;
	for (int i = 0; i < ui->VdsList->count(); ++i) {
		QListWidgetItem* item = ui->VdsList->item(i);
		if (item && item->text() == VdsSTR) {
			isDuplicate = true;
			break;
		}
	}
	if (isDuplicate) {
		// Display a message or take appropriate action for duplicate name
		QMessageBox::warning(this, "Duplicate Vds", "Duplicate Vds");
		return; // Don't proceed with adding the MOSFET
	}
	ui->VdsList->addItem(VdsSTR);
}

void SemiconductorDeviceSimulatorDTA::on_DeleteVds_clicked() {
	// Get the selected item from the list widget
	QListWidgetItem* selectedItem = ui->VdsList->currentItem();

	if (!selectedItem) {
		QMessageBox::warning(this, "Error", "Please select a Vds to delete.");
		return;
	}

	// Get the name of the selected MOSFET
	QString Vds = selectedItem->text();
	delete selectedItem;
}

void SemiconductorDeviceSimulatorDTA::on_TransferSimulateButton_clicked(){
QListWidgetItem* selectedItem = ui->MosfetList_3->currentItem();
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
        double Vmin = ui->Output_8->value();
        double Vmax = ui->Output_9->value();
        double Vstep = ui->Output_10->value();
        int level = ui->Output_7->value();
        if (((Vmin > Vmax) && (Vstep > 0)) || (Vmin < Vmax) && (Vstep < 0)) {
            QMessageBox::warning(this, "Error", "Vmin-Vmax-Vstep sign mismatch");
            return;
        }
        std::vector<double> vdsValues;
        for (int i = 0; i < ui->VdsList->count(); ++i) {
            QString itemText = ui->VdsList->item(i)->text();
            double value = itemText.toDouble();
            vdsValues.push_back(value);
        }

        std::string targetName = mosfetName.toStdString();
        MOSFET* targetMOSFET = MOSFET::getMOSFETByName(targetName);
        TransferSimulation output(*targetMOSFET, Vmin, Vmax, Vstep, vdsValues);

        if (ui->LogCheck->isChecked()) {
            output.GraphTransferCurveLog(level);    //Logarithmic scale 
        }
        else {
            output.GraphTransferCurve(level);       //Linear scale
        }
    }
    else {
        return;
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