//
// Created by jf1519 on 20/03/23.
//

#include "DataGenerator.h"
#include <random>
#include <cmath>

std::vector<double> DataGenerator::generateLargeData(unsigned int N) {
    std::vector<double> data = std::vector<double>(N);
    double max = std::numeric_limits<double>::max();
    for(unsigned int i = 0; i < N; ++i){
        data[i] = (double)std::rand()/RAND_MAX/100*std::sqrt(max);
    }
    return data;
}
