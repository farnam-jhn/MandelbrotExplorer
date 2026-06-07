//
// Created by Farnam on 6/2/2026.
//

#include "VisualComputer.h"
#include "Mandelbrot.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdint>
#include <thread>
#include <vector>

void VisualComputer::computeImage(const Mandelbrot &mb, unsigned int width, unsigned int height, unsigned int startWidth, unsigned int startHeight, sf::Image &currentImage) const {
    std::vector<std::uint8_t> pixels(static_cast<std::size_t>(width) * height * 4, 0);

    if (startHeight >= height || startWidth >= width) {
        currentImage = sf::Image({width, height}, pixels.data());
        return;
    }

    const unsigned int rowsToCompute = height - startHeight;
    const unsigned int requestedThreadCount = std::max(10u, std::thread::hardware_concurrency());
    const unsigned int threadCount = std::min(requestedThreadCount, rowsToCompute);
    const unsigned int rowsPerThread = (rowsToCompute + threadCount - 1) / threadCount;

    std::vector<std::thread> workers;
    workers.reserve(threadCount);

    for (unsigned int threadIndex = 0; threadIndex < threadCount; threadIndex++) {
        const unsigned int yBegin = startHeight + threadIndex * rowsPerThread;
        const unsigned int yEnd = std::min(yBegin + rowsPerThread, height);

        /* Creates a new thread (in anonymous form) and adds it to workers vector
         * this is beneficial for joining the threads.
         */
        workers.emplace_back([&, yBegin, yEnd]() {
            // Loops through this thread's rows and checks if each pixel is in the set.
            for (unsigned int y = yBegin; y < yEnd; y++) {
                for (unsigned int x = startWidth; x < width; x++) {
                    /* Pixels in the image are saved in an array;
                     * this means that coordinating system in the image and cartesian coordinating
                     * systems are distinct
                     */
                    double realC = (x - WIDTH / 2.0) * SCALE - 0.5; // maps each pixel on the image to a point on cartesian coordinating system.
                    double imagC = (y - HEIGHT / 2.0) * SCALE;

                    std::complex<double> c(realC, imagC);

                    int iteration = mb.iterationsCount(c);
                    sf::Color color = smoothColor(colorPalette, iteration, mb.getMaxIterations());

                    const std::size_t pixelIndex = (static_cast<std::size_t>(y) * width + x) * 4;
                    pixels[pixelIndex] = color.r;
                    pixels[pixelIndex + 1] = color.g;
                    pixels[pixelIndex + 2] = color.b;
                    pixels[pixelIndex + 3] = color.a;
                }
            }
        });
    }

    for (std::thread &worker : workers) {
        worker.join();
    }

    currentImage = sf::Image({width, height}, pixels.data());
}

// Gives a color for each iteration amount
sf::Color VisualComputer::smoothColor(const std::vector<sf::Color> &palette, int iteration, int maxIterations) const {
    if (iteration >= maxIterations) {
        return palette.back();
    }

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
sf::Color VisualComputer::lerpColor(sf::Color color1, sf::Color color2, double t) const {
    // Lambda form im lerp
    auto lerp = [t](std::uint8_t x, std::uint8_t y) {
        return static_cast<std::uint8_t>(x + (y - x) * t);
    };

    return sf::Color(
      lerp(color1.r, color2.r),
      lerp(color1.g, color2.g),
      lerp(color1.b, color2.b),
      lerp(color1.a, color2.a)
    );
}

unsigned int VisualComputer::getWidth() const{
    return static_cast<unsigned int>(WIDTH);
}

unsigned int VisualComputer::getHeight() const{
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
