#include <iostream>
#include "ri7database\table.h"

using namespace std;

int main()
{
  //  ri7::database::Database Data;
    ri7::data::DataBase *db=new ri7::data::DataBase();
    db->open("DataBase.db");

	ri7::data::SimpleTable myTable(db);
	ri7::data::SimpleTable myTable2(db);
	
	myTable2.AddCol("real_name",ri7::data::DB_TYPE_STRING,32);
	myTable2.Fill("SELECT real_name FROM users");
	cout << "Users on DB " << myTable2.GetRows() << endl ;

	/*
	Table miTabla = miBaseDatos.CreateTable();
	miTabla.AddCol("userName", "nvarchar(50)");
	miTabla.AddCol("numPKs", "int");
	miTable.fill( "SELECT * FROM users" );
	*/
   // Data.open("DataBase.db");
    //Data.query("SELECT real_name FROM users WHERE id_user='root'");
    myTable.AddCol("id_user",ri7::data::DB_TYPE_STRING,32);
    myTable.AddCol("password",ri7::data::DB_TYPE_STRING,32);
    myTable.AddCol("real_name",ri7::data::DB_TYPE_STRING,32);
	myTable.AddCol("level",ri7::data::DB_TYPE_INTEGER);
	
    
	myTable.Fill("SELECT * FROM users");
	cout << "Users on DB " << myTable.GetRows() << endl ;

	for(int i=0;i<myTable.GetRows();i++)
	{
		cout << "User " << i << endl;
		cout << "->id_user   is " << myTable.GetString(i,"id_user").c_str() << endl;
		cout << "->password  is " << myTable.GetString(i,"password").c_str() << endl;
		cout << "->real_name is " << myTable.GetString(i,"real_name").c_str() << endl;
		cout << "->Level     is " << myTable.GetInt(i,"level") << endl;
	}

	for(int i=0;i<myTable.GetRows();i++)
	{
		cout << "User " << i << endl;
		cout << "->id_user   is " << myTable.GetString(i,"id_user").c_str() << endl;
		cout << "->password  is " << myTable.GetString(i,"password").c_str() << endl;
		cout << "->real_name is " << myTable.GetString(i,"real_name").c_str() << endl;
		cout << "->Level     is " << myTable.GetInt(i,"level") << endl;
	}


    return 0;
}
