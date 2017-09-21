#pragma once

#include<SFML\System.hpp>
#include<vector>
#include<memory>
#include<functional>
#include "animation.h"
#include<map>

namespace charlotte {
	class Object
	{
	public:
		Object();
		Object(Object&);
		virtual ~Object() = 0;
		sf::Vector2i coord;
		bool activated;
		bool persistent = false;
		int priority = 0;
		bool operator<(const Object& other)
			const;
		std::function<void()> update;
		std::function<void()> render;
		int32_t getID();
	private:
		friend class MainService;
		int32_t m_guid;
	};
}