#include "table.h"

namespace ri7
{
	namespace data
	{

		void SimpleTable::AddCol(std::string colname,EnumDataBaseTypes type,int lenght)
		{
			Column NewCol;
			NewCol.SetName(colname);
			NewCol.SetType(type,lenght);
			NewCol.SetOffset(offset_max);
			offset_max+=NewCol.GetSize();
			columns.push_back(NewCol);
			std::cout << "[ADDCOL] Name:" << colname.c_str() << " Lenght: " << lenght << " Type: "<< type << " Offset_max :" << offset_max << std::endl;

		}

		void SimpleTable::Fill(std:: string consult) {
			sqlite_result = db->query(nrows,ncols,(char*)consult.c_str());

			for(unsigned int i=0;i<columns.size();i++)
			{
				rowSize+=columns.at(i).GetSize();
			}
//			std::cout << "Size total is " << rowSize * nrows << " " << nrows << " x " << ncols << std::endl;



			data = new unsigned char[ nrows * rowSize ];
			
			int cols=0;

			for(int i=ncols; i<(ncols)*(nrows+1); i++){
				
				if(cols==ncols)
				{
					cols=0;
				}
				

				switch(columns.at(cols).GetType())
				{
				case DB_TYPE_INTEGER:
					//std::cout << "DB_TYPE_INTEGER " <<  offset << std::endl;
					*(  (int *)((int)data) + offset) =  atoi(sqlite_result[i]);
					offset+=4;

					break;
				case DB_TYPE_FLOAT:
					//std::cout << "DB_TYPE_FLOAT " <<  offset << std::endl;
					*(  (float *)((int)data) + offset) = atof(sqlite_result[i]);
					offset+=8;
					break;
				case DB_TYPE_STRING:
					//std::cout << "DB_TYPE_STRING " <<  offset <<  std::endl;
					memcpy(data + offset ,sqlite_result[i],strlen(sqlite_result[i]));
					data[offset+strlen(sqlite_result[i])]='\0';
					offset+=columns.at(cols).GetSize();
					break;


				}
				cols++;
			
			}
			


		}
		int SimpleTable::GetInt(int nrow, int ncol) {
			return *(  (int *)((int)data) + (nrow * rowSize ) +columns.at(ncol).GetOffset());
		}
		std::string SimpleTable::GetString(int nrow, int ncol)
		 {
			 //char *str=new char[columns.at(ncol).GetSize()]; //<----Lol?? Con esto peta!!!! :S

			 //char str[1024];
			
			 //std::string str2;
			 //memcpy(str,data + (nrow * rowSize ) +columns.at(ncol).GetOffset(),columns.at(ncol).GetSize() );
			 //str2=str;
	
			 //return str;
			
			 return (char*)( data + (nrow * rowSize ) +columns.at(ncol).GetOffset());

		 }
		
		 int SimpleTable::GetInt(int nrow, std::string colname)
		 {
			 int ncol=GetRowIndex(colname);

			 if(ncol<0)
				 return NULL;
			 return GetInt(nrow,ncol);

		 }
		std::string SimpleTable::GetString(int nrow,std::string colname)
		{
			int ncol=GetRowIndex(colname);
			
			if(ncol<0)
				return "(null)";
			return GetString(nrow,ncol);
		}

		 float SimpleTable::GetFloat(int nrow, int ncol) {
			// std::cout << "OffSET: " <<  (nrow * rowSize ) + columns.at(ncol).GetOffset() << std::endl ;
			 return *(  (float *)((int)data) + (nrow * rowSize ) +columns.at(ncol).GetOffset());
		 }

		 int SimpleTable::GetRowIndex(std::string colname)
		 {
			 for(unsigned int i=0;i<columns.size();i++)
			 {
				
				 if(colname.compare(columns.at(i).GetName())==0)
					return i;
			 }
			 return -1;
		 }

	}

}
