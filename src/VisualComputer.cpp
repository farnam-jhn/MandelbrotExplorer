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

            int iteration = mb.iterationsCount(c);
            image.setPixel({x,y}, smoothColor(colorPalette, iteration, mb.getMaxIterations()));
        }
    }
    
    return image;
}

// Gives a color for each iteration amount
sf::Color VisualComputer::smoothColor(const std::vector<sf::Color> &palette, int iteration, int maxIterations) {
    double t = static_cast<double>(iteration) / static_cast<double>(maxIterations);
    double scaled = t * (palette.size() - 1);

    std::size_t i = static_cast<std::size_t>(scaled);
    std::size_t j = std::min(i + 1, palette.size() - 1); // next index after i but bounded
    double fraction = scaled - i;

    // Generates a color between palette[i] and palette[j]
    return lerpColor(palette[i], palette[j], fraction);
}

/* This function generates a color between two colors
 * it benefits from linear interpolation (aka. lerp)
 * for more info check docs.
 */
sf::Color VisualComputer::lerpColor(sf::Color color1, sf::Color color2, double t) {
    // Lambda form im lerp
    auto lerp = [t](std::uint8_t x, std::uint8_t y) {
        return (x + (y - x) * t);
    };

    return sf::Color(
      lerp(color1.r, color2.r),
      lerp(color1.g, color2.g),
      lerp(color1.b, color2.b),
      lerp(color1.a, color2.a)
    );
}

unsigned int VisualComputer::getWidth(){
    return static_cast<unsigned int>(WIDTH);
}

unsigned int VisualComputer::getHeight(){
    return static_cast<unsigned int>(HEIGHT);
}

// A palette of colors used in smoothColor function (AI generated btw :0)
const std::vector<sf::Color> VisualComputer::colorPalette = {
    sf::Color(8, 10, 25),        // Very dark blue-black background
    sf::Color(15, 20, 45),       // Deep space blue
    sf::Color(25, 35, 70),       // Dark navy
    sf::Color(35, 55, 100),      // Deep blue
    sf::Color(50, 80, 130),      // Rich blue
    sf::Color(70, 105, 160),     // Vibrant blue
    sf::Color(95, 130, 185),     // Bright blue
    sf::Color(120, 155, 205),    // Soft blue
    sf::Color(145, 180, 220),    // Light blue
    sf::Color(170, 200, 230),    // Pale blue-cyan
    sf::Color(190, 215, 235),    // Very pale cyan
    sf::Color(210, 225, 230),    // Near-white
    sf::Color(235, 210, 180),    // Warm gold
    sf::Color(245, 180, 130),    // Orange-gold
    sf::Color(250, 145, 90),     // Bright orange
    sf::Color(250, 110, 60),     // Deep orange
    sf::Color(245, 80, 45),      // Red-orange
    sf::Color(235, 55, 40),      // Vermilion
    sf::Color(210, 40, 40),      // Crimson
    sf::Color(170, 30, 45),      // Dark red
    sf::Color(120, 22, 42),      // Maroon
    sf::Color(70, 15, 35),       // Very dark red
    sf::Color(30, 8, 25),        // Almost black red
    sf::Color(0, 0, 0)           // MANDELBROT SET INTERIOR (pure black)
};