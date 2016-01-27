/*
 * Object.h
 *
 *  Created on: Feb 5, 2014
 *      Author: djvibegga
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <db/ar/CActiveRecord.h>

class Object: public CActiveRecord
{
	DECLARE_AR_CLASS(Object)
	DECLATE_AR_ATTRIBUTE(AR_ATTRIBUTE_ULONG, id)
	DECLATE_AR_ATTRIBUTE(AR_ATTRIBUTE_STRING, type)
	DECLARE_ATTRIBUTE_POPULATE()
	DECLARE_ATTRIBUTES_GETSET()
	DECLARE_PRIMARY_KEY()

public:

	Object(const string & scenario = "", CDbConnection * connection = 0);
	Object(const Object & other);
	virtual ~Object();
};

#endif /* OBJECT_H_ */
