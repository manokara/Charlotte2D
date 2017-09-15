#pragma once
#include<SFML\Graphics.hpp>
#include<map>
#include<functional>

class SystemComponent
{
public:
	virtual void update()
	{

	}
};

namespace miwa {
	namespace input {
		class Keyboard
		{
		public:
			enum KeyStates
			{
				Released, Release, Pressed, Press
			};
		protected:
			static std::vector<KeyStates> _KeyM;
		public:
			Keyboard();

			static KeyStates& getKeyState(const sf::Keyboard::Key& keyToGet);
		};

		class MKeyboard : public Keyboard, public SystemComponent
		{
		public:
			void update();
		};
	}
}