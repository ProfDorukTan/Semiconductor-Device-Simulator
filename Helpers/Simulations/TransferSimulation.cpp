//
// Created by Doruk Tan Atila on 13/04/24.
//

#include "TransferSimulation.h"
#include <iomanip>
#include <algorithm>

TransferSimulation::TransferSimulation(MOSFET &mosfet_par, double Vmin_var, double Vmax_var, double Vstep_var, const std::vector<double> &params_Vds) :
        mosfet_(mosfet_par), Vmin_(Vmin_var), Vmax_(Vmax_var), Vstep_(Vstep_var){

    // Set up the mapping of vgs values to empty vector of Ids values
    for (auto vds: params_Vds) {
        Params_Vds_Ids_[vds] = std::vector<double>();
    }
    /*
    The following mapping will be used for the simulation data:
        Vds1 ->  Ids1, Ids2, Ids3, ...
        Vds2 ->  Ids1, Ids2, Ids3, ...
        Vds3 ->  Ids1, Ids2, Ids3, ...
        ...
    */
}

//GETTER FUNCTIONS
const std::unordered_map<double,std::vector<double>> & TransferSimulation::getParams_Vds_Ids() const {
    return Params_Vds_Ids_;
}

//SIMULATION FUNCTIONS
void TransferSimulation::GenerateTransferCurve(int COMPLEXITY) {
    // Creating Vds values
    double Vgs = Vmin_;
    if (Vmax_ > Vmin_) {
        while (Vgs <= Vmax_) {
            Params_Vgs_.push_back(Vgs);
            Vgs += Vstep_;
        }
    }else if(Vmax_ < Vmin_) {
		while (Vgs >= Vmax_) {
			Params_Vgs_.push_back(Vgs);
			Vgs += Vstep_;
		}
	}


    // Generate Ids values according to complexity value
    switch(COMPLEXITY) {
        case 1:
            level1_sweep_transfer(mosfet_, Params_Vds_Ids_, Params_Vgs_);
            break;

        case 2:
            level2_sweep_transfer(mosfet_, Params_Vds_Ids_, Params_Vgs_);
            break;

        case 3:
            level3_sweep_transfer(mosfet_, Params_Vds_Ids_, Params_Vgs_);
            break;

        default:
            throw std::invalid_argument("Invalid Complexity Level");
    }
}

void TransferSimulation::GraphTransferCurve(int COMPLEXITY) {
    TransferSimulation::GenerateTransferCurve(COMPLEXITY);
    // GRAPHING CURVES

    // Graph Title
    std::string NameString = "Transfer Curve - " + mosfet_.getName() + "Vth=" + std::to_string(mosfet_.getVt()) + " - Vds:";

    // Store vgs_pair.first values in a temporary container
    std::vector<double> vds_values;
    for (const auto& vds_pair : Params_Vds_Ids_) {
        vds_values.push_back(vds_pair.first);
    }
    // Sort the vgs_values container
    std::sort(vds_values.begin(), vds_values.end());

    // Params in the Title
    for (const auto& vds_value : vds_values) {
        // Format the floating-point number with 2 decimal places
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << vds_value; //To make params 2 decimal places
        NameString += ss.str() + "/";
    }

    wchar_t *title = stringToWideChar(NameString);

    bool success;
    StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
    RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = imageW;
    settings->height = imageL;
    settings->autoBoundaries = true;
    settings->title = toVector(title);
    settings->xLabel = toVector(L"Vgs (V)");
    settings->yLabel = toVector(L"Ids (A)");

// Loop through Params_Vgs_Ids and create ScatterPlotSeries dynamically
    int i = 0;
    for (auto vgs_pair : Params_Vds_Ids_) {
        ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
        series->xs = &Params_Vgs_;
        series->ys = &Params_Vds_Ids_[vgs_pair.first];
        series->linearInterpolation = true;
        series->lineType = toVector(L"solid");
        series->lineThickness = 2;
        series->color = CreateRGBColor(0.66/(0.3*i+1), 0.75/(0.3*i+1), 1/(0.3*i+1));  // Example: Assigning alternating colors

        settings->scatterPlotSeries->push_back(series);
        i++;
    }
    success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

    if(success) {
        std::vector<double> *pngdata = ConvertToPNG(imageReference->image);
        WriteToFile(pngdata, "TransferCurve");
        DeleteImage(imageReference->image);
    } else {
        std::cerr << "Error: ";
        for(wchar_t c : *errorMessage->string){
            std::cerr << c;
        }
        std::cerr << std::endl;
    }

}

void TransferSimulation::GraphTransferCurveLog(int COMPLEXITY) {
    TransferSimulation::GenerateTransferCurve(COMPLEXITY);
    // GRAPHING CURVES

    // Graph Title
    std::string NameString = "Transfer Curve (Log) - " + mosfet_.getName() + "Vth=" + std::to_string(mosfet_.getVt()) + " - Vds:";

    // Store vgs_pair.first values in a temporary container
    std::vector<double> vds_values;
    for (const auto& vds_pair : Params_Vds_Ids_) {
        vds_values.push_back(vds_pair.first);
    }
    // Sort the vgs_values container
    std::sort(vds_values.begin(), vds_values.end());

    // Params in the Title
    for (const auto& vds_value : vds_values) {
        // Format the floating-point number with 2 decimal places
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << vds_value; //To make params 2 decimal places
        NameString += ss.str() + "/";
    }

    wchar_t* title = stringToWideChar(NameString);

    bool success;
    StringReference* errorMessage = CreateStringReferenceLengthValue(0, L' ');
    RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

    ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
    settings->width = imageW;
    settings->height = imageL;
    settings->autoBoundaries = true;
    settings->title = toVector(title);
    settings->xLabel = toVector(L"Vgs (V)");
    settings->yLabel = toVector(L"Ids (A)");

    // Convert the Ids values to logarithmic scale
    for (auto& vds_pair : Params_Vds_Ids_) {
        // Transform the Ids values to logarithmic scale
        for (double& Id : vds_pair.second) {
            if (Id <= 0) {
				Id = 1e-12;
			}
            Id = std::log10(Id);
        }
    }

    // Loop through Params_Vgs_Ids and create ScatterPlotSeries dynamically
    int i = 0;
    for (auto vgs_pair : Params_Vds_Ids_) {
        ScatterPlotSeries* series = GetDefaultScatterPlotSeriesSettings();
        series->xs = &Params_Vgs_;
        series->ys = &Params_Vds_Ids_[vgs_pair.first];
        series->linearInterpolation = true;
        series->lineType = toVector(L"solid");
        series->lineThickness = 2;
        series->color = CreateRGBColor(0.66 / (0.3 * i + 1), 0.75 / (0.3 * i + 1), 1 / (0.3 * i + 1));  // Example: Assigning alternating colors

        settings->scatterPlotSeries->push_back(series);
        i++;
    }
    success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

    if (success) {
        std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
        WriteToFile(pngdata, "TransferCurve");
        DeleteImage(imageReference->image);
    }
    else {
        std::cerr << "Error: ";
        for (wchar_t c : *errorMessage->string) {
            std::cerr << c;
        }
        std::cerr << std::endl;
    }

}

