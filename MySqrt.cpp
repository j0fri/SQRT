//
// Created by jf1519 on 21/03/23.
//

#include "MySqrt.h"
#include <iostream>
#include <cmath>
#include <bitset>

//First version with dynamic convergence
//double MySqrt::sqrt(double x) {
//    static double tol = 0.001;
//    double y = 1;
//    double err = y*y - x;
//    while(err < 0 || err/x > tol){
//        y -= err/(2*y);
//        err = y*y - x;
//    }
//    return y;
//}
//Benchmark: 3.3s per million

//Just guessing
//double MySqrt::sqrt(double x) {
//    double y = 10;
//    y -= (y*y - x)/(2*y);
//    y -= (y*y - x)/(2*y);
//    y -= (y*y - x)/(2*y);
//    y -= (y*y - x)/(2*y);
//    y -= (y*y - x)/(2*y);
//    y -= (y*y - x)/(2*y);
//    y -= (y*y - x)/(2*y);
//    y -= (y*y - x)/(2*y);
//    return y;
//}
//Benchmark: 0.017 per million

//initial guess by power
//double MySqrt::sqrt(double x) {
//    double pow = 1;
//    while(pow*pow < x){
//        pow *= 10;
//    }
//    double y = pow;
//    y -= 0.5*(y - x/y);
//    y -= 0.5*(y - x/y);
//    y -= 0.5*(y - x/y);
//    y -= 0.5*(y - x/y);
//    y -= 0.5*(y - x/y);
//    y -= 0.5*(y - x/y);
//    y -= 0.5*(y - x/y);
//    y -= 0.5*(y - x/y);
//    return y;
//}
//Benchmark: 0.17s per million.

//initial guess by power with bitshift
//double MySqrt::sqrt(double x) {
//    long long yi = ((*(long long*) &x >> 52) - 1023) >> 1; //Get half power
//    yi = ((((yi + 1023) << 1) | 1UL) << 51); //Double format
//    double y = *(double*) &yi;
//    y -= 0.5*(y - x/y);
//    y -= 0.5*(y - x/y);
//    y -= 0.5*(y - x/y);
//    y -= 0.5*(y - x/y);
//    return y;
//}
//Benchmark: 0.0068 per million :)

//Helpers:
double log2approx(const double& x){
    //std::cout << std::endl << "Forward: " << std::endl;
    double xi = (double) (*(long long*) &x);
    //std::cout << "initial cast: " << xi << ", bits: " << std::bitset<64>(*(long long*) &xi) << std::endl;
    //unsigned long long int expmask = 0x7FF0000000000000ULL; //1 only at exp locations
    unsigned long long int antiexpmask = 0xFFFFFFFFFFFFFULL; //12 zeros, 52 ones
    unsigned long long int exp = (*(long long*) &xi) >> 52;
    unsigned long long int newexp = exp - 52ULL; //52 for log + 1 for halflog
    //std::cout << "newexp: " << newexp << std::endl << "newexp-1: " << newexp - 1ULL << std::endl;
    unsigned long long int result = ((*(long long*)&xi) & antiexpmask) | (newexp << 52);
    double log = *(double *) &result + 0.043 - 1023;
    return log;
}
double exp2approx(double x){
    //std::cout << std::endl<< std::endl<< std::endl<< "Backward: " << std::endl;
    //std::cout << std::endl << "x: " << x << ", bits: " << std::bitset<64>(*(unsigned long long int*)&x) << std::endl;
    double invSum = x - 0.043 + 1023;

    unsigned long long int result = *(unsigned long long int*) &invSum;
    //std::cout << std::endl << "invSum: " << invSum << ", bits: " << std::bitset<64>(result) << std::endl;
    unsigned long long int newexp = result >> 52;
    //std::cout << "newexp: " << newexp << std::endl;
    unsigned long long int exp = newexp + 52ULL;
    //std::cout << "exp: " << exp << std::endl << ", bits: " << std::bitset<64>(exp) <<  std::endl;
    unsigned long long int antiexpmask = 0xFFFFFFFFFFFFFULL; //12 zeros, 52 ones
    unsigned long long int xidi = (result & antiexpmask) | (exp << 52);
    //std::cout << "xidi: " << *(double*) &xidi << std::endl <<", bits: " << std::bitset<64>(xidi) <<  std::endl;
    unsigned long long int xi = (long long)    *(double *) &xidi;
    //std::cout << "xi: " << *(double*) &xi << std::endl <<", bits: " << std::bitset<64>(xi) <<  std::endl;

    return *(double*) &xi;
}

//log division
double MySqrt::sqrt(double x) {
    double xi = (double) (*(long long*) &x);
    //std::cout << "initial cast: " << xi << ", bits: " << std::bitset<64>(*(long long*) &xi) << std::endl;
    //unsigned long long int expmask = 0x7FF0000000000000ULL; //1 only at exp locations
    unsigned long long int antiexpmask = 0xFFFFFFFFFFFFFULL; //12 zeros, 52 ones
    unsigned long long int exp = (*(long long*) &xi) >> 52;
    unsigned long long int newexp = exp - 52ULL; //52 for log + 1 for halflog
    //std::cout << "newexp: " << newexp << std::endl << "newexp-1: " << newexp - 1ULL << std::endl;
    unsigned long long int result = ((*(long long*)&xi) & antiexpmask) | (newexp << 52);
    double log2 = *(double *) &result + 0.043 - 1023;
    log2 /= 2;
    //double y = exp2approx(log2);
    double invSum = log2 - 0.043 + 1023;

    result = *(unsigned long long int*) &invSum;
    //std::cout << std::endl << "invSum: " << invSum << ", bits: " << std::bitset<64>(result) << std::endl;
    newexp = result >> 52;
    //std::cout << "newexp: " << newexp << std::endl;
    exp = newexp + 52ULL;
    //std::cout << "exp: " << exp << std::endl << ", bits: " << std::bitset<64>(exp) <<  std::endl;
    //unsigned long long int antiexpmask = 0xFFFFFFFFFFFFFULL; //12 zeros, 52 ones
    unsigned long long int xidi = (result & antiexpmask) | (exp << 52);
    //std::cout << "xidi: " << *(double*) &xidi << std::endl <<", bits: " << std::bitset<64>(xidi) <<  std::endl;
    unsigned long long int xi2 = (long long)    *(double *) &xidi;
    //std::cout << "xi: " << *(double*) &xi << std::endl <<", bits: " << std::bitset<64>(xi) <<  std::endl;

    double y = *(double*) &xi2;
//    y -= 0.5*(y - x/y);
//    y -= 0.5*(y - x/y);
//    y -= 0.5*(y - x/y);
    return y;
}
//Benchmark: 0.0068 per million :)