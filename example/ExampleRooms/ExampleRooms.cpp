#include"Charlotte.h"

namespace gamens {
	using namespace charlotte;

	class HifumiIcon : public Object
	{
	public:
		HifumiIcon()
		{
			update = [this]()
			{
				if (input->keyboard->getKeyState(sf::Keyboard::A) == Keyboard::KeyStates::Pressed)
				{
					content->getRoom("SecondRoom").execute(60);
				}
			};
			render = []() {
				graphics->draw(content->getSprite("HifumiIconSpr"));
			};
		}
	};
	class AobaIcon : public Object
	{
	public:
		AobaIcon()
		{
			update = [this]()
			{
				if (input->keyboard->getKeyState(sf::Keyboard::A) == Keyboard::KeyStates::Pressed)
				{
					content->getRoom("FirstRoom").execute(60);
				}
			};
			render = []() {
				graphics->draw(content->getSprite("AobaIconSpr"));
			};
		}
	};
	class HifumiWallpaper : public Object
	{
	public:
		HifumiWallpaper()
		{
			render = []() {
				graphics->draw(content->getSprite("HifumiWallpaperSpr"));
			};
		}
	};
	class AobaWallpaper : public Object
	{
	public:
		AobaWallpaper()
		{
			render = []() {
				graphics->draw(content->getSprite("AobaWallpaperSpr"));
			};
		}
	};
	class Game : CharlotteServices
	{
	public:
		Game()
		{
			sf::RenderWindow window(sf::VideoMode(800, 800), "Window..");
			m_window = &window;
			initialise(window);
			load();
			init();
		}
	private:
		void init()
		{
			content->getRoom("FirstRoom").execute(60);
			main->update();
		}
		void loadSprites()
		{
			content->makeSprite("HifumiIconSpr", content->makeTextureFromFile("HifumiIconTex", "ng_icon_4.jpg"));
			content->makeSprite("AobaIconSpr", content->makeTextureFromFile("AobaIconTex", "ng_icon_1.jpg"));
			content->makeSprite("HifumiWallpaperSpr", content->makeTextureFromFile("HifumiWallpaperTex", "ng_wallpaper_4.jpg"));
			content->makeSprite("AobaWallpaperSpr", content->makeTextureFromFile("AobaWallpaperTex", "ng_wallpaper_1.jpg"));
		}
		void loadRooms()
		{
			content->makeRoom("FirstRoom", []()
			{
				auto hI = new HifumiIcon();
				hI->priority = 1;
				main->insertObject(hI);
				auto hW = new HifumiWallpaper();
				hW->priority = 0;
				main->insertObject(hW);
			}).changeBackgroundColor(sf::Color(13, 13, 13));
			content->makeRoom("SecondRoom", []()
			{
				auto aI = new AobaIcon();
				aI->priority = 1;
				main->insertObject(aI);
				auto aW = new AobaWallpaper();
				aW->priority = 0;
				main->insertObject(aW);
			}).changeBackgroundColor(sf::Color(237, 237, 237));
		}
		void load()
		{
			content->setDefaultSearchPath("Content/");
			loadSprites();
			loadRooms();
		}

		sf::RenderWindow* m_window = nullptr;
	};
}

int main()
{
	gamens::Game game = gamens::Game();
	return 0;
}
