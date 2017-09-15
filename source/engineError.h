#pragma once
#include<string>

class GameSysError
{
	std::string _what = "";
public:
	GameSysError(std::string errorText);
	std::string what();
};