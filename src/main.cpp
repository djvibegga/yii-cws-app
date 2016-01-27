/*
 * main.cpp
 *
 *  Created on: Oct 13, 2013
 *      Author: djvibegga
 */

#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <base/CEvent.h>
#include <base/CModule.h>
#include <base/CException.h>
#include <base/Cws.h>
#include <db/CDbConnection.h>

#include "interfaces.h"
#include <base/CStatePersister.h>
#include <utils/CArchiver.h>

#include "WebRequestPool.h"

int main(int argc, char* const argv[])
{
	string configPath = getcwd(0, 0);
	configPath += "/main.xml";
	cout << "Config file path: " << configPath << endl;
	try {
		WebRequestPool pool(configPath, argc, argv);
		CDbConnection::glConnection.setClient(SA_MySQL_Client);
		pool.init();
		pool.run();
	} catch (const CException & e) {
		cout << e.getFullMessage() << endl;
		return 1;
	}
    return 0;
}
