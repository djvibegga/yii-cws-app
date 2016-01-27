/*
 * DbConnection.h
 *
 *  Created on: Apr 12, 2015
 *      Author: djvibegga
 */

#ifndef DBCONNECTION_H_
#define DBCONNECTION_H_

#include <db/CDbConnection.h>

class DbConnection: public CDbConnection
{
public:
	DbConnection(CModule * module);
	DbConnection(CModule * module, string dsn, string username, string password);

protected:
	virtual void initSchema(CDbSchema & schema);
};

#endif /* DBCONNECTION_H_ */
