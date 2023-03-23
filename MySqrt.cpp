//
// Created by jf1519 on 21/03/23.
//

#include "MySqrt.h"
#include <iostream>

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
double MySqrt::sqrt(double x) {
    long long yi = ((*(long long*) &x >> 52) - 1023) >> 1; //Get half power
    yi = ((((yi + 1023) << 1) | 1UL) << 51); //Double format
    double y = *(double*) &yi;
    y -= 0.5*(y - x/y);
    y -= 0.5*(y - x/y);
    y -= 0.5*(y - x/y);
    y -= 0.5*(y - x/y);
    return y;
}
//Benchmark: 0.0068 per million :)