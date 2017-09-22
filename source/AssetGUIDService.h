#pragma once
#include<map>
#include<string>
#include "ServiceLocator.h"
#include<iostream>
namespace charlotte {
	class AssetGUIDService : public Service
	{
		static std::map<std::string, int32_t> _guids;
	public:
		int32_t noID = -1;
		template<typename T>
		int32_t get()
		{
			auto typeName = typeid(T).name();
			auto iter = this->_guids.find(typeName);

			if (iter != this->_guids.end())
			{
				return iter->second;
			}

			return noID;
		}
		template<typename T>
		void increment()
		{
			auto typeName = typeid(T).name();
			auto iter = this->_guids.find(typeName);

			if (iter != this->_guids.end())
			{
				++iter->second;
			}
		}
		template<typename T>
		void insert()
		{
			this->_guids.insert(this->_guids.begin(), std::make_pair( typeid(T).name(), 0 ));
		}
	};
}