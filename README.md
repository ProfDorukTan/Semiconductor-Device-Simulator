# MOSFET Simulation Software

## Introduction

This is a simulator software repository for semiconductor devices and is implemented in C++. The simulator is designed to be easy to use and to be easily extendable. It is intended for use in teaching environments but can also be utilized for research purposes.

## Referencing

This work is described in the dissertation written by Doruk Tan Atila, titled "A Novel Approach to Modelling of MOS Devices – Development of a Simulation Tool for MOSFET Analysis". The dissertation is available in the repository.

## How to Add a New Model

To add a new model, follow the steps below:

1. If your model requires a MOSFET object that is not already available (i.e., it requires different inputs), you need to implement it first:
    - Go to `MOSFET.h` and `MOSFET.cpp` and create a MOSFET constructor such as:
        ```cpp
        // LVL2 Constructor
        MOSFET(std::string name, char type, double vt, double mobility, double cox, double w, double l, double lambda);
        ```
    - Under the `Models` folder, create a new folder with the name of the model. Create necessary `.h` and `.cpp` files.
    - Include `"../MOSFET/MOSFET.h"` at the beginning of the model.
    - Define the model's functions, such as:
        ```cpp
        void XXX_sweep_output(MOSFET &mosfet, std::unordered_map<double, std::vector<double>>& Vgs_Ids_vector, std::vector<double> Vds_vector);
        void XXX_sweep_transfer(MOSFET &mosfet, std::unordered_map<double, std::vector<double>>& Vgs_Ids_vector, std::vector<double> Vds_vector);
        ```
        (Replace `XXX` with your model name)
    - Implement any other intermediate functions as needed.

2. Go to `OutputSimulation.h` and `TransferSimulation.h` and include the newly created model source file.

3. Go to `OutputSimulation.cpp` and `TransferSimulation.cpp` and alter the switch case statements to include your model:
    ```cpp
    switch (COMPLEXITY) {
        case 1:
            level1_sweep_output(mosfet_, Params_Vgs_Ids_, Params_Vds_);
            break;

        case 2:
            level2_sweep_output(mosfet_, Params_Vgs_Ids_, Params_Vds_);
            break;

        case 3:
            level3_sweep_output(mosfet_, Params_Vgs_Ids_, Params_Vds_);
            break;

        default:
            throw std::invalid_argument("Invalid Complexity Level");
    }
    ```
    (Replace `XXX` with your model name and do the same for transfer)

Your model is now added to the source code and can be simulated.

**- Doruk Tan Atila**
