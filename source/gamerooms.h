#pragma once

#include<vector>
#include<memory>
#include<functional>
#include "objects.h"

namespace miwa {
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
	namespace loop {
		void destroyObject(Object* objPtr);
		bool findObject(Object* objPtr);
		void clearObjects();
		void startLoop();
	}
}