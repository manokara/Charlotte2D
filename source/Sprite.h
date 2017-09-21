#pragma once

#include "Animation.h"
#include<SFML\Graphics.hpp>

namespace charlotte {
	class SpriteWrapper : public sf::Sprite
	{
		std::map<std::string, Animation> _anim;
		int32_t _guid = -1;
	public:
		SpriteWrapper(sf::Texture& tex, sf::IntRect rect);
		SpriteWrapper();
		Animation& makeAnimation(std::string name, int cellW, int cellH, int sepH, int sepV, size_t rangeBegin, size_t rangeEnd);
		Animation& makeAnimation(std::string name, int cellW, int cellH, int sepH, int sepV);
		Animation& getAnimation(std::string name);
		int32_t getID();
	};
	typedef SpriteWrapper Sprite;
}