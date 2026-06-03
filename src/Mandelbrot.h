//
// Created by Farnam on 5/31/2026.
//

#ifndef CMAKESFMLPROJECT_MANDELBROT_H
#define CMAKESFMLPROJECT_MANDELBROT_H

#include <complex>

class Mandelbrot {
public:
int iterationsCount(std::complex<double> c);
int getMaxIterations() const;

private:
    const int MAX_ITERATIONS = 500;
    const double MAX_MAGNITUDE = 2.0;
};


#endif //CMAKESFMLPROJECT_MANDELBROT_H
