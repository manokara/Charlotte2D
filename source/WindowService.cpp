#include "stdafx.h"
#include "WindowService.h"
#include "Error.h"
#include "ServiceLocator.h"
#include "ErrorService.h"
#include<iostream>

extern charlotte::ServiceLocator globalServiceLocator;

sf::RenderWindow* charlotte::WindowService::_window = nullptr;

charlotte::WindowService::WindowService(sf::RenderWindow& window)
{
	this->_window = &window;
}

charlotte::WindowService::~WindowService()
{

}

sf::RenderWindow* charlotte::WindowService::getSfRenderWindow()
{
	if (!this->_window)
	{
		globalServiceLocator.get<ErrorService>()->setError(CharlotteError("No SFML Window found"));
	}
	return this->_window;
}

void charlotte::WindowService::resize(sf::Vector2u& newSize)
{
	this->getSfRenderWindow()->setSize(newSize);
}

void charlotte::WindowService::changeTitle(std::string& newTitle)
{
	this->getSfRenderWindow()->setTitle(newTitle);
}