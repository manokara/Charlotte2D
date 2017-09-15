#pragma once
#include<SFML\System.hpp>
#include<vector>
#include<memory>
#include<functional>
#include"preproc.h"
#include"animation.h"
#include<map>

namespace miwa {
	class Object
	{
	public:
		Object();
		Object(Object&);
		~Object();

		sf::Vector2i coord;
		bool activated;
		bool persistent = false;
		int priority = 0;
		bool operator<(const miwa::Object& other)
			const;
		std::function<void()> update;
		std::function<void()> render;
		friend Object& makeObjectCopy(Object& toCopy);
	};

#ifndef _OBJSET_
#define _OBJSET_

	std::vector<std::shared_ptr<miwa::Object>>& getLoopV();

	template<typename T>
	T& makeObject()
	{
		auto& loopV = getLoopV();
		loopV.push_back(std::make_shared<T>());
		return static_cast<T&>(*loopV.back());
	}
#endif

	Object& makeObjectCopy(Object& toCopy);

}