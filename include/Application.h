/*
 * Application.h
 *
 *  Created on: Oct 15, 2013
 *      Author: djvibegga
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <web/CWebApplication.h>
#include <logging/CLogRouter.h>

class Application: public CWebApplication
{
public:
	Application(const string &configPath, int argc, char * const argv[]);
	Application(const xml_document & configDocument, int argc, char * const argv[]);
	virtual ~Application();
	void logStdout(CEvent & event);

protected:
	void registerComponents();
	virtual CUrlManager * createUrlManager();
	virtual CLogRouter * createLogRouter();
};

#endif /* APPLICATION_H_ */
