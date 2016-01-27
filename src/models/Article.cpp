/*
 * Article.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: djvibegga
 */

#include "models/Article.h"


IMPLEMENT_AR_CLASS(Article, "article")

BEGIN_ATTRIBUTE_POPULATE(Article)
	ATTRIBUTE_POPULATE(id, "id", AR_POPULATE_ULONG)
	ATTRIBUTE_POPULATE(name, "name", AR_POPULATE_STRING)
END_ATTRIBUTE_POPULATE()

BEGIN_ATTRIBUTES_SETTER(Article)
	ATTRIBUTES_SETTER(id, "id", AR_ATTRIBUTE_GET_ULONG)
	ATTRIBUTES_SETTER(name, "name", AR_ATTRIBUTE_GET_STRING)
END_ATTRIBUTES_SETTER()

BEGIN_ATTRIBUTES_GETTER(Article)
	ATTRIBUTES_GETTER("id", id)
	ATTRIBUTES_GETTER("name", name)
END_ATTRIBUTES_GETTER()

BEGIN_PRIMARY_KEY(Article)
	PRIMARY_KEY_ADD_PROPERTY("id", id)
END_PRIMARY_KEY()

Article::Article(const string & scenario, CDbConnection * connection)
: CActiveRecord(scenario, connection),
  id(0)
{
}

Article::Article(const Article & other)
: CActiveRecord(other.getScenario(), other.getDbConnection()),
  id(other.id)
{
}

Article::~Article()
{
}
