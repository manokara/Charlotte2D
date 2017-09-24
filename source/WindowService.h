#pragma once

#include "ServiceLocator.h"
#include "Error.h"
#include<SFML/Graphics.hpp>
#include<memory>
#include<string>

namespace charlotte {	
	/*
	*Brief ->
	*
	*	Window Service-
	*	A class to Window management
	*/

	class WindowService : public Service
	{
	private:
		static sf::RenderWindow* _window;
	
	public:
		WindowService(sf::RenderWindow& window);

		~WindowService();

		sf::RenderWindow* getSfRenderWindow();

		void resize(sf::Vector2u& newSize);

		void changeTitle(std::string& newTitle);
	};
}