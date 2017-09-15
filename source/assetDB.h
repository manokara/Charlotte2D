#pragma once

#include<map>
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include"miwa.h"
#include<iostream>

namespace miwa {
	#define MAPSS   std::map<std::string, sf::Sound>
#define MAPST   std::map<std::string, sf::Texture>
#define MAPSSB  std::map<std::string, sf::SoundBuffer>
#define MAPSSPR std::map<std::string, miwa::Sprite>
#define MAPSR   std::map<std::string, miwa::GameRoom>
#define MAPSHDR std::map<std::string, std::shared_ptr<sf::Shader>>
	class ResContainer
	{
		static MAPST		_tResources;
		static MAPSSB		_sbResources;
		static MAPSS		_sResources;
		static MAPSSPR		_sprResources;
		static MAPSR		_rResources;
		static MAPSHDR		_shdrResources;
		static std::string	_searchDir;
	public:
		ResContainer();
		explicit ResContainer(const std::string& searchDir);
		static void setDefaultSearchPath(const std::string& searchDir);
		static void loadAssets();
		static sf::Sound& getSound(const std::string &e);
		static sf::Texture& getTexture(const std::string &e);
		static miwa::Sprite& makeSprite(const std::string& name);
		static miwa::Sprite& makeSprite(const std::string& name, sf::Texture& tex);
		static sf::Texture& makeTextureFromFile(const std::string& name, const std::string& filePath);
		static sf::Texture& makeTextureFromBuffer(const std::string& name, uint8_t* ptr, const size_t& size);
		static sf::SoundBuffer& makeSoundBufferFromFile(const std::string& name, const std::string& filePath);
		static sf::SoundBuffer& makeSoundBufferFromMemory(const std::string& name, uint8_t* dataPtr, const size_t& size);
		static miwa::GameRoom& makeRoom(const std::string& name, const std::function<void()>& func);
		static miwa::GameRoom& getRoom(const std::string& name);
		static miwa::Sprite& getSprite(const std::string& name);
		static sf::Sound& makeSound(const std::string& name, sf::SoundBuffer& sndBuffer);
		static sf::Shader& makeShaderFromFile(const std::string& name, const std::string& vertShaderPath, const std::string& fragShaderPath);
		static sf::Shader& makeShaderFromMemory(const std::string& name, const std::string& vertShaderSource, const std::string& fragShaderSource);
		static sf::Shader& getShader(const std::string& name);
	};
}