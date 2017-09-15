#include"stdafx.h"
#include "assetDB.h"

std::string miwa::ResContainer::_searchDir = "";
MAPST miwa::ResContainer::_tResources = MAPST();
MAPSSB miwa::ResContainer::_sbResources = MAPSSB();
MAPSS miwa::ResContainer::_sResources = MAPSS();
MAPSSPR miwa::ResContainer::_sprResources = MAPSSPR();
MAPSR miwa::ResContainer::_rResources = MAPSR();
MAPSHDR miwa::ResContainer::_shdrResources = MAPSHDR();

miwa::ResContainer::ResContainer()
{

}

miwa::ResContainer::ResContainer(const std::string& searchDir)
{
	_searchDir = searchDir;
}

void miwa::ResContainer::setDefaultSearchPath(const std::string& searchDir)
{
	_searchDir = searchDir;
}

void miwa::ResContainer::loadAssets()
{
	auto& map = miwa::externalFiles::getMap();
	for (const auto& i : map)
	{
		makeTextureFromBuffer(i.first, i.second.getData(), i.second.getSize());
	}
}

sf::Sound& miwa::ResContainer::getSound(const std::string &e)
{
	return _sResources[e];
}

sf::Texture& miwa::ResContainer::getTexture(const std::string &e)
{
	return _tResources[e];
}

miwa::Sprite& miwa::ResContainer::makeSprite(const std::string& name)
{
	auto it = _sprResources.insert(_sprResources.end(), std::make_pair(name, miwa::Sprite()));
	return it->second;
}

miwa::Sprite& miwa::ResContainer::makeSprite(const std::string& name, sf::Texture& tex)
{
	auto it = _sprResources.insert(_sprResources.end(), std::make_pair(name, miwa::Sprite()));
	it->second.setTexture(tex);
	return it->second;
}

sf::Texture& miwa::ResContainer::makeTextureFromFile(const std::string& name, const std::string& filePath)
{
	auto it = _tResources.insert(_tResources.end(), std::make_pair(name, sf::Texture()));
	it->second.loadFromFile(filePath);
	return it->second;
}

sf::Texture& miwa::ResContainer::makeTextureFromBuffer(const std::string& name, uint8_t* ptr, const size_t& size)
{

	auto it = _tResources.insert(_tResources.end(), std::make_pair(name, sf::Texture()));
	it->second.loadFromMemory(ptr, size);
	return it->second;
}

sf::SoundBuffer& miwa::ResContainer::makeSoundBufferFromFile(const std::string& name, const std::string& filePath)
{
	auto it = _sbResources.insert(_sbResources.end(), std::make_pair(name, sf::SoundBuffer()));
	it->second.loadFromFile(_searchDir + filePath);
	return it->second;
}

sf::SoundBuffer& miwa::ResContainer::makeSoundBufferFromMemory(const std::string& name, uint8_t* dataPtr, const size_t& size)
{
	auto it = _sbResources.insert(_sbResources.end(), std::make_pair(name, sf::SoundBuffer()));
	it->second.loadFromMemory(dataPtr, size);
	return it->second;
}

miwa::GameRoom& miwa::ResContainer::makeRoom(const std::string& name, const std::function<void()>& func)
{
	auto it = _rResources.insert(_rResources.end(), std::make_pair(name, miwa::GameRoom(name, func)));
	return it->second;
}

miwa::GameRoom& miwa::ResContainer::getRoom(const std::string& name)
{
	return _rResources[name];
}

miwa::Sprite& miwa::ResContainer::getSprite(const std::string& name)
{
	return _sprResources[name];
}

sf::Sound& miwa::ResContainer::makeSound(const std::string& name, sf::SoundBuffer& sndBuffer)
{
	auto it = _sResources.insert(_sResources.end(), std::make_pair(name, sf::Sound()));
	it->second.setBuffer(sndBuffer);
	return it->second;
}

sf::Shader& miwa::ResContainer::makeShaderFromFile(const std::string& name, const std::string& vertShaderPath, const std::string& fragShaderPath)
{
	auto it = _shdrResources.insert(_shdrResources.end(), std::make_pair(name, std::make_shared<sf::Shader>()));
	(it->second)->loadFromFile(_searchDir + vertShaderPath, _searchDir + fragShaderPath);
	return *it->second;
}

sf::Shader& miwa::ResContainer::makeShaderFromMemory(const std::string& name, const std::string& vertShaderSource, const std::string& fragShaderSource)
{
	auto it = _shdrResources.insert(_shdrResources.end(), std::make_pair(name, std::make_shared<sf::Shader>()));
	(it->second)->loadFromMemory(vertShaderSource, fragShaderSource);
	return *it->second;
}

sf::Shader& miwa::ResContainer::getShader(const std::string& name)
{
	return *_shdrResources[name];
}