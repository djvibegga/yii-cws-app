/*
 * Tag.h
 *
 *  Created on: Feb 5, 2014
 *      Author: djvibegga
 */

#ifndef TAG_H_
#define TAG_H_

#include <db/ar/CActiveRecord.h>

class Tag: public CActiveRecord
{
	DECLARE_AR_CLASS(Tag)
	DECLATE_AR_ATTRIBUTE(AR_ATTRIBUTE_ULONG, id)
	DECLATE_AR_ATTRIBUTE(AR_ATTRIBUTE_STRING, name)
	DECLATE_AR_ATTRIBUTE(AR_ATTRIBUTE_VSTRING, label)
	DECLATE_AR_ATTRIBUTE(AR_ATTRIBUTE_ULONG, objectId)
	DECLARE_ATTRIBUTE_POPULATE()
	DECLARE_ATTRIBUTES_GETSET()
	DECLARE_PRIMARY_KEY()

public:

	Tag(const string & scenario = "", CDbConnection * connection = 0);
	Tag(const Tag & other);
	virtual ~Tag();
	TActiveRecordPtr findByName(string & name);
};

#endif /* TAG_H_ */
