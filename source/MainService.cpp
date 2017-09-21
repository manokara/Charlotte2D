#include "stdafx.h"
#include<vector>
#include<memory>
#include<queue>
#include<iostream>
#include "InstanceQueue.h"
#include "keyboard.h"
#include "ServiceLocator.h"
#include "inputService.h"
#include "WindowService.h"
#include "Error.h"
#include "MainService.h"
#include "GraphicsService.h"
#include "CharlotteMain.h"
#include "ErrorService.h"
#include "ContentService.h"
#include "AssetGUIDService.h"
#include "CharlotteServices.h"

charlotte::ServiceLocator globalServiceLocator;

charlotte::MainService::MainService()
{

}

charlotte::MainService::~MainService()
{

}

charlotte::GameRoom& charlotte::MainService::getCurrentRoom()
{
	return *this->_currentRoomPtr;
}

void charlotte::MainService::changeFrameRate(uint32_t FPS)
{
	_fps = FPS;
	globalServiceLocator.get<WindowService>()->getSfRenderWindow()->setFramerateLimit(FPS);
}

void charlotte::MainService::update()
{
	auto windowService = globalServiceLocator.get<WindowService>();
	auto inputService = globalServiceLocator.get<InputService>();
	auto mainService = globalServiceLocator.get<MainService>();
	auto graphicsService = globalServiceLocator.get<GraphicsService>();

	try {
		if (!windowService->getSfRenderWindow())
		{
			throw CharlotteError("No window found");
		}
		bool quit = false;
		sf::Clock deltaC;
		while (!quit) {
			const sf::Time deltaT = deltaC.restart();
			windowService->getSfRenderWindow()->pollEvent(this->_events);
			switch (this->_events.type)
			{
			case sf::Event::Closed:
				windowService->getSfRenderWindow()->close();
				quit = true;
				break;
			}
			graphicsService->clear(_currentRoomPtr->getBackgroundColor());
			for (auto& it : instanceM)
			{
				instQ.pushd(it);
			}
			uint32_t sS = 0;
			/*
			*	Update Input
			*/
			inputService->update();

			while (!instQ.empty())
			{
				loopVectorPos = instQ.size() - 1 - sS;
				auto& cInst = instQ.top();
				selfDest = false;
				if (instQ.getVector().size() > 0) {
					/*
					*	Call instance events
					*/
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
			graphicsService->update();
			windowService->getSfRenderWindow()->display();
			sf::sleep(sf::milliseconds(1000.0 / static_cast<float>(mainService->_currentRoomPtr->getFPS())));
		}
	}
	catch (CharlotteError& err)
	{
		std::cerr << "ERROR: " << err.what() << std::endl;
		system("pause");
	}
}

bool charlotte::MainService::findObject(Object* objPtr)
{
	auto iter = std::find_if(instanceM.begin(), instanceM.end(), [&objPtr](decltype(*instanceM.begin())& e) {
		return e.get() == objPtr;
	});
	return iter != instanceM.end();
}

void charlotte::MainService::destroyObject(Object* objPtr)
{
	auto iter = std::find_if(instanceM.begin(), instanceM.end(), [objPtr](std::weak_ptr<Object> i)
	{
		return i.lock().get() == objPtr;
	});

	if (iter == instanceM.end())
	{
		globalServiceLocator.get<charlotte::ErrorService>()->setError( CharlotteError("The object is not in the list of instances" ) );
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

void charlotte::MainService::clearObjects()
{
	instanceM.clear();
	instQ.getVector().clear();
}

extern charlotte::ServiceLocator globalServiceLocator;

void charlotte::MainService::insertObject(void* objPtr)
{
	instanceM.push_back(std::shared_ptr<charlotte::Object>((charlotte::Object*)objPtr));
	auto guidService = globalServiceLocator.get<AssetGUIDService>();
	auto n = guidService->get<charlotte::Object>();
	guidService->increment<charlotte::Object>();
	instanceM.back()->m_guid = n;
}

/*
*Brief ->
*
*	Initialization of services
*/

void charlotte::initialise(sf::RenderWindow& window)
{
	auto service = globalServiceLocator.insertService<charlotte::AssetGUIDService>(new charlotte::AssetGUIDService());
	service.insert<charlotte::Sprite>();
	service.insert<charlotte::RenderTexture>();
	service.insert<charlotte::Object>();
	globalServiceLocator.insertService		(		new charlotte::InputService()		);
	globalServiceLocator.insertService		(		new charlotte::WindowService(window)	);
	globalServiceLocator.insertService		(		new charlotte::GraphicsService()		);
	globalServiceLocator.insertService		(		new charlotte::MainService()			);
	globalServiceLocator.insertService		(		new charlotte::ErrorService()		);
	globalServiceLocator.insertService		(		new charlotte::ContentService()		);
	charlotte::CharlotteServices services = charlotte::CharlotteServices();
	services.init();
}