#pragma once
#include<SFML/Graphics.hpp>
namespace charlotte {
	class ContentService;
	class InputService;
	class WindowService;
	class MainService;
	class GraphicsService;
	class ErrorService;

	class CharlotteServices
	{
		void init();
	public:
		friend void initialise(sf::RenderWindow& window);
		static ContentService	*content;
		static InputService		*input;
		static WindowService	*window;
		static MainService		*main;
		static GraphicsService	*graphics;
		static ErrorService		*error;
		CharlotteServices();
		~CharlotteServices();
	};
}