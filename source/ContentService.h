#pragma once

#include<map>
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<iostream>
#include "Sprite.h"
#include "GameRoom.h"
#include"ServiceLocator.h"
#include"RenderTexture.h"

namespace charlotte {
	typedef std::map<std::string, sf::Sound>					MAPSS;
	typedef std::map<std::string, sf::Texture>					MAPST;
	typedef std::map<std::string, sf::SoundBuffer>				MAPSSB;
	typedef std::map<std::string, charlotte::Sprite>					MAPSSPR;
	typedef std::map<std::string, charlotte::GameRoom>				MAPSR;
	typedef std::map<std::string, std::shared_ptr<sf::Shader>>	MAPSHDR;
	
	class ContentService : public Service
	{
		MAPST		_tResources;
		MAPSSB		_sbResources;
		MAPSS		_sResources;
		MAPSSPR		_sprResources;
		MAPSR		_rResources;
		MAPSHDR		_shdrResources;
		std::string	_searchDir;
	public:
		ContentService();
		explicit ContentService(const std::string& searchDir);
		void setDefaultSearchPath(const std::string& searchDir);
		void loadAssets();
		sf::Sound& getSound(const std::string &e);
		sf::Texture& getTexture(const std::string &e);
		charlotte::Sprite& makeSprite(const std::string& name);
		charlotte::Sprite& makeSprite(const std::string& name, sf::Texture& tex);
		sf::Texture& makeTextureFromFile(const std::string& name, const std::string& filePath);
		sf::Texture& makeTextureFromBuffer(const std::string& name, uint8_t* ptr, const size_t& size);
		sf::SoundBuffer& makeSoundBufferFromFile(const std::string& name, const std::string& filePath);
		sf::SoundBuffer& makeSoundBufferFromMemory(const std::string& name, uint8_t* dataPtr, const size_t& size);
		charlotte::GameRoom& makeRoom(const std::string& name, const std::function<void()>& func);
		charlotte::GameRoom& getRoom(const std::string& name);
		charlotte::Sprite& getSprite(const std::string& name);
		sf::Sound& makeSound(const std::string& name, sf::SoundBuffer& sndBuffer);
		sf::Shader& makeShaderFromFile(const std::string& name, const std::string& vertShaderPath, const std::string& fragShaderPath);
		sf::Shader& makeShaderFromMemory(const std::string& name, const std::string& vertShaderSource, const std::string& fragShaderSource);
		sf::Shader& getShader(const std::string& name);
	};
}