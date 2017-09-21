#pragma once
#include<SFML\Graphics.hpp>
#include "Animation.h"
#include<map>
#include "ServiceLocator.h"
#include<memory>
#include "EngineComponent.h"
#include "RenderTexture.h"
#include "CharlotteServices.h"

namespace charlotte
{
	class GraphicsService : public Service, EngineComponent
	{
		charlotte::RenderTexture* _applicationRenderTexture = nullptr;
		charlotte::RenderTexture* _defaultRenderTexture = nullptr;
		std::vector< std::shared_ptr<charlotte::RenderTexture> > _textures;
	public:
		GraphicsService();
		void update();
		void draw(const sf::Drawable&, sf::RenderStates states = sf::RenderStates::Default);
		charlotte::RenderTexture& getApplicationRenderTexture();
		void setRenderTextureTarget(charlotte::RenderTexture& textureTarget);
		charlotte::RenderTexture& makeRenderTexture(sf::Vector2u size);
		void destroyRenderTexture(charlotte::RenderTexture& target);
		void resetRenderTextureTarget();
		void clear(sf::Color& color);
	};
}