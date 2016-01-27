/*
 * ArticleCategory.h
 *
 *  Created on: Nov 24, 2014
 *      Author: djvibegga
 */

#ifndef ARTICLECATEGORY_H_
#define ARTICLECATEGORY_H_

#include <db/ar/CActiveRecord.h>

class ArticleCategory: public CActiveRecord
{
	DECLARE_AR_CLASS(ArticleCategory)
	DECLATE_AR_ATTRIBUTE(AR_ATTRIBUTE_ULONG, id)
	DECLATE_AR_ATTRIBUTE(AR_ATTRIBUTE_STRING, name)
	DECLATE_AR_ATTRIBUTE(AR_ATTRIBUTE_VSTRING, label)
	DECLATE_AR_ATTRIBUTE(AR_ATTRIBUTE_ULONG, index)
	DECLARE_ATTRIBUTE_POPULATE()
	DECLARE_ATTRIBUTES_GETSET()
	DECLARE_PRIMARY_KEY()

public:
	ArticleCategory(const string & scenario = "", CDbConnection * connection = 0);
	ArticleCategory(const ArticleCategory & other);
	virtual ~ArticleCategory();
};

#endif /* ARTICLECATEGORY_H_ */
