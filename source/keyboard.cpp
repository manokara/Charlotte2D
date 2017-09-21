#include "stdafx.h"
#include "keyboard.h"
#include<vector>
#include<map>


charlotte::Keyboard::KeyStates& charlotte::Keyboard::getKeyState(const sf::Keyboard::Key& keyToGet)
{
	return _KeyM[keyToGet];
}

charlotte::Keyboard::Keyboard()
{

}

std::vector<charlotte::Keyboard::KeyStates> charlotte::Keyboard::_KeyM = std::vector<KeyStates>(sf::Keyboard::KeyCount, Keyboard::KeyStates::Release);
