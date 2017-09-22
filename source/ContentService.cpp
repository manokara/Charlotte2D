#include "stdafx.h"
#include "ContentService.h"

charlotte::ContentService::ContentService()
{
	_searchDir = "";
	_tResources = MAPST();
	_sbResources = MAPSSB();
	_sResources = MAPSS();
	_sprResources = MAPSSPR();
	_rResources = MAPSR();
	_shdrResources = MAPSHDR();
}

charlotte::ContentService::ContentService(const std::string& searchDir)
{
	_searchDir = searchDir;
}

void charlotte::ContentService::setDefaultSearchPath(const std::string& searchDir)
{
	_searchDir = searchDir;
}

sf::Sound& charlotte::ContentService::getSound(const std::string &e)
{
	return _sResources[e];
}

sf::Texture& charlotte::ContentService::getTexture(const std::string &e)
{
	return _tResources[e];
}

charlotte::Sprite& charlotte::ContentService::makeSprite(const std::string& name)
{
	auto it = _sprResources.insert(_sprResources.end(), std::make_pair(name, charlotte::Sprite()));
	return it->second;
}

charlotte::Sprite& charlotte::ContentService::makeSprite(const std::string& name, sf::Texture& tex)
{
	auto it = _sprResources.insert(_sprResources.end(), std::make_pair(name, charlotte::Sprite()));
	it->second.setTexture(tex);
	return it->second;
}

sf::Texture& charlotte::ContentService::makeTextureFromFile(const std::string& name, const std::string& filePath)
{
	auto it = _tResources.insert(_tResources.end(), std::make_pair(name, sf::Texture()));
	it->second.loadFromFile(filePath);
	return it->second;
}

sf::Texture& charlotte::ContentService::makeTextureFromBuffer(const std::string& name, uint8_t* ptr, const size_t& size)
{

	auto it = _tResources.insert(_tResources.end(), std::make_pair(name, sf::Texture()));
	it->second.loadFromMemory(ptr, size);
	return it->second;
}

sf::SoundBuffer& charlotte::ContentService::makeSoundBufferFromFile(const std::string& name, const std::string& filePath)
{
	auto it = _sbResources.insert(_sbResources.end(), std::make_pair(name, sf::SoundBuffer()));
	it->second.loadFromFile(_searchDir + filePath);
	return it->second;
}

sf::SoundBuffer& charlotte::ContentService::makeSoundBufferFromMemory(const std::string& name, uint8_t* dataPtr, const size_t& size)
{
	auto it = _sbResources.insert(_sbResources.end(), std::make_pair(name, sf::SoundBuffer()));
	it->second.loadFromMemory(dataPtr, size);
	return it->second;
}

charlotte::GameRoom& charlotte::ContentService::makeRoom(const std::string& name, const std::function<void()>& func)
{
	auto it = _rResources.insert(_rResources.end(), std::make_pair(name, charlotte::GameRoom(name, func)));
	return it->second;
}

charlotte::GameRoom& charlotte::ContentService::getRoom(const std::string& name)
{
	return _rResources[name];
}

charlotte::Sprite& charlotte::ContentService::getSprite(const std::string& name)
{
	return _sprResources[name];
}

sf::Sound& charlotte::ContentService::makeSound(const std::string& name, sf::SoundBuffer& sndBuffer)
{
	auto it = _sResources.insert(_sResources.end(), std::make_pair(name, sf::Sound()));
	it->second.setBuffer(sndBuffer);
	return it->second;
}

sf::Shader& charlotte::ContentService::makeShaderFromFile(const std::string& name, const std::string& vertShaderPath, const std::string& fragShaderPath)
{
	auto it = _shdrResources.insert(_shdrResources.end(), std::make_pair(name, std::make_shared<sf::Shader>()));
	(it->second)->loadFromFile(_searchDir + vertShaderPath, _searchDir + fragShaderPath);
	return *it->second;
}

sf::Shader& charlotte::ContentService::makeShaderFromMemory(const std::string& name, const std::string& vertShaderSource, const std::string& fragShaderSource)
{
	auto it = _shdrResources.insert(_shdrResources.end(), std::make_pair(name, std::make_shared<sf::Shader>()));
	(it->second)->loadFromMemory(vertShaderSource, fragShaderSource);
	return *it->second;
}

sf::Shader& charlotte::ContentService::getShader(const std::string& name)
{
	return *_shdrResources[name];
}