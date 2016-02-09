/*
 * PageController.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: djvibegga
 */

#include "controllers/PageController.h"
#include <boost/assign.hpp>
#include <base/Cws.h>
#include <base/CSecurityManager.h>
#include <db/CDbDataReader.h>
#include <db/CDbCriteria.h>
#include <db/schema/CDbCommandBuilder.h>
#include <web/CAssetManager.h>
#include <web/CClientScript.h>
#include <web/CUrlManager.h>
#include <web/CWebUser.h>
#include <utils/CMap.h>
#include <boost/assign/list_of.hpp>

#include "MainLayout.h"
#include "models/Page.h"

PageController::PageController(CModule * parent)
: CController("page", parent)
{
	setDefaultLayout(TViewPtr(new MainLayout(this)));
}

PageController::~PageController()
{
}

void PageController::init()
{
    CController::init();
	registerAction("view", ACTION(&PageController::actionView));
	registerAction("index", ACTION(&PageController::actionIndex));
	registerAction("contacts", ACTION(&PageController::actionContacts));
}

void PageController::actionIndex(CHttpRequest * const request, CHttpResponse * response) throw (CException)
{
	CDbCriteria criteria;
	CDT viewData, page;
	CApplication * app = Cws::app();
	CUrlManager * urlManager = dynamic_cast<CUrlManager*>(app->getComponent("urlManager"));
	TActiveRecordList pages = Page::model()->findAll(criteria);

    viewData["pages"] = CDT();
    for (TActiveRecordList::iterator iter = pages.begin(); iter != pages.end(); ++iter) {
    	Page * item = dynamic_cast<Page*>(iter->get());
    	page["id"] = item->id;
    	page["name"] = item->name;
    	page["url"] = urlManager->createUrl(item->url);
    	viewData["pages"].PushBack(page);
    }

	viewData["assetsUrl"] = dynamic_cast<CAssetManager*>(app->getComponent("assetManager"))
		->getPublishedUrl(Cws::getPathOfAlias("application.assets"));

	render("index", viewData);
}

void PageController::actionView(CHttpRequest * const request, CHttpResponse * response) throw (CException)
{
	string pageId = request->getParam("id");
	if (pageId.empty()) {
		throw CHttpException(400, "Bad request");
	}

	CTablePrimaryKey pk("id", pageId);
	TActiveRecordPtr ptr = Page::model()->findByPk(pk);
	Page * pagePtr = dynamic_cast<Page*>(ptr.get());
	if (pagePtr == 0) {
		throw CHttpException(404, "Page not found");
	}

	CDT viewData;
	viewData["page.name"] = pagePtr->name;
	viewData["page.content"] = _to_utf8(pagePtr->content);

	render("view", viewData);
}

void PageController::actionContacts(CHttpRequest * const request, CHttpResponse * response) throw (CException)
{
	CDT viewData;
	setLayout(TViewPtr(new MainLayout(this, "application.views.layouts.main_simple")));
	viewData["page.name"] = _to_utf8(_t("Contacts Us"));
	viewData["page.content"] = "It is the contacts page of the company.";
	render("view", viewData);
}
