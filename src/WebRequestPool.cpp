/*
 * TestWebRequestPool.cpp
 *
 *  Created on: Feb 18, 2014
 *      Author: djvibegga
 */

#include "WebRequestPool.h"
#include "Application.h"

WebRequestPool::WebRequestPool(const string &configPath, int argc, char * const argv[])
: CWebRequestPool(configPath, argc, argv)
{
}

CWebApplication * WebRequestPool::createAppInstance() const
{
	return new Application(getConfigDocument(), argc, argv);
}
