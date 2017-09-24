#pragma once
#include<SFML/Graphics.hpp>
#include"Drawables.h"
#include"CharlotteServices.h"

namespace charlotte {
	class GraphicsService;
	
	class RenderTextureWrapper : public sf::RenderTexture
	{
	public:
		RenderTextureWrapper();
		int32_t getID();
	private:
		int32_t _guid = -1;
	};

	typedef RenderTextureWrapper RenderTexture;
}