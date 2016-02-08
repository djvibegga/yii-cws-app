/*
 * PageController.h
 *
 *  Created on: Feb 1, 2016
 *      Author: djvibegga
 */

#ifndef PAGECONTROLLER_H_
#define PAGECONTROLLER_H_

#include <web/CController.h>

class PageController: public CController
{
public:
	PageController(CModule * parent);
	virtual ~PageController();
	void init();
	void actionView(CHttpRequest * const request, CHttpResponse * response) throw (CException);
};

#endif /* PAGECONTROLLER_H_ */
