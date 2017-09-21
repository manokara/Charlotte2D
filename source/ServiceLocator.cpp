#include "stdafx.h"
#include "ServiceLocator.h"
#include"ErrorService.h"
#include"Error.h"

extern charlotte::ServiceLocator globalServiceLocator;

charlotte::ServiceLocator& charlotte::getServiceLocator()
{
	return globalServiceLocator;
}