#include "stdafx.h"
#include<SFML\Graphics.hpp>
#include<iostream>
#include "animation.h"
#include"core.h"
#include"internal.h"

miwa::Animation::Animation(sf::Sprite& sprite, int cellW, int cellH, int sepH, int sepV)
{
	_sprite = &sprite;
	sf::Vector2u cell = sf::Vector2u(cellW + sepH, cellH + sepV);
	auto* stexture = sprite.getTexture();
	for (auto i = 0; i < stexture->getSize().y; i += cell.y)
	{
		for (auto j = 0; j < stexture->getSize().x; j += cell.x)
		{
			cells.push_back(sf::Rect<int>(j, i, cellW, cellH));
		}
	}
}

miwa::Animation::Animation(sf::Sprite& sprite, size_t cellW, size_t cellH, size_t sepH, size_t sepV, size_t rangeBegin, size_t rangeEnd)
{
	_sprite = &sprite;
	sf::Vector2u cell = sf::Vector2u(cellW + sepH, cellH + sepV);
	auto* stexture = sprite.getTexture();
	for (auto i = 0; i < stexture->getSize().y; i += cell.y)
	{
		for (auto j = 0; j < stexture->getSize().x; j += cell.x)
		{
			cells.push_back(sf::Rect<int>(j, i, cellW, cellH));
		}
	}
	cells.erase(cells.begin() + rangeEnd, cells.end());
	cells.erase(cells.begin(), cells.begin() + rangeBegin);
}

miwa::Animation::~Animation()
{
	
}

extern Core mainCore;

sf::Sprite& miwa::Animation::getSprite()
{
	return *_sprite;
}


sf::Sprite miwa::Animation::operator[](int n)
{
	return sf::Sprite(*_sprite->getTexture(), cells[n]);
}

size_t miwa::Animation::frameNumber()
{
	return cells.size();
}

void miwa::Animation::draw(size_t subimage, const sf::RenderStates& states)
{
	_sprite->setTextureRect(this->cells[subimage]);
	miwa::draw(*_sprite, states);
}

miwa::Animation::Animation()
{

}