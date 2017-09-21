#include "stdafx.h"
#include "CharlotteServices.h"
#include "ServiceLocator.h"
#include "ContentService.h"
#include "WindowService.h"
#include "inputService.h"
#include "MainService.h"
#include "GraphicsService.h"
#include "ErrorService.h"

extern charlotte::ServiceLocator globalServiceLocator;

charlotte::ContentService*		charlotte::CharlotteServices::content		= nullptr;
charlotte::InputService*			charlotte::CharlotteServices::input		= nullptr;
charlotte::WindowService*		charlotte::CharlotteServices::window		= nullptr;
charlotte::MainService*			charlotte::CharlotteServices::main		= nullptr;
charlotte::GraphicsService*		charlotte::CharlotteServices::graphics	= nullptr;
charlotte::ErrorService*			charlotte::CharlotteServices::error		= nullptr;

charlotte::CharlotteServices::CharlotteServices()
{

}

void charlotte::CharlotteServices::init()
{
	if (!content)
	{
		this->content = globalServiceLocator.get<ContentService>();
	}
	if (!input)
	{
		this->input = globalServiceLocator.get<InputService>();
	}
	if (!window)
	{
		this->window = globalServiceLocator.get<WindowService>();
	}
	if (!main)
	{
		this->main = globalServiceLocator.get<MainService>();
	}
	if (!graphics)
	{
		this->graphics = globalServiceLocator.get<GraphicsService>();
	}
	if (!error)
	{
		this->error = globalServiceLocator.get<ErrorService>();
	}
}

charlotte::CharlotteServices::~CharlotteServices()
{

}