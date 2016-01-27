/*
 * Tag.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: djvibegga
 */

#include "models/Tag.h"

IMPLEMENT_AR_CLASS(Tag, "tag")

BEGIN_ATTRIBUTE_POPULATE(Tag)
	ATTRIBUTE_POPULATE(id, "id", AR_POPULATE_ULONG)
	ATTRIBUTE_POPULATE(name, "name", AR_POPULATE_STRING)
	ATTRIBUTE_POPULATE(label, "label", AR_POPULATE_VSTRING)
	ATTRIBUTE_POPULATE(objectId, "object_id", AR_POPULATE_ULONG)
END_ATTRIBUTE_POPULATE()

BEGIN_ATTRIBUTES_SETTER(Tag)
	ATTRIBUTES_SETTER(id, "id", AR_ATTRIBUTE_GET_ULONG)
	ATTRIBUTES_SETTER(name, "name", AR_ATTRIBUTE_GET_STRING)
	ATTRIBUTES_SETTER(label, "label", AR_ATTRIBUTE_GET_VSTRING)
	ATTRIBUTES_SETTER(objectId, "object_id", AR_ATTRIBUTE_GET_ULONG)
END_ATTRIBUTES_SETTER()

BEGIN_ATTRIBUTES_GETTER(Tag)
	ATTRIBUTES_GETTER("id", id)
	ATTRIBUTES_GETTER("name", name)
	ATTRIBUTES_GETTER("label", label)
	ATTRIBUTES_GETTER("object_id", objectId)
END_ATTRIBUTES_GETTER()

BEGIN_PRIMARY_KEY(Tag)
	PRIMARY_KEY_ADD_PROPERTY("id", id)
END_PRIMARY_KEY()

Tag::Tag(const string & scenario, CDbConnection * connection)
: CActiveRecord(scenario, connection),
  id(0),
  name(""),
  label(_("")),
  objectId(0)
{
}

Tag::Tag(const Tag & other)
: CActiveRecord(other.getScenario(), other.getDbConnection()),
  id(other.id),
  name(other.name),
  label(other.label),
  objectId(0)
{
}

Tag::~Tag()
{
}

TActiveRecordPtr Tag::findByName(string & name)
{
	CDbCriteria criteria;
	criteria.compare("t.name", name);
	return find(criteria);
}
