#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include "DataGenerator.h"
#include "MySqrt.h"

void benchmark(std::vector<double>& data, std::vector<double>& output, double (*func)(double), bool store){
    if (store){
        for(unsigned int i = 0; i < (unsigned int) data.size(); ++i){
            output[i] = func(data[i]);
        }
    }else{
        for(unsigned int i = 0; i < (unsigned int) data.size(); ++i){
            func(data[i]);
        }
    }
}

void standardTest(double (*func)(double)){
    std::vector<int> powers = {-100, -10, 0, 1, 2, 6, 100};
    //std::vector<int> powers = {0};
    for (auto power: powers){
        double x = 2 * std::pow(10,power);
        std::cout << std::setprecision(10);
        std::cout << "x = " << x << std::endl;
        std::cout << "library sqrt: " << std::sqrt(x) << std::endl;
        std::cout << "my sqrt: " << func(x) << std::endl << std::endl;
    }

}

int main(int argc, char **argv) {
    unsigned int N = 10000;
    unsigned int reps = 1000000;

    auto data = DataGenerator::generateLargeData(N);
    std::vector<double> outputLibrary = std::vector<double>(N);
    std::vector<double> myOutput = std::vector<double>(N);

    for(unsigned int rep = 0; rep < reps; ++rep){
        if (rep == 0){
            benchmark(data, outputLibrary, std::sqrt, true);
            benchmark(data, myOutput, MySqrt::sqrt, true);
        }else{
            benchmark(data, outputLibrary, std::sqrt, false);
            benchmark(data, myOutput, MySqrt::sqrt, false);
        }
    }

//    std::cout << "Tests: " << std::endl;
//    std::cout << std::setprecision(10);
//    std::cout << "x: " << data[0] << std::endl;
//    std::cout << "library: " << outputLibrary[0] << std::endl;
//    std::cout << "mySqrt: " << myOutput[0] << std::endl << std::endl;
//    std::cout << "x: " << data[1] << std::endl;
//    std::cout << "library: " << outputLibrary[1] << std::endl;
//    std::cout << "mySqrt: " << myOutput[1] << std::endl << std::endl;
//    std::cout << "x: " << data[2] << std::endl;
//    std::cout << "library: " << outputLibrary[2] << std::endl;
//    std::cout << "mySqrt: " << myOutput[2] << std::endl << std::endl;

    standardTest(MySqrt::sqrt);
}


