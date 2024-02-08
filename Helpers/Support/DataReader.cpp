//
// Created by Doruk Tan Atila on 10/30/23.
//

#include "DataReader.h"


DataReader::DataReader(const std::string &filename, int noOfIColumn) : filename(filename) {
    this->readData(noOfIColumn);
}
bool DataReader::readData(int no_of_columns) {
    const char *FILENAME = filename.c_str();
    FILE* fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return false;
    }

    char* line = NULL;
    size_t len = 0;

    while (fgets(line, len, fp) != NULL) {
        std::vector<double> rowData;
        char* token = strtok(line, "\t");

        for (int i = 0; i < no_of_columns; ++i) {
            if (token != NULL) {
                double value;
                if (sscanf(token, "%lf", &value) == 1) {
                    rowData.push_back(value);
                    //std::cout << "Column " << i << ": " << value << " ";
                }
            }
            token = strtok(NULL, "\t");
        }

        data.push_back(rowData);
        //std::cout << std::endl; // Add a newline to separate rows
    }

    fclose(fp);
    if (line)
        free(line);

    return true;
}

const std::vector<std::vector<double>> &DataReader::getData() const {
    return data;
}



