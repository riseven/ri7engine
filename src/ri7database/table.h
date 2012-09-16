#pragma once


#include "sqlite\sqlite3.h"
#include <iostream>
#include <vector>

#include "ri7database.h"
namespace ri7
{
    namespace data
    {
		enum EnumDataBaseTypes
		{
			DB_TYPE_UNKNOWN = 0x00,
			DB_TYPE_STRING  = 0x01,
			DB_TYPE_INTEGER = 0x02,
			DB_TYPE_FLOAT   = 0x03
		};
		class Column
		{
		private:
			EnumDataBaseTypes type;
			int size;
			int offset;
		public:
			std::string Name;
			Column(){}
			~Column(){}
			void SetType(EnumDataBaseTypes type,int length=1)
			{
			    this->type=type;
			    switch(this->type)
			    {
			        case DB_TYPE_INTEGER:
                        this->size=4;
                    break;
                    case DB_TYPE_FLOAT:
                        this->size=8;
                    break;
                    case DB_TYPE_STRING:
                        this->size=((length+5)/4)*4;  //Para el end_of_string \0 y hacerlo multiplo de 4
                    break;
                    default:
                        this->size=0;
                    break;


			    }
			}

            EnumDataBaseTypes GetType()
            {
                return this->type;
            }

            void SetName(std::string name)
            {
                this->Name=name;
            }

			inline std::string GetName()
			{
				return this->Name;
			}
            void SetOffset(int offset)
            {
                this->offset=offset;
            }
            int GetOffset()
			{
                return offset;
            }
			int GetSize()
			{
			   return size;
            }


		};
		class SimpleTable {
		private:
			char **sqlite_result;
			int nrows;
			int ncols;
			std::vector< Column > columns;
			DataBase *db;
			int rowSize;
			int offset;
			int offset_max;
			unsigned char *data;

			int GetRowIndex(std::string rowname);

		public:
			SimpleTable(DataBase *db) : db(db), nrows( 0 ), ncols( 0), data( 0 ), rowSize( 0 ) , offset(0) , offset_max(0) {}
			void AddCol(std::string colname,EnumDataBaseTypes type,int lenght=1);
			inline int GetRows()
			{
				return this->nrows;
			}
			//void Fill(std::string consult);
			void Fill(std:: string consult);
			float GetFloat(int nrow, int ncol);
            std::string GetString(int nrow, int ncol);
            int GetInt(int nrow, int ncol);
			std::string GetString(int nrow,std::string colname);
			int GetInt(int nrow, std::string colname);

		};
    }
}
