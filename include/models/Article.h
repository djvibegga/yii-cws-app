/*
 * Article.h
 *
 *  Created on: Feb 5, 2014
 *      Author: djvibegga
 */

#ifndef ARTICLE_H_
#define ARTICLE_H_

#include <db/ar/CActiveRecord.h>

class Article: public CActiveRecord
{
	DECLARE_AR_CLASS(Article)
	DECLATE_AR_ATTRIBUTE(AR_ATTRIBUTE_ULONG, id)
	DECLATE_AR_ATTRIBUTE(AR_ATTRIBUTE_STRING, name)
	DECLARE_ATTRIBUTE_POPULATE()
	DECLARE_ATTRIBUTES_GETSET()
	DECLARE_PRIMARY_KEY()

public:

	Article(const string & scenario = "", CDbConnection * connection = 0);
	Article(const Article & other);
	virtual ~Article();
};

#endif /* ARTICLE_H_ */
