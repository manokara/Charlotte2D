#pragma once

#include<vector>
#include<memory>
#include<functional>
#include<SFML\Graphics.hpp>
namespace charlotte {
	class GameRoom
	{
		std::function<void()> _callback;
		sf::Color backgroundColor;
		uint32_t _fps;
	public:
		void changeBackgroundColor(sf::Color color);
		sf::Color& getBackgroundColor();
		GameRoom(std::string name, const std::function<void()>& callback);
		~GameRoom();
		GameRoom();
		void execute(uint32_t fps);
		uint32_t getFPS();
	};
}