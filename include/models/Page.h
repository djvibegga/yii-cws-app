/*
 * Page.h
 *
 *  Created on: Feb 5, 2014
 *      Author: djvibegga
 */

#ifndef PAGE_H_
#define PAGE_H_

#include <db/ar/CActiveRecord.h>

class Page: public CActiveRecord
{
	DECLARE_AR_CLASS(Page)
	DECLATE_AR_ATTRIBUTE(AR_ATTRIBUTE_ULONG, id)
	DECLATE_AR_ATTRIBUTE(AR_ATTRIBUTE_STRING, name)
	DECLATE_AR_ATTRIBUTE(AR_ATTRIBUTE_STRING, url)
	DECLATE_AR_ATTRIBUTE(AR_ATTRIBUTE_VSTRING, content)
	DECLARE_ATTRIBUTE_POPULATE()
	DECLARE_ATTRIBUTES_GETSET()
	DECLARE_PRIMARY_KEY()

public:

	Page(const string & scenario = "", CDbConnection * connection = 0);
	Page(const Page & other);
	virtual ~Page();
	TActiveRecordPtr findByName(string & name);
};

#endif /* PAGE_H_ */
