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
    private:
    static sf::Color colorFromGradient(const std::vector<sf::Color> &palette, int irritation, int maxIrritation);

    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;
    static constexpr double SCALE = 4.0 / WIDTH;

    static const std::vector<sf::Color> colorPalette;
};


#endif //CMAKESFMLPROJECT_VISUALCOMPUTER_H
