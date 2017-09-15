#include"stdafx.h"
#include"keyboard.h"


miwa::input::Keyboard::KeyStates& miwa::input::Keyboard::getKeyState(const sf::Keyboard::Key& keyToGet)
{
	return _KeyM[keyToGet];
}

miwa::input::Keyboard::Keyboard()
{

}

void miwa::input::MKeyboard::update()
{
	for (auto i = 0; i < _KeyM.size(); ++i)
	{
		auto& rK = _KeyM[i];

		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
		{
			switch (rK)
			{
			case Keyboard::KeyStates::Release:
				rK = Keyboard::KeyStates::Pressed;
				break;
			case Keyboard::KeyStates::Released:
				rK = Keyboard::KeyStates::Pressed;
				break;
			case Keyboard::KeyStates::Pressed:
				rK = Keyboard::KeyStates::Press;
				break;
			default:
				break;
			}
		}
		else
		{
			switch (rK)
			{
			case Keyboard::KeyStates::Pressed:
				rK = Keyboard::KeyStates::Released;
				break;
			case Keyboard::KeyStates::Press:
				rK = Keyboard::KeyStates::Released;
				break;
			case Keyboard::KeyStates::Released:
				rK = Keyboard::KeyStates::Release;
				break;
			default:
				break;
			}
		}
	}
}

std::vector<miwa::input::Keyboard::KeyStates> miwa::input::Keyboard::_KeyM = std::vector<KeyStates>(sf::Keyboard::KeyCount, Keyboard::KeyStates::Release);