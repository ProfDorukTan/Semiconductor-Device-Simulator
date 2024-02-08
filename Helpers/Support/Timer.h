//
// Created by Doruk Tan Atila on 11/12/23.
//

#ifndef MOSFET_SIMULATION_PROGRAM_1_TIMER_H
#define MOSFET_SIMULATION_PROGRAM_1_TIMER_H


#include <iostream>
#include <chrono>

enum TimerState {
    NOT_STARTED,
    STARTED,
    STOPPED
};

class Timer {
private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point stopTime;
    TimerState state;

public:
    Timer() : state(NOT_STARTED) {}

    void start() {
        if (state == NOT_STARTED) {
            startTime = std::chrono::high_resolution_clock::now();
            state = STARTED;
            std::cout << "Timer started." << std::endl;
        } else {
            std::cout << "Timer is already started." << std::endl;
        }
    }

    void stop() {
        if (state == STARTED) {
            stopTime = std::chrono::high_resolution_clock::now();
            state = STOPPED;
            std::cout << "Timer stopped." << std::endl;
        } else {
            std::cout << "Timer is not started or already stopped." << std::endl;
        }
    }

    void reset() {
        state = NOT_STARTED;
        std::cout << "Timer reset." << std::endl;
    }

    void measureTime() {
        if (state == STOPPED) {
            auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
            auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime);
            auto duration3 = std::chrono::duration_cast<std::chrono::seconds>(stopTime - startTime);
            std::cout << "Time taken: " << duration1.count() << "us/" << duration2.count() << "ms/" << duration3.count() << "s" << std::endl;

        } else {
            std::cout << "Timer is not stopped. Call stop() first." << std::endl;
        }
    }
};


#endif //MOSFET_SIMULATION_PROGRAM_1_TIMER_H
