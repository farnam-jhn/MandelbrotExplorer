//
// Created by Farnam on 6/2/2026.
//

#ifndef CMAKESFMLPROJECT_VISUALCOMPUTER_H
#define CMAKESFMLPROJECT_VISUALCOMPUTER_H

#include "Mandelbrot.h"
#include <SFML/Graphics.hpp>
#include <vector>

class VisualComputer {
    public:
    void computeImage(const Mandelbrot &mb, unsigned int width, unsigned int height, unsigned int startWidth, unsigned int startHeight, sf::Image &currentImage) const;

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    private:
    sf::Color smoothColor(const std::vector<sf::Color> &palette, int iteration, int maxIterations) const;
    sf::Color lerpColor(sf::Color color1, sf::Color color2, double t) const;


    static constexpr int WIDTH = 1440;
    static constexpr int HEIGHT = 900;
    static constexpr double SCALE = 4.0 / WIDTH;

    static const std::vector<sf::Color> colorPalette;
};


#endif //CMAKESFMLPROJECT_VISUALCOMPUTER_H
