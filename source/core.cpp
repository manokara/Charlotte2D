#include"stdafx.h"
#include"preproc.h"
#include"miwa.h"
#include<vector>
#include<memory>
#include<queue>
#include<iostream>
#include"internal.h"
#include"keyboard.h"
#include<GL\glew.h>
#include<SFML\OpenGL.hpp>

extern std::vector<std::shared_ptr<miwa::Object>> instanceM;

miwa::input::MKeyboard keyboardManager;

Core mainCore;

void miwa::draw(const sf::Drawable& d, const sf::RenderStates states)
{
	miwa::getWindow().draw(d, states);
}

sf::RenderWindow& miwa::getWindow()
{
	return *mainCore._window;
}


Core::Core()
{

}

void miwa::initialise(sf::RenderWindow& window)
{
	mainCore = Core();
	mainCore._window = &window;
	window.setActive(false);
	miwa::externalFiles::fillFileBuffer();
}

void Core::initialise(sf::RenderWindow& window)
{
	this->_window = &window;
}

sf::RenderWindow& getWindow()
{
	return *mainCore._window;
}

void Core::changeFrameRate(uint32_t fps)
{
	this->_fps = fps;
	this->_window->setFramerateLimit(fps);
}

extern size_t watafoka;
extern size_t loopVectorPos;

#ifndef PRIORITY_LOOP_EXEC

void Core::loop()
{
	try {
		if (!this->_window)
		{
			throw GameSysError("Cade a janela?");
		}
		bool quit = false;
		sf::Clock deltaC;
		while (!quit) {
			const sf::Time deltaT = deltaC.restart();
			this->_window->pollEvent(this->_events);
			switch (this->_events.type)
			{
			case sf::Event::Closed:
				this->_window->close();
				quit = true;
				break;
			}
			this->_window->clear(mainCore.currentRoomPointer->getBackgroundColor());
			for (auto iter = 0; iter != instanceM.size(); ++iter)
			{
				loopVectorPos = iter;
				if (instanceM[iter].get()->update) {
					instanceM[iter].get()->update();
				}
				iter -= watafoka;
				bool cancel = watafoka != 0;
				watafoka = 0;
				if (!cancel) {
					if (instanceM[iter].get()->render) {
						instanceM[iter].get()->render();
					}
				}
				iter -= watafoka;
				watafoka = 0;
			}
			this->_window->display();

			sf::sleep(sf::microseconds(1));
		}
	}
	catch (GameSysError& err)
	{
		std::cerr << "PANIC: Core Module: " << err.what() << std::endl;
		system("pause");
	}
}
#else

bool WeakPtrForQueue::operator<(const WeakPtrForQueue& e)
const
{
	return e.lock().get()->priority < lock().get()->priority;
}

WeakPtrForQueue::WeakPtrForQueue(std::shared_ptr<miwa::Object>& obj) : weak_ptr(obj)
{

}

instanceQueue::instanceQueue()
{

}

instanceQueue::~instanceQueue()
{

}

std::vector<WeakPtrForQueue>::iterator instanceQueue::begin()
{
	return c.begin();
}
std::vector<WeakPtrForQueue>::iterator instanceQueue::end()
{
	return c.end();
}

std::vector<WeakPtrForQueue>& instanceQueue::getVector()
{
	return c;
}

WeakPtrForQueue& instanceQueue::operator[](int n)
{
	return *(c.begin() + n);
}

void instanceQueue::pushd(std::shared_ptr<miwa::Object>& obj)
{
	push(WeakPtrForQueue(obj));
}


instanceQueue instQ;

bool selfDest = false;

void Core::loop()
{
	try {
		if (!this->_window)
		{
			throw GameSysError("Cade a janela?");
		}
		bool quit = false;
		sf::Clock deltaC;
		while (!quit) {
			const sf::Time deltaT = deltaC.restart();
			this->_window->pollEvent(this->_events);
			switch (this->_events.type)
			{
			case sf::Event::Closed:
				this->_window->close();
				quit = true;
				break;
			}
			this->_window->clear(mainCore.currentRoomPointer->getBackgroundColor());
			for (auto& it : instanceM)
			{
				instQ.pushd(it);
			}
			uint32_t sS = 0;
			keyboardManager.update();
			
			while (!instQ.empty())
			{
				loopVectorPos = instQ.size() - 1 - sS;
				auto& cInst = instQ.top();
				selfDest = false;
				if (instQ.getVector().size() > 0) {
					if (cInst.lock()->update) {
						cInst.lock()->update();
					}
					if (instQ.getVector().size() > 0) {
						if (cInst.lock()->render) {
							cInst.lock()->render();
						}
					}
					watafoka = 0;
				}
				if (instQ.size() > 0 && !selfDest)
				{
					instQ.pop();
				}
			}
			this->_window->display();
			sf::sleep(sf::milliseconds(1000.0/static_cast<float>(mainCore.currentRoomPointer->getFPS())));
		}
	}
	catch (GameSysError& err)
	{
		std::cerr << "PANIC: Core Module: " << err.what() << std::endl;
		system("pause");
	}
}
#endif

Core::~Core()
{

}