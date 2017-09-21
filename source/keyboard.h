#pragma once
#include<SFML\Graphics.hpp>
#include<map>
#include<functional>
#include "ServiceLocator.h"
#include "EngineComponent.h"


namespace charlotte {
	class InputService;

	/*
	*	Keyboard Module, a class to Keyboard Management
	*/

	class Keyboard
	{
	public:
		enum KeyStates
		{
			Released, Release, Pressed, Press
		};

		Keyboard();

		KeyStates& getKeyState(const sf::Keyboard::Key& keyToGet);
	private:
		static std::vector<KeyStates> _KeyM;

		friend class InputService;
	};
}