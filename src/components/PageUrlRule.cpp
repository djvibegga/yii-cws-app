/*
 * PageUrlRule.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: djvibegga
 */

#include "components/PageUrlRule.h"
#include "models/Page.h"
#include <base/CStringUtils.h>

PageUrlRule::PageUrlRule()
: CUrlRule("page/view", "*")
{
}

string PageUrlRule::getClassName() const
{
	return "PageUrlRule";
}

string PageUrlRule::createUrl(
	const CUrlManager * const manager,
	TRouteStruct &route, const string & ampersand) const
{
	TRequestParams::const_iterator found = route.params.find("id");
	if (found == route.params.end()) {
		return "";
	}

	CTablePrimaryKey pk("id", found->second);
	TActiveRecordPtr ptr = Page::model()->findByPk(pk);
	if (ptr.get() == 0) {
		return (dynamic_cast<Page*>(ptr.get()))->url;
	}

	return "";
}

string PageUrlRule::parseUrl(
	const CUrlManager * const manager,
	CHttpRequest * const request,
	const string & pathInfo, const string & rawPathInfo) const
{
	CDbCriteria criteria;
	string url = pathInfo;
	criteria.compare("url", url);
	TActiveRecordPtr ptr = Page::model()->find(criteria);
	if (ptr.get() == 0) {
		return "";
	}

	request->setParam("id", CStringUtils::fromULong(dynamic_cast<Page*>(ptr.get())->id));
	return "page/view";
}
