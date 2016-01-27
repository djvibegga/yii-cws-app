/*
 * ArticleCategory.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: djvibegga
 */

#include "models/ArticleCategory.h"

IMPLEMENT_AR_CLASS(ArticleCategory, "article_category")

BEGIN_ATTRIBUTE_POPULATE(ArticleCategory)
	ATTRIBUTE_POPULATE(id, "id", AR_POPULATE_ULONG)
	ATTRIBUTE_POPULATE(name, "name", AR_POPULATE_STRING)
	ATTRIBUTE_POPULATE(label, "label", AR_POPULATE_VSTRING)
	ATTRIBUTE_POPULATE(index, "index", AR_POPULATE_ULONG)
END_ATTRIBUTE_POPULATE()

BEGIN_ATTRIBUTES_SETTER(ArticleCategory)
	ATTRIBUTES_SETTER(id, "id", AR_ATTRIBUTE_GET_ULONG)
	ATTRIBUTES_SETTER(name, "name", AR_ATTRIBUTE_GET_STRING)
	ATTRIBUTES_SETTER(label, "label", AR_ATTRIBUTE_GET_VSTRING)
	ATTRIBUTES_SETTER(index, "index", AR_ATTRIBUTE_GET_ULONG)
END_ATTRIBUTES_SETTER()

BEGIN_ATTRIBUTES_GETTER(ArticleCategory)
	ATTRIBUTES_GETTER("id", id)
	ATTRIBUTES_GETTER("name", name)
	ATTRIBUTES_GETTER("label", label)
	ATTRIBUTES_GETTER("index", index)
END_ATTRIBUTES_GETTER()

BEGIN_PRIMARY_KEY(ArticleCategory)
	PRIMARY_KEY_ADD_PROPERTY("id", id)
END_PRIMARY_KEY()

ArticleCategory::ArticleCategory(const string & scenario, CDbConnection * connection)
: CActiveRecord(scenario, connection),
  id(0),
  name(""),
  label(_("")),
  index(0)
{
}

ArticleCategory::ArticleCategory(const ArticleCategory & other)
: CActiveRecord(other.getScenario(), other.getDbConnection()),
  id(other.id),
  name(other.name),
  label(other.label),
  index(other.index)
{
}

ArticleCategory::~ArticleCategory()
{
}
