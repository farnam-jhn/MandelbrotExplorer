#include <SFML/Graphics.hpp>
#include "Mandelbrot.h"
#include "VisualComputer.h"
int main()
{
	sf::RenderWindow window( sf::VideoMode( {800,600} ), "Mandelbrot Explorer" );

	const Mandelbrot MB; 

	sf::Image image = VisualComputer::computeImage(MB);

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
