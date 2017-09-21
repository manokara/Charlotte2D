#pragma once
#include<string>
namespace charlotte {
	class CharlotteError
	{
		std::string _what = "";
	public:
		CharlotteError(std::string errorText);
		std::string what();
		void operator=(CharlotteError&);
	};
}