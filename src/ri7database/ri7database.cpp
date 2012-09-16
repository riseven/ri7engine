#include "ri7database.h"
#include "table.h"

using namespace std;

namespace ri7
{
    namespace data
    {
    DataBase::DataBase()
    {
        cout << "DataBase Loaded.." << endl;
    }

    DataBase::~DataBase()
    {
        cout << "DataBase UnLoaded.." << endl;
    }
	
	ri7::data::SimpleTable *DataBase::CreateSimpleTable()
	{
			return new SimpleTable(this);
	}

    int DataBase::open(std::string filename)
    {
        int result;
        result = sqlite3_open(filename.c_str(),&sqlite_db);

        return result;
	}


    int DataBase::callback(void *NotUsed, int argc, char **argv, char **azColName){
            int i;
            cout << "Dumping.." << endl;

            for(i=0; i<argc; i++){
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
            }
            printf("\n");
            return 0;
    }

	char ** DataBase::query(int &rows,int &cols,char *queryf, ...) {
	va_list ap;
	int retval;
	char *error, *query;
    char **pResult;
    int nrow,ncolumn;

	va_start(ap, queryf);
	query = sqlite3_vmprintf(queryf, ap);
	va_end(ap);



	//retval = sqlite3_exec(sqlite_db query, NULL, NULL, &error);
	//retval   = sqlite3_exec(sqlite_db, query, (int (*)(void*,int,char**,char**))callback, 0, &error);
	cout << "Query :" << query << endl;

	retval = sqlite3_get_table(sqlite_db,query, &pResult,&nrow,&ncolumn,&error);


//int sqlite3_get_table(
//  sqlite3*,             /* An open database */
//  const char *sql,      /* SQL to be evaluated */
//  char ***pResult,      /* Results of the query */
//  int *nrow,            /* Number of result rows written here */
//  int *ncolumn,         /* Number of result columns written here */
//  char **errmsg         /* Error msg written here */
//);
      rows=nrow;
      cols=ncolumn;

        //for(int j=0; j<=nrow; j++)
        //{
     /*   int cols=0;
        for(int i=0; i<(ncolumn)*(nrow+1); i++){
            if(cols==ncolumn)
            {
                printf("\n");
                cols=0;
            }
            cols++;

            printf("(%d)%s  ",i, pResult[i]);


            }*/

        //}


	  if( retval!=SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", error);
        sqlite3_free(zErrMsg);
        }

	return pResult;
    }

    }
}
