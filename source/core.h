#pragma once
#include<SFML\Graphics.hpp>

sf::RenderWindow& getWindow();

namespace miwa 
{
	void initialise(sf::RenderWindow& window);

	class Draw
	{
	public:
		enum DrawTypes
		{
			Sprite, Shape
		};
		
	};
	sf::RenderWindow& getWindow();
	void draw(const sf::Drawable&, sf::RenderStates states = sf::RenderStates::Default);
}