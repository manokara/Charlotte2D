#pragma once
#include<SFML/Graphics.hpp>
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
		CharlotteServices m_services;
		std::vector<std::shared_ptr<Object>> m_instances;
		sf::Event m_event;
		uint32_t m_fps = 60;
		instanceQueue m_instance_queue;
		size_t watafoka;
		size_t m_loop_index;
		bool m_loop_index_destruction = false;
		charlotte::GameRoom* m_current_room_pointer = nullptr;
	};
}