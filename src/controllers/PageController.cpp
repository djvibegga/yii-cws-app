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
	setLayout(TViewPtr(new MainLayout(this)));
}

PageController::~PageController()
{
}

void PageController::init()
{
    CController::init();
	registerAction("view", ACTION(&PageController::actionView));
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
