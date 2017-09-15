#include "stdafx.h"
#include "gamerooms.h"
#include"core.h"
#include<iostream>
#include"internal.h"
#include"engineError.h"
#include"internal.h"

std::vector<std::shared_ptr<miwa::Object>> instanceM;

typedef std::vector<std::shared_ptr<miwa::Object>> smartInstanceVector_t;

miwa::GameRoom* currentGameRoomPtr = nullptr;

size_t loopVectorPos = 0;

size_t watafoka = 0;

extern Core mainCore;


miwa::GameRoom::GameRoom(std::string name, const std::function<void()>& callback)
{
	this->_callback = callback;
}

miwa::GameRoom::GameRoom()
{

}

miwa::GameRoom::~GameRoom()
{

}

void miwa::GameRoom::changeBackgroundColor(sf::Color color)
{
	this->backgroundColor.r = color.r;
	this->backgroundColor.g = color.g;
	this->backgroundColor.b = color.b;
	this->backgroundColor.a = color.a;
}

sf::Color& miwa::GameRoom::getBackgroundColor()
{
	return this->backgroundColor;
}

bool miwa::loop::findObject(Object* objPtr)
{
	auto iter = std::find_if(instanceM.begin(), instanceM.end(), [&objPtr](decltype(*instanceM.begin())& e) {
		return e.get() == objPtr;
	});
	return iter != instanceM.end();
}

extern instanceQueue instQ;

extern bool selfDest;

uint32_t miwa::GameRoom::getFPS()
{
	return this->_fps;
}

void miwa::loop::destroyObject(Object* objPtr)
{
	auto iter = std::find_if(instanceM.begin(), instanceM.end(),[objPtr]( std::weak_ptr<Object> i)
	{
		return i.lock().get() == objPtr;
	});
	
	if (iter == instanceM.end())
	{
		throw GameSysError("O objeto não está na lista de instâncias");
	}
	else {
		auto dist = static_cast<decltype(loopVectorPos)>(std::distance(instanceM.begin(), iter));
		if (dist < loopVectorPos)
		{
			watafoka++;
		}
		instanceM.erase(iter);
		auto it = std::find_if(instQ.getVector().begin(), instQ.getVector().end(), [objPtr](std::weak_ptr<Object> i)
		{
			return i.lock().get() == objPtr;
		});
		if (it->lock().get() == instQ.top().lock().get())
		{
			selfDest = true;
			instQ.pop();
		}
	}
}

void miwa::loop::clearObjects()
{
	instanceM.clear();
	instQ.getVector().clear();
}

void miwa::loop::startLoop()
{
	mainCore.loop();
}

void miwa::GameRoom::execute(uint32_t fps)
{
	this->_fps = fps;
	try
	{
		mainCore._window->setFramerateLimit(fps);

		auto& room =  *mainCore.currentRoomPointer;
		std::vector<std::shared_ptr<miwa::Object>> perList;
		for (std::vector<std::shared_ptr<miwa::Object>>::reverse_iterator iter = instanceM.rbegin(); iter < instanceM.rend(); ++iter)
		{
			if (iter->get()->persistent)
			{
				perList.push_back(*iter);
				std::cout << "Persistent" << std::endl;
			}
		}
		instanceM.clear();
		instQ.getVector().clear();
		instanceM.swap(perList);
		mainCore.currentRoomPointer = this;
		_callback();
	}
	catch (const std::exception& e)
	{
		std::cerr << "PANIC: GameRoom Module: " << e.what() << std::endl;
	}
}