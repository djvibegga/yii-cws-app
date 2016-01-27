/*
 * MainLayout.h
 *
 *  Created on: Nov 22, 2014
 *      Author: djvibegga
 */

#ifndef MAINLAYOUT_H_
#define MAINLAYOUT_H_

#include <web/CLayoutView.h>

class MainLayout: public CLayoutView
{
private:
	string _viewName;

public:
	MainLayout(const CBaseController * owner = 0, const string & viewName = "application.views.layouts.main");
	virtual string getClassName() const;
	virtual void run() throw (CException);
};

#endif /* MAINLAYOUT_H_ */
