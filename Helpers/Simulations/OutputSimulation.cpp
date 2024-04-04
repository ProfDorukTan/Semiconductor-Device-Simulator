//
// Created by Doruk Tan Atila on 11/12/23.
//

#include "OutputSimulation.h"
#include <iomanip>
#include <algorithm>

OutputSimulation::OutputSimulation(MOSFET &mosfet_par, double Vmin_var, double Vmax_var, double Vstep_var, const std::vector<double> &params_Vgs) :
        mosfet_(mosfet_par), Vmin_(Vmin_var), Vmax_(Vmax_var), Vstep_(Vstep_var){

    // Set up the mapping of vgs values to empty vector of Ids values
    for (auto vgs: params_Vgs) {
        Params_Vgs_Ids_[vgs] = std::vector<double>();
    }
    /*
    The following mapping will be used for the simulation data:
        Vgs1 ->  Ids1, Ids2, Ids3, ...
        Vgs2 ->  Ids1, Ids2, Ids3, ...
        Vgs3 ->  Ids1, Ids2, Ids3, ...
        ...
    */
}

//GETTER FUNCTIONS
const std::unordered_map<double,std::vector<double>> &OutputSimulation::getParams_Vgs_Ids() const {
    return Params_Vgs_Ids_;
}

//SIMULATION FUNCTIONS
void OutputSimulation::GenerateOutputCurve(int COMPLEXITY) {
    // Creating Vds values
    double Vds = Vmin_;
    if (Vmax_ > Vmin_) {
        while (Vds <= Vmax_) {
            Params_Vds_.push_back(Vds);
            Vds += Vstep_;
        }
    }else if(Vmax_ < Vmin_) {
		while (Vds >= Vmax_) {
			Params_Vds_.push_back(Vds);
			Vds += Vstep_;
		}
	}


    // Generate Ids values according to complexity value
    switch(COMPLEXITY) {
        case 1:
            level1_sweep(mosfet_, Params_Vgs_Ids_, Params_Vds_);
            break;

        case 2:
            level2_sweep(mosfet_, Params_Vgs_Ids_, Params_Vds_);
            break;

        case 3:
            level3_sweep(mosfet_, Params_Vgs_Ids_, Params_Vds_);
            break;

        default:
            throw std::invalid_argument("Invalid Complexity Level");
    }
}

void OutputSimulation::GraphOutputCurve(int COMPLEXITY) {
    OutputSimulation::GenerateOutputCurve(COMPLEXITY);
    // GRAPHING CURVES

    // Graph Title
    std::string NameString = "Output Curve - " + mosfet_.getName() + " - Vgs:";

    // Store vgs_pair.first values in a temporary container
    std::vector<double> vgs_values;
    for (const auto& vgs_pair : Params_Vgs_Ids_) {
        vgs_values.push_back(vgs_pair.first);
    }
    // Sort the vgs_values container
    std::sort(vgs_values.begin(), vgs_values.end());

    // Params in the Title
    for (const auto& vgs_value : vgs_values) {
        // Format the floating-point number with 2 decimal places
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << vgs_value; //To make params 2 decimal places
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
    settings->xLabel = toVector(L"Vds (V)");
    settings->yLabel = toVector(L"Ids (A)");

// Loop through Params_Vgs_Ids and create ScatterPlotSeries dynamically
    int i = 0;
    for (auto vgs_pair : Params_Vgs_Ids_) {
        ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
        series->xs = &Params_Vds_;
        series->ys = &Params_Vgs_Ids_[vgs_pair.first];
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
        WriteToFile(pngdata, "OutputCurve");
        DeleteImage(imageReference->image);
    } else {
        std::cerr << "Error: ";
        for(wchar_t c : *errorMessage->string){
            std::cerr << c;
        }
        std::cerr << std::endl;
    }

}


