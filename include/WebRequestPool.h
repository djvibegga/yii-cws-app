/*
 * TestWebAppPool.h
 *
 *  Created on: Feb 18, 2014
 *      Author: djvibegga
 */

#ifndef WEBAPPPOOL_H_
#define WEBAPPPOOL_H_

#include "web/CWebRequestPool.h"

class WebRequestPool: public CWebRequestPool
{
public:
	WebRequestPool(const string &configPath, int argc, char * const argv[]);

protected:
	virtual CWebApplication * createAppInstance() const;
};

#endif /* WEBAPPPOOL_H_ */
