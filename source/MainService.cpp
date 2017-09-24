#include "stdafx.h"
#include<vector>
#include<memory>
#include<queue>
#include<iostream>
#include "InstanceQueue.h"
#include "keyboard.h"
#include "ServiceLocator.h"
#include "InputService.h"
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
	return *this->m_current_room_pointer;
}

void charlotte::MainService::changeFrameRate(uint32_t FPS)
{
	m_fps = FPS;
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
			windowService->getSfRenderWindow()->pollEvent(this->m_event);
			switch (this->m_event.type)
			{
			case sf::Event::Closed:
				windowService->getSfRenderWindow()->close();
				quit = true;
				break;
			}
			graphicsService->clear(m_current_room_pointer->getBackgroundColor());
			for (auto& it : m_instances)
			{
				m_instance_queue.pushd(it);
			}
			uint32_t sS = 0;
			/*
			*	Update Input
			*/
			inputService->update();

			while (!m_instance_queue.empty())
			{
				m_loop_index = m_instance_queue.size() - 1 - sS;
				auto& cInst = m_instance_queue.top();
				m_loop_index_destruction = false;
				if (m_instance_queue.getVector().size() > 0) {
					/*
					*	Call instance events
					*/
					if (cInst.lock()->update) {
						cInst.lock()->update();
					}
					if (m_instance_queue.getVector().size() > 0) {
						if (cInst.lock()->render) {
							cInst.lock()->render();
						}
					}
					watafoka = 0;
				}
				if (m_instance_queue.size() > 0 && !m_loop_index_destruction)
				{
					m_instance_queue.pop();
				}
			}
			graphicsService->update();
			windowService->getSfRenderWindow()->display();
			sf::sleep(sf::milliseconds(1000.0 / static_cast<float>(mainService->m_current_room_pointer->getFPS())));
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
	auto iter = std::find_if(m_instances.begin(), m_instances.end(), [&objPtr](decltype(*m_instances.begin())& e) {
		return e.get() == objPtr;
	});
	return iter != m_instances.end();
}

void charlotte::MainService::destroyObject(Object* objPtr)
{
	auto iter = std::find_if(m_instances.begin(), m_instances.end(), [objPtr](std::weak_ptr<Object> i)
	{
		return i.lock().get() == objPtr;
	});

	if (iter == m_instances.end())
	{
		CharlotteError error("The object is not in the list of instances");
		globalServiceLocator.get<charlotte::ErrorService>()->setError( error );
	}
	else {
		auto dist = static_cast<decltype(m_loop_index)>(std::distance(m_instances.begin(), iter));
		if (dist < m_loop_index)
		{
			watafoka++;
		}
		m_instances.erase(iter);
		auto it = std::find_if(m_instance_queue.getVector().begin(), m_instance_queue.getVector().end(), [objPtr](std::weak_ptr<Object> i)
		{
			return i.lock().get() == objPtr;
		});
		if (it->lock().get() == m_instance_queue.top().lock().get())
		{
			m_loop_index_destruction = true;
			m_instance_queue.pop();
		}
	}
}

void charlotte::MainService::clearObjects()
{
	m_instances.clear();
	m_instance_queue.getVector().clear();
}

extern charlotte::ServiceLocator globalServiceLocator;

void charlotte::MainService::insertObject(void* objPtr)
{
	m_instances.push_back(std::shared_ptr<charlotte::Object>((charlotte::Object*)objPtr));
	auto guidService = globalServiceLocator.get<AssetGUIDService>();
	auto n = guidService->get<charlotte::Object>();
	guidService->increment<charlotte::Object>();
	m_instances.back()->m_guid = n;
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
