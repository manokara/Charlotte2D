#include "stdafx.h"
#include "RenderTexture.h"
#include "ServiceLocator.h"
#include "AssetGUIDService.h"
#include "GraphicsService.h"

extern charlotte::ServiceLocator globalServiceLocator;

charlotte::RenderTextureWrapper::RenderTextureWrapper() : RenderTexture()
{
	auto service = globalServiceLocator.get<AssetGUIDService>();
	if (this->_guid == service->noID)
	{
		this->_guid = service->get<RenderTextureWrapper>();
		service->increment<RenderTextureWrapper>();
	}
}

int32_t charlotte::RenderTextureWrapper::getID()
{
	return this->_guid;
}
