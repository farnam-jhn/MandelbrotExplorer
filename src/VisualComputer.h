//
// Created by Farnam on 6/2/2026.
//

#ifndef CMAKESFMLPROJECT_VISUALCOMPUTER_H
#define CMAKESFMLPROJECT_VISUALCOMPUTER_H

#include "Mandelbrot.h"
#include <SFML/Graphics.hpp>

class VisualComputer {
    public:
    static sf::Image computeImage(Mandelbrot mb);
    static unsigned int getWidth();
    static unsigned int getHeight();
    private:
    static sf::Color smoothColor(const std::vector<sf::Color> &palette, int iteration, int maxIterations);
    static sf::Color lerpColor(sf::Color color1, sf::Color color2, double t);


    static constexpr int WIDTH = 1440;
    static constexpr int HEIGHT = 900;
    static constexpr double SCALE = 4.0 / WIDTH;

    static const std::vector<sf::Color> colorPalette;
};


#endif //CMAKESFMLPROJECT_VISUALCOMPUTER_H
