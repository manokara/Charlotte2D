#pragma once

#include "Service.h"

namespace charlotte {
	class CharlotteError;

	class ErrorService : public Service
	{
		static CharlotteError* _error;
	public:
		ErrorService();
		~ErrorService();
		CharlotteError& getError();
		void setError(CharlotteError& error);
	};
}
