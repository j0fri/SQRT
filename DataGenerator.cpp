//
// Created by jf1519 on 20/03/23.
//

#include "DataGenerator.h"
#include <chrono>
#include <thread>

std::vector<double> DataGenerator::generateData(unsigned int N) {
    std::vector<double> data = std::vector<double>(N);
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds

    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(1));
    return data;
}
