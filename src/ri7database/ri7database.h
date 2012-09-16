#pragma once

#include "sqlite\sqlite3.h"
#include <iostream>



namespace ri7
{
    namespace data
    {
	
		class SimpleTable;
        class DataBase{
        private:
        sqlite3 *sqlite_db;
        char *zErrMsg;
        char **ColName;
        char **argv;
        int argc;

        static int callback(void *NotUsed, int argc, char **argv, char **azColName);

        protected:
        public:
            DataBase();
            ~DataBase();
			
            int open(std::string filename);
            char **query(int &rows,int &cols,char *queryf, ...);
			SimpleTable *CreateSimpleTable();
        };

    }
}
