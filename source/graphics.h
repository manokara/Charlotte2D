#pragma once
#include<SFML\Graphics.hpp>
#include "animation.h"
#include<map>

namespace miwa
{
	typedef sf::Sprite sSprite_t;

	class Sprite : public sSprite_t
	{
		std::map<std::string, Animation> _anim;
	public:
		Sprite(sf::Texture& tex, sf::IntRect rect);
		Sprite();
		Animation& makeAnimation(std::string name, int cellW, int cellH, int sepH, int sepV, size_t rangeBegin, size_t rangeEnd);
		Animation& makeAnimation(std::string name, int cellW, int cellH, int sepH, int sepV);
		Animation& getAnimation(std::string name);
	};


	class GameInfo
	{

	};


}