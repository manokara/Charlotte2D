#pragma once

#include<vector>
#include<string>
#include"ErrorService.h"
#include"Error.h"
#include"Service.h"

namespace charlotte {
	class ServiceLocator {
		std::vector<Service*> services;
	public:
		template<typename T>
		T& insertService(T* service)
		{
			auto it = (*services.insert(services.end(), (T*)service));
			it->typeName = typeid(T).name();
			return (*service);
		}
		template<typename T>
		T* get()
		{
			std::string typeName = typeid(T).name();
			for (auto* i : services)
			{
				if (i->typeName == typeName)
				{
					return (T*)i;
				}
			}
			auto errorService = this->get<ErrorService>();
			if (errorService)
			{
				errorService->setError(CharlotteError("No service " + typeName + " found"));
			}
			return nullptr;
		}
	};
	ServiceLocator& getServiceLocator();
}