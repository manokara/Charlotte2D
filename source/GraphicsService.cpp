#include "stdafx.h"
#include "GraphicsService.h"
#include "WindowService.h"
#include "Error.h"
#include<iostream>
#include"RenderTexture.h"

extern charlotte::ServiceLocator globalServiceLocator;

charlotte::GraphicsService::GraphicsService()
{
	if (!_defaultRenderTexture)
	{
		auto windowService = globalServiceLocator.get<WindowService>();
		auto windowSize = windowService->getSfRenderWindow()->getSize();
		_defaultRenderTexture = &this->makeRenderTexture(windowSize);
		_applicationRenderTexture = _defaultRenderTexture;
	}
}

charlotte::RenderTexture& charlotte::GraphicsService::makeRenderTexture(sf::Vector2u size)
{
	_textures.push_back(std::make_shared< charlotte::RenderTextureWrapper >());
	(*_textures.back()).create(size.x,size.y);
	return *_textures.back();
}

void charlotte::GraphicsService::destroyRenderTexture(charlotte::RenderTexture& target)
{
	int i = 0;
	decltype(this->_textures)::iterator iter = this->_textures.end();
	for (std::shared_ptr<charlotte::RenderTexture>& it : this->_textures)
	{
		if (it->getID() == target.getID())
		{
			iter = this->_textures.begin() + i;
			break;
		}
		i++;
	}
	if (iter != _textures.end())
	{
		_textures.erase(iter);
	}
}

void charlotte::GraphicsService::clear(sf::Color& color)
{
	this->_applicationRenderTexture->clear(color);
}

void charlotte::GraphicsService::update()
{
	auto service = globalServiceLocator.get<charlotte::WindowService>();
	this->_applicationRenderTexture->display();
	sf::Sprite tar(this->_applicationRenderTexture->getTexture());
	service->getSfRenderWindow()->draw(tar);
}

charlotte::RenderTexture& charlotte::GraphicsService::getApplicationRenderTexture()
{
	return *(this->_applicationRenderTexture);
}

void charlotte::GraphicsService::setRenderTextureTarget(charlotte::RenderTexture& textureTarget)
{
	this->_applicationRenderTexture = &textureTarget;
}

void charlotte::GraphicsService::draw(const sf::Drawable& dw, sf::RenderStates states)
{
	this->_applicationRenderTexture->draw(dw, states);
}

void charlotte::GraphicsService::resetRenderTextureTarget()
{
	this->_applicationRenderTexture = _defaultRenderTexture;
}