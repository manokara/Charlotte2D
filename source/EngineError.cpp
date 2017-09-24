#include "stdafx.h"
#include "Error.h"

charlotte::CharlotteError::CharlotteError(std::string errorText)
{
	_what = errorText;
}
std::string charlotte::CharlotteError::what()
{
	return _what;
}