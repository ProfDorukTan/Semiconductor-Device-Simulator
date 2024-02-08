//
// Created by Doruk Tan Atila on 11/12/23.
//

#include "OutputSimulation.h"

OutputSimulation::OutputSimulation(MOSFET mosfet_par, double Vmin_var, double Vmax_var, double Vstep_var, const std::vector<double> &params_Vgs) :
        mosfet_(mosfet_par), Vmin_(Vmin_var), Vmax_(Vmax_var), Vstep_(Vstep_var){

    // Set up the mapping of vgs values to empty vector of Ids values
    for (auto vgs: params_Vgs) {
        Params_Vgs_Ids_[vgs] = std::vector<double>();
    }
}

double OutputSimulation::getVmin() const {
    return Vmin_;
}
double OutputSimulation::getVmax() const {
    return Vmax_;
}
double OutputSimulation::getVstep() const {
    return Vstep_;
}
const std::unordered_map<double,std::vector<double>> &OutputSimulation::getParams_Vgs_Ids() const {
    return Params_Vgs_Ids_;
}

void OutputSimulation::GenerateOutputCurve(int COMPLEXITY) {
    double Vds;

    Vds = Vmin_;
    // Iterate starting from Vmin to Vmax to fill up Params_Vds
    while (Vds <= Vmax_) {
        Params_Vds_.push_back(Vds);
        Vds += Vstep_;
    }


    // Generate Ids values according to complexity value (1 or 2) and Params_Vds
    switch(COMPLEXITY) {
        case 1:
            // Iterate vgs values
            for (const auto vgs_Ids_pair : Params_Vgs_Ids_)
            {
                auto vgs = vgs_Ids_pair.first;
                // Iterate vds values
                for (const auto vds : Params_Vds_)
                {
                    Params_Vgs_Ids_[vgs].push_back(level1_calc(vgs, vds, mosfet_));
                }
            }
            break;

        case 2:
            // Iterate vgs values
            for (const auto vgs_Ids_pair : Params_Vgs_Ids_)
            {
                auto vgs = vgs_Ids_pair.first;
                // Iterate vds values
                for (const auto vds : Params_Vds_)
                {
                    Params_Vgs_Ids_[vgs].push_back(level2_calc(vgs, vds, mosfet_));
                }
            }
            break;

        default:
            throw std::invalid_argument("Invalid Complexity Level");
    }
}

void OutputSimulation::GraphOutputCurve(int COMPLEXITY) {
    OutputSimulation::GenerateOutputCurve(COMPLEXITY);
    // GRAPHING CURVES

    // Graph Title
    std::string NameString = "Output Curve (L" + std::to_string(COMPLEXITY) + ") - ";

    // Params in the Title
    for(const auto vgs_pair : Params_Vgs_Ids_){
        NameString = NameString + std::to_string(vgs_pair.first) + "/";
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


