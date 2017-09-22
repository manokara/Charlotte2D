#include "stdafx.h"
#include "GameRoom.h"
#include "MainService.h"
#include<iostream>
#include "InstanceQueue.h"
#include "Error.h"

extern charlotte::ServiceLocator globalServiceLocator;

charlotte::GameRoom::GameRoom(std::string name, const std::function<void()>& callback) 
{
	this->_callback = callback;
}

charlotte::GameRoom::GameRoom()
{

}

charlotte::GameRoom::~GameRoom()
{

}

void charlotte::GameRoom::changeBackgroundColor(sf::Color color)
{
	this->backgroundColor.r = color.r;
	this->backgroundColor.g = color.g;
	this->backgroundColor.b = color.b;
	this->backgroundColor.a = color.a;
}

sf::Color& charlotte::GameRoom::getBackgroundColor()
{
	return this->backgroundColor;
}

void charlotte::GameRoom::execute(uint32_t fps)
{
	this->m_fps = fps;
	try
	{
		auto windowService = globalServiceLocator.get<WindowService>();
		auto mainService = globalServiceLocator.get<MainService>();
		windowService->getSfRenderWindow()->setFramerateLimit(fps);

		auto& room = mainService->getCurrentRoom();
		std::vector<std::shared_ptr<charlotte::Object>> perList;
		for (std::vector<std::shared_ptr<charlotte::Object>>::reverse_iterator iter = mainService->m_instances.rbegin(); iter < mainService->m_instances.rend(); ++iter)
		{
			if (iter->get()->persistent)
			{
				perList.push_back(*iter);
			}
		}
		mainService->m_instances.clear();
		mainService->m_instance_queue.getVector().clear();
		mainService->m_instances.swap(perList);
		mainService->m_current_room_pointer = this;
		_callback();
	}
	catch (const std::exception& e)
	{
		std::cerr << "PANIC: GameRoom Module: " << e.what() << std::endl;
	}
}

uint32_t charlotte::GameRoom::getFPS()
{
	return this->m_fps;
}
