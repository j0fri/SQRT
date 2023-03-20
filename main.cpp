#include <iostream>
#include <vector>
#include "DataGenerator.h"

int main(int argc, char **argv) {
    std::cout << "Hello" << std::endl;
    auto data = DataGenerator::generateData(10);
}
