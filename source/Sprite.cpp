#include "stdafx.h"
#include "Sprite.h"
#include "ServiceLocator.h"
#include"AssetGUIDService.h"

extern charlotte::ServiceLocator globalServiceLocator;

charlotte::SpriteWrapper::SpriteWrapper(sf::Texture& tex, sf::IntRect rect) : Sprite(tex, rect)
{
	auto service = globalServiceLocator.get<AssetGUIDService>();
	if (this->_guid == service->noID)
	{
		this->_guid = service->get<SpriteWrapper>();
		service->increment<SpriteWrapper>();
	}
}
charlotte::SpriteWrapper::SpriteWrapper() : Sprite()
{
	auto service = globalServiceLocator.get<AssetGUIDService>();
	if (this->_guid == service->noID)
	{
		this->_guid = service->get<SpriteWrapper>();
		service->increment<SpriteWrapper>();
	}
}
int32_t charlotte::SpriteWrapper::getID()
{
	return this->_guid;
}
charlotte::Animation& charlotte::SpriteWrapper::makeAnimation(std::string name, int cellW, int cellH, int sepH, int sepV, size_t rangeBegin, size_t rangeEnd)
{
	auto iter = _anim.insert(_anim.end(),
		std::make_pair(
			name,
			charlotte::Animation(*this,
				cellW,
				cellH,
				sepH,
				sepV,
				rangeBegin,
				rangeEnd)
		)
	);
	return iter->second;
}
charlotte::Animation& charlotte::SpriteWrapper::makeAnimation(std::string name, int cellW, int cellH, int sepH, int sepV)
{
	auto iter = _anim.insert(_anim.end(),
		std::make_pair
		(
			name,
			charlotte::Animation(*this,
				cellW,
				cellH,
				sepH,
				sepV
			)
		)
	);
	return iter->second;
}
charlotte::Animation& charlotte::SpriteWrapper::getAnimation(std::string name)
{
	return _anim[name];
}