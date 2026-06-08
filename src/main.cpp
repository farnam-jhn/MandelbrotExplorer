#include <SFML/Graphics.hpp>
#include "Mandelbrot.h"
#include "VisualComputer.h"

#include <optional>

int main() {
	const Mandelbrot MB;
	const VisualComputer vc;

	sf::RenderWindow window( sf::VideoMode( {vc.getWidth(),vc.getHeight()} ), "Mandelbrot Explorer" );
	sf::Image image({vc.getWidth(),vc.getHeight()}, sf::Color::Black);
	vc.computeImage(MB, vc.getWidth(), vc.getHeight(), 0, 0, image);


	sf::Texture texture(image);
	sf::Sprite sprite(texture);

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}
		window.clear();
		window.draw(sprite);
		window.display();
	}
}
