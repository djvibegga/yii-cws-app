/*
 * Object.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: djvibegga
 */

#include "models/Object.h"


IMPLEMENT_AR_CLASS(Object, "object")

BEGIN_ATTRIBUTE_POPULATE(Object)
	ATTRIBUTE_POPULATE(id, "id", AR_POPULATE_ULONG)
	ATTRIBUTE_POPULATE(type, "type", AR_POPULATE_STRING)
END_ATTRIBUTE_POPULATE()

BEGIN_ATTRIBUTES_SETTER(Object)
	ATTRIBUTES_SETTER(id, "id", AR_ATTRIBUTE_GET_ULONG)
	ATTRIBUTES_SETTER(type, "type", AR_ATTRIBUTE_GET_STRING)
END_ATTRIBUTES_SETTER()

BEGIN_ATTRIBUTES_GETTER(Object)
	ATTRIBUTES_GETTER("id", id)
	ATTRIBUTES_GETTER("type", type)
END_ATTRIBUTES_GETTER()

BEGIN_PRIMARY_KEY(Object)
	PRIMARY_KEY_ADD_PROPERTY("id", id)
END_PRIMARY_KEY()

Object::Object(const string & scenario, CDbConnection * connection)
: CActiveRecord(scenario, connection),
  id(0)
{
}

Object::Object(const Object & other)
: CActiveRecord(other.getScenario(), other.getDbConnection()),
  id(other.id)
{
}

Object::~Object()
{
}
