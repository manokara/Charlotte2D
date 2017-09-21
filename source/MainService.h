#pragma once
#include<SFML\Graphics.hpp>
#include "ServiceLocator.h"
#include "WindowService.h"
#include "GameRoom.h"
#include "InstanceQueue.h"
#include "Object.h"
#include "CharlotteServices.h"
#include "AssetGUIDService.h"

namespace charlotte 
{
	/*
	*
	*/

	class MainService : public Service
	{
	public:
		MainService();
		
		~MainService();

		void changeFrameRate(uint32_t FPS);

		void update();
		
		void destroyObject(Object* objPtr);
		
		bool findObject(Object* objPtr);

		void insertObject(void* objPtr);
		
		void clearObjects();

		GameRoom& getCurrentRoom();

		friend class GameRoom;

	private:
		CharlotteServices services;
		std::vector<std::shared_ptr<Object>> instanceM;
		sf::Event _events;
		uint32_t _fps = 60;
		instanceQueue instQ;
		size_t watafoka;
		size_t loopVectorPos;
		bool selfDest = false;
		charlotte::GameRoom* _currentRoomPtr = nullptr;
	};
}