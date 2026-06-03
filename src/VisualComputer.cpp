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

            int irritation = mb.irritationsCount(c);
            image.setPixel({x,y}, colorFromGradient(colorPalette, irritation, mb.getMaxIrritations()));
        }
    }
    
    return image;
}

sf::Color VisualComputer::colorFromGradient(const std::vector<sf::Color> &palette, int irritation, int maxIrritation) {
    double tempRatio = static_cast<double>(irritation) / static_cast<double>(maxIrritation);

    auto index = static_cast<std::size_t>(tempRatio * (palette.size() - 1));

    return palette[index];
}

// A simple palette of colors used in colorFromGradient function
const std::vector<sf::Color> VisualComputer::colorPalette = {
    sf::Color(0, 7, 100),
    sf::Color(32, 107, 203),
    sf::Color(237, 255, 255),
    sf::Color(255, 170, 0),
    sf::Color(0, 2, 0)
};

