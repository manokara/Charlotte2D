#include"stdafx.h"
#include"engineError.h"

GameSysError::GameSysError(std::string errorText)
{
	_what = errorText;
}
std::string GameSysError::what()
{
	return _what;
}