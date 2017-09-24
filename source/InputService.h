#pragma once

#include "EngineComponent.h"
#include "ServiceLocator.h"
#include<SFML/Graphics.hpp>

/*
*	Input Service
*	Services related to keyboard, mouse, etc.
*/
namespace charlotte {
	class Keyboard;

	class InputService : public Service, EngineComponent
	{
		void _updateKeyboard();
	public:
		static charlotte::Keyboard* keyboard;

		InputService();

		void update();
	};
}