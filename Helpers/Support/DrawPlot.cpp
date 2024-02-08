//
// Created by Doruk Tan Atila on 10/29/23.
//

#include "DrawPlot.h"

void TabularReadGraph(std::string filename, std::vector<double> titleVector, std::vector<std::vector<double> > MeasurementData) {
    //GRAPHING CURVES
    std::string NameString = "MeasuredCurves" "-";
    for (int i = 0; i < titleVector.size(); ++i) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << titleVector[i];
        NameString += oss.str();
        if (i < titleVector.size() - 1) {
            NameString += "/";
        }
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
    settings->xLabel = toVector(L"V (V)");
    settings->yLabel = toVector(L"I (A)");

    // Loop through Params_Vgs_Ids and create ScatterPlotSeries dynamically
    for (size_t i = 1; i < MeasurementData[0].size(); ++i) {
        ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
        series->xs = new std::vector<double>(); // Common x-axis is the first column
        series->ys = new std::vector<double>(); // Create a new vector for each y-series

        // Iterate over rows to populate the x-series (common x-axis)
        for (size_t j = 0; j < MeasurementData.size(); ++j) {
            series->xs->push_back(MeasurementData[j][0]);
        }

        // Iterate over rows to populate the y-series
        for (size_t j = 0; j < MeasurementData.size(); ++j) {
            series->ys->push_back(MeasurementData[j][i]); // Each subsequent row is a value in the y-series
        }

        series->linearInterpolation = true;
        series->lineType = toVector(L"solid");
        series->lineThickness = 2;
        series->color = CreateRGBColor(0.66 / (0.3 * i + 1), 0.75 / (0.3 * i + 1), 1 / (0.3 * i + 1));

        settings->scatterPlotSeries->push_back(series);

    }


    success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

    if (success) {
        std::vector<double> *pngdata = ConvertToPNG(imageReference->image);
        WriteToFile(pngdata, "ResultCurve");
        DeleteImage(imageReference->image);
    } else {
        std::cerr << "Error: ";
        for (wchar_t c: *errorMessage->string) {
            std::cerr << c;
        }
        std::cerr << std::endl;
    }
}

void ManualGraph(std::string titlevar, std::vector<std::vector<double>> MeasurementData) {
    //GRAPHING CURVES
    std::string NameString = "ManualGraph" "-" + titlevar;
    wchar_t *title = stringToWideChar(NameString);

    bool success;
    StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
    RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = imageW;
    settings->height = imageL;
    settings->autoBoundaries = true;
    settings->title = toVector(title);
    settings->xLabel = toVector(L"V (V)");
    settings->yLabel = toVector(L"I (A)");

    // Loop through Params_Vgs_Ids and create ScatterPlotSeries dynamically
    for (size_t i = 1; i < MeasurementData[0].size(); ++i) {
        ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
        series->xs = new std::vector<double>(); // Common x-axis is the first column
        series->ys = new std::vector<double>(); // Create a new vector for each y-series

        // Iterate over rows to populate the x-series (common x-axis)
        for (size_t j = 0; j < MeasurementData.size(); ++j) {
            series->xs->push_back(MeasurementData[j][0]);
        }

        // Iterate over rows to populate the y-series
        for (size_t j = 0; j < MeasurementData.size(); ++j) {
            series->ys->push_back(MeasurementData[j][i]); // Each subsequent row is a value in the y-series
        }

        series->linearInterpolation = true;
        series->lineType = toVector(L"solid");
        series->lineThickness = 2;
        series->color = CreateRGBColor(0.66 / (0.3 * i + 1), 0.75 / (0.3 * i + 1), 1 / (0.3 * i + 1));

        settings->scatterPlotSeries->push_back(series);

    }

    success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

    if (success) {
        std::vector<double> *pngdata = ConvertToPNG(imageReference->image);
        WriteToFile(pngdata, "ResultCurve");
        DeleteImage(imageReference->image);
    } else {
        std::cerr << "Error: ";
        for (wchar_t c: *errorMessage->string) {
            std::cerr << c;
        }
        std::cerr << std::endl;
    }
}
