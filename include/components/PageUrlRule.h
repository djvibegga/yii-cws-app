/*
 * PageUrlRule.h
 *
 *  Created on: Jan 28, 2016
 *      Author: djvibegga
 */

#ifndef PAGEURLRULE_H_
#define PAGEURLRULE_H_

#include <web/CUrlManager.h>

class PageUrlRule: public CUrlRule
{
public:
	PageUrlRule();
	virtual string getClassName() const;
	virtual string createUrl(
		const CUrlManager * const manager,
		TRouteStruct &route, const string & ampersand = "&") const;
	virtual string parseUrl(
		const CUrlManager * const manager,
		CHttpRequest * const request,
		const string & pathInfo, const string & rawPathInfo) const;
};

#endif /* PAGEURLRULE_H_ */
