//
// Created by Farnam on 5/31/2026.
//

#include <complex>
#include "Mandelbrot.h"

/* Checks if: Z(n+1) = Z^(n) + C diverges or not
 * This approach is approximate as it doesn't actually check for the sequence divergence.
 * see "C++ Implementation" in docs folder.
 */

int Mandelbrot::iterationsCount(std::complex<double> c) const {
    std::complex<double> z (0,0); // Initial value for z (z(0)) should be 0 + 0i
    int iteration = 0;

    while (iteration < MAX_ITERATIONS) {
        z = z * z + c; // the formula for mandelbrot function

        /* Approach bellow is used so we can skip using sqrt.
            * another slower approach is to check if :
            *      std::abs(z) >= MAX_MAGNITUDE
            * this is slower as the std::abs function uses square roots.
            */
        if (std::norm(z) >= MAX_MAGNITUDE * MAX_MAGNITUDE) {
            break;
        }
        iteration++;
    }

    return iteration;
}

int Mandelbrot::getMaxIterations() const {
    return MAX_ITERATIONS;
}
