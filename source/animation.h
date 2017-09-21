#pragma once

#include<SFML\Graphics.hpp>

namespace charlotte
{
	class Animation
	{
	public:
		Animation();
		~Animation();
		Animation(sf::Sprite& tex, int cellW, int cellH, int sepH, int sepV);
		Animation(sf::Sprite& tex, size_t cellW, size_t cellH, size_t sepH, size_t sepV, size_t rangeBegin, size_t rangeEnd);
		sf::Sprite& getSprite();
		void draw(size_t subimage, const sf::RenderStates& states = sf::RenderStates::Default);
		size_t charlotte::Animation::frameNumber();
		sf::Sprite operator[](int);
	private:
		std::vector<sf::Rect<int>> cells;
		sf::Sprite* _sprite;
	};
}