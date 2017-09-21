#include "stdafx.h"
#include "ErrorService.h"
#include "Error.h"
#include<iostream>
charlotte::CharlotteError* charlotte::ErrorService::_error = nullptr;

charlotte::ErrorService::ErrorService()
{
	if (!this->_error)
	{
		this->_error = new charlotte::CharlotteError("");
	}
}

charlotte::ErrorService::~ErrorService()
{

}

charlotte::CharlotteError& charlotte::ErrorService::getError()
{
	if (!this->_error)
	{
		std::cerr << "Error service not initialized" << std::endl;
	}
	return *this->_error;
}

void charlotte::ErrorService::setError(charlotte::CharlotteError& error)
{
	std::cerr << error.what() << std::endl;
	*(this->_error) = error;
}

void charlotte::CharlotteError::operator=(CharlotteError& ref)
{
	this->_what = ref.what();
}