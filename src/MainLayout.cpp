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

	TRouteStruct portfolioRoute("work/index");
	CUrlManager * urlManager = dynamic_cast<CUrlManager*>(app->getComponent("urlManager"));
	viewData["portfolioUrl"] = urlManager->createUrl(portfolioRoute);

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

	render(_viewName, viewData);
}
