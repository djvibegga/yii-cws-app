/*
 * DbConnection.cpp
 *
 *  Created on: Apr 12, 2015
 *      Author: djvibegga
 */

#include "components/DbConnection.h"
#include <boost/assign/list_of.hpp>

DbConnection::DbConnection(CModule * module)
: CDbConnection(module)
{
}

DbConnection::DbConnection(CModule * module, string dsn, string username, string password)
: CDbConnection(module, dsn, username, password)
{
}

void DbConnection::initSchema(CDbSchema & schema)
{
	CDbTableSchema pageTable;
	pageTable.setTableName("page");
	pageTable.setPrimaryKey(boost::assign::list_of("id"));
	schema.addTableSchema(pageTable);

	CDbTableSchema articleTable;
	pageTable.setTableName("article");
	pageTable.setPrimaryKey(boost::assign::list_of("id"));
	schema.addTableSchema(articleTable);

	CDbTableSchema articleCategoryTable;
	articleCategoryTable.setTableName("article_category");
	articleCategoryTable.setPrimaryKey(boost::assign::list_of("id"));
	schema.addTableSchema(articleCategoryTable);

	CDbTableSchema tagTable;
	tagTable.setTableName("tag");
	tagTable.setPrimaryKey(boost::assign::list_of("id"));
	schema.addTableSchema(tagTable);

	CDbTableSchema objectTable;
	objectTable.setTableName("object");
	objectTable.setPrimaryKey(boost::assign::list_of("id"));
	schema.addTableSchema(objectTable);
}
