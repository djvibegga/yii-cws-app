/*
 * Page.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: djvibegga
 */

#include "models/Page.h"
#include <db/CDbCriteria.h>

IMPLEMENT_AR_CLASS(Page, "page")

BEGIN_ATTRIBUTE_POPULATE(Page)
	ATTRIBUTE_POPULATE(id, "id", AR_POPULATE_ULONG)
	ATTRIBUTE_POPULATE(name, "name", AR_POPULATE_STRING)
	ATTRIBUTE_POPULATE(url, "url", AR_POPULATE_STRING)
	ATTRIBUTE_POPULATE(content, "content", AR_POPULATE_VSTRING)
END_ATTRIBUTE_POPULATE()

BEGIN_ATTRIBUTES_SETTER(Page)
	ATTRIBUTES_SETTER(id, "id", AR_ATTRIBUTE_GET_ULONG)
	ATTRIBUTES_SETTER(name, "name", AR_ATTRIBUTE_GET_STRING)
	ATTRIBUTES_SETTER(url, "url", AR_ATTRIBUTE_GET_STRING)
	ATTRIBUTES_SETTER(content, "content", AR_ATTRIBUTE_GET_VSTRING)
END_ATTRIBUTES_SETTER()

BEGIN_ATTRIBUTES_GETTER(Page)
	ATTRIBUTES_GETTER("id", id)
	ATTRIBUTES_GETTER("name", name)
	ATTRIBUTES_GETTER("url", url)
	ATTRIBUTES_GETTER("content", content)
END_ATTRIBUTES_GETTER()

BEGIN_PRIMARY_KEY(Page)
	PRIMARY_KEY_ADD_PROPERTY("id", id)
END_PRIMARY_KEY()

Page::Page(const string & scenario, CDbConnection * connection)
: CActiveRecord(scenario, connection),
  id(0)
{
}

Page::Page(const Page & other)
: CActiveRecord(other.getScenario(), other.getDbConnection()),
  id(other.id)
{
}

Page::~Page()
{
}

TActiveRecordPtr Page::findByName(const string & name)
{
	CDbCriteria criteria;
	string pageName = name;
	criteria.compare("t.name", pageName);
	return find(criteria);
}
