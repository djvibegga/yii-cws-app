/*
 * Application.cpp
 *
 *  Created on: Oct 15, 2013
 *      Author: djvibegga
 */

#include "Application.h"

#include <base/Cws.h>
#include <web/CController.h>
#include <logging/CFileLogRoute.h>
#include <logging/CConsoleLogRoute.h>
#include <base/CEvent.h>
#include <web/renderers/CBaseViewRenderer.h>
#include <web/CUrlManager.h>
#include <web/CAssetManager.h>
#include <web/CClientScript.h>
#include <web/CWebUser.h>
#include <utils/CFile.h>

#include "components/DbConnection.h"
#include "controllers/SiteController.h"
#include "controllers/PageController.h"
#include "components/PageUrlRule.h"

Application::Application(const string &configPath, int argc, char * const argv[])
: CWebApplication(configPath, argc, argv)
{
}

Application::Application(const xml_document & configDocument, int argc, char * const argv[])
: CWebApplication(configDocument, argc, argv)
{
}

Application::~Application()
{
}

CUrlManager * Application::createUrlManager()
{
	CUrlManager * manager = CWebApplication::createUrlManager();
	manager->addRule(new CUrlRule("site/index", "/"));
	manager->addRule(new CUrlRule("site/am", "am"));
	manager->addRule(new CUrlRule("site/db", "db"));
	manager->addRule(new PageUrlRule());
	manager->addRule(new CUrlRule("page/view", "page/<name:\\w+>*"));
	return manager;
}

CLogRouter * Application::createLogRouter()
{
	CLogRouter * log = CWebApplication::createLogRouter();
	CFileLogRoute * fileRoute = new CFileLogRoute("application.log");
	fileRoute->setLevels("info,error,warning,trace,profile");
	fileRoute->init();
	log->addRoute(fileRoute);
#ifdef CWS_DEBUG
//	CConsoleLogRoute * consoleRoute = new CConsoleLogRoute();
//	consoleRoute->setLevels("info,error,warning,trace,profile");
//	consoleRoute->init();
//	log->addRoute(consoleRoute);
//	getLogger().autoFlush = 1;
//	getLogger().autoDump = true;
#endif
    getLogger().attachEventHandler("onLog", this, EVENT_HANDLER(&Application::logStdout));
	return log;
}

void Application::registerComponents()
{
	CDbConnection * connection = new DbConnection(this);
	connection->setId("db");
	connection->init();
	if (!connection->open()) {
		Cws::log("Can't open database connection.", CLogger::LEVEL_ERROR);
	}
	setComponent(connection);

	CAssetManager * am = new CAssetManager(this);
	am->init();

	CClientScript * cs = new CClientScript(this);
	cs->init();

	SiteController * siteController = new SiteController(this);
	siteController->init();

	PageController * pageController = new PageController(this);
	pageController->init();
}


void Application::logStdout(CEvent & event)
{
	SLogElement * logItem = (SLogElement*)(event.params["logItem"]);
	if (logItem->level == CLogger::LEVEL_ERROR) {
		cout << "[" << logItem->time << "] [" << logItem->category << "] " << logItem->message << endl;
	}
}
