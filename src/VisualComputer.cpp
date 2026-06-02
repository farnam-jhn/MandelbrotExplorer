//
// Created by Farnam on 6/2/2026.
//

#include "VisualComputer.h"
#include "Mandelbrot.h"
#include <SFML/Graphics.hpp>

sf::Image VisualComputer::computeImage(Mandelbrot mb) {
    sf::Image image({WIDTH, HEIGHT}, sf::Color::Blue);
    // loops through the image and check if each pixel is in the set or not
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            /* Pixels in the image are saved in an array;
             * this means that coordinating system in the image and cartesian coordinating
             * systems are distinct
             */
            double realC = (x - WIDTH / 2.0) * SCALE - 0.5; // maps each pixel on the image to a point on cartesian coordinating system.
            double imagC = (y - HEIGHT / 2.0) * SCALE;

            std::complex<double> c(realC, imagC);

            bool inSet = mb.isDivergent(c);
            if (inSet) {
                image.setPixel({static_cast<unsigned>(x), static_cast<unsigned>(y)}, sf::Color::Black);
            } else {
                image.setPixel({static_cast<unsigned>(x), static_cast<unsigned>(y)}, sf::Color::White);
            }
        }
    }

    return image;
}
