#include"stdafx.h"
#include "graphics.h"

miwa::Sprite::Sprite(sf::Texture& tex, sf::IntRect rect) : sSprite_t(tex, rect)
{

}
miwa::Sprite::Sprite() : sSprite_t()
{

}
miwa::Animation& miwa::Sprite::makeAnimation(std::string name, int cellW, int cellH, int sepH, int sepV, size_t rangeBegin, size_t rangeEnd)
{
	auto iter = _anim.insert(_anim.end(),
		std::make_pair(
			name,
			miwa::Animation(*this,
				cellW,
				cellH,
				sepH,
				sepV,
				rangeBegin,
				rangeEnd)
			)
	);
	return iter->second;
}
miwa::Animation& miwa::Sprite::makeAnimation(std::string name, int cellW, int cellH, int sepH, int sepV)
{
	auto iter = _anim.insert(_anim.end(),
		std::make_pair
		(
			name,
			miwa::Animation(*this,
				cellW,
				cellH,
				sepH,
				sepV
			)
		)
	);
	return iter->second;
}
miwa::Animation& miwa::Sprite::getAnimation(std::string name)
{
	return _anim[name];
}