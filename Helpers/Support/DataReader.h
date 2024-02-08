//
// Created by Doruk Tan Atila on 10/30/23.
//

#ifndef MAIN_CPP_DATAREADER_H
#define MAIN_CPP_DATAREADER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>


class DataReader {
public:
    //Tab-Delimited file reading --> Create object DataReader --> Call getData() to get a 2D vector: data[0][] -> 1st column data[0][] -> 2nd column etc..
    DataReader(const std::string &filename, int noOfIColumn);
    bool readData(int noOfIColumn);
    const std::vector<std::vector<double>> &getData() const;

private:
    std::string filename;
    std::vector<std::vector<double> > data;
};

#endif //MAIN_CPP_DATAREADER_H
