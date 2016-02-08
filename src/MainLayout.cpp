/*
 * MainLayout.cpp
 *
 *  Created on: Nov 22, 2014
 *      Author: djvibegga
 */

#include "MainLayout.h"
#include <web/CAssetManager.h>
#include <web/CUrlManager.h>
#include <web/CClientScript.h>
#include <base/Cws.h>
#include "models/Page.h"

MainLayout::MainLayout(const CBaseController * owner, const string & viewName)
: CLayoutView(owner),
  _viewName(viewName)
{
}

string MainLayout::getClassName() const
{
	return "MainLayout";
}

void MainLayout::run() throw (CException)
{
	CDT viewData;
	viewData["content"] = content;
	CApplication * app = Cws::app();
	viewData["assetsUrl"] = dynamic_cast<CAssetManager*>(app->getComponent("assetManager"))
		->getPublishedUrl(Cws::getPathOfAlias("application.assets"));

	CUrlManager * urlManager = dynamic_cast<CUrlManager*>(app->getComponent("urlManager"));
	viewData["badRequestUrl"] = urlManager->createUrl("nonexisturl");
	viewData["loginUrl"] = urlManager->createUrl("site/login");
	viewData["amUrl"] = urlManager->createUrl("site/am");
	viewData["sessionsUrl"] = urlManager->createUrl("site/session");
	viewData["cookiesUrl"] = urlManager->createUrl("site/cookies");
	viewData["securityUrl"] = urlManager->createUrl("site/security");
	viewData["dbUrl"] = urlManager->createUrl("site/db");
	viewData["translateUrl"] = urlManager->createUrl("site/translate");

	TRouteStruct contactsRoute;
	contactsRoute.path = "page/view";
	TActiveRecordPtr contactsPtr = Page::model()->findByName("Contacts Us");
	contactsRoute.params["id"] = CStringUtils::fromULong(dynamic_cast<Page*>(contactsPtr.get())->id);
	viewData["contactsUrl"] = urlManager->createUrl(contactsRoute);

	dynamic_cast<CClientScript*>(Cws::app()->getComponent("clientScript"))
		->registerPackage("main");

	viewData["lang"] = app->getLanguage();

	string currentRoute = dynamic_cast<CController*>(app->getComponent("controller"))->getRoute();
	CHttpRequest * request = dynamic_cast<CHttpRequest*>(app->getComponent("request"));
	vector<string> languages = app->getLanguages();

	viewData["langs"] = CDT();
	for (vector<string>::const_iterator iter = languages.begin(); iter != languages.end(); ++iter) {
		TRouteStruct route(currentRoute);
		route.params = request->getParams();
		route.params["lang"] = *iter;
		CDT lang;
		lang["label"] = *iter;
		string url = urlManager->createUrl(route);
		lang["url"] = url;
		viewData["langs"].PushBack(lang);
	}

	viewData["loginButton"] = "Login";

	render(_viewName, viewData);
}
