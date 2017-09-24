#include "stdafx.h"
#include "InputService.h"
#include "keyboard.h"

charlotte::Keyboard* charlotte::InputService::keyboard = nullptr;

charlotte::InputService::InputService()
{
	if (!keyboard)
	{
		keyboard = new charlotte::Keyboard();
	}
}

void charlotte::InputService::_updateKeyboard()
{
	for (auto i = 0; i < keyboard->_KeyM.size(); ++i)
	{
		auto& rK = keyboard->_KeyM[i];
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
		{
			switch (rK)
			{
			case charlotte::Keyboard::KeyStates::Release:
				rK = charlotte::Keyboard::KeyStates::Pressed;
				break;
			case charlotte::Keyboard::KeyStates::Released:
				rK = charlotte::Keyboard::KeyStates::Pressed;
				break;
			case charlotte::Keyboard::KeyStates::Pressed:
				rK = charlotte::Keyboard::KeyStates::Press;
				break;
			default:
				break;
			}
		}
		else
		{
			switch (rK)
			{
			case charlotte::Keyboard::KeyStates::Pressed:
				rK = charlotte::Keyboard::KeyStates::Released;
				break;
			case charlotte::Keyboard::KeyStates::Press:
				rK = charlotte::Keyboard::KeyStates::Released;
				break;
			case charlotte::Keyboard::KeyStates::Released:
				rK = charlotte::Keyboard::KeyStates::Release;
				break;
			default:
				break;
			}
		}
	}
}

void charlotte::InputService::update()
{
	_updateKeyboard();
}
