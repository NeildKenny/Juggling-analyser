#include "stdAfx.h"
#include "DatabaseHandler.h"



DatabaseHandler::DatabaseHandler()
{

  

   rc = sqlite3_open("trainer.db", &db);

   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));	
	  void CreateTrainerTable(void);
	void CreateProgramTable(void);
      				
   }else{
      fprintf(stderr, "Opened database successfully\n");

   }
   
}



DatabaseHandler::~DatabaseHandler(void)
{
	sqlite3_close(db);

}


static int CICallback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

static int SUDCallback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

void DatabaseHandler::CreateStatement(char *sql){

	rc = sqlite3_exec(db, sql, CICallback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Created successfully\n");
   }

}

void DatabaseHandler::SUDSatement(char *sql){
	const char* data = "Callback function called";
	rc = sqlite3_exec(db, sql, SUDCallback, (void*)data, &zErrMsg);
	if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation completed successfully\n");
   }
}

std::vector<std::vector<std::string>> DatabaseHandler::Query(char *query){

	

	sqlite3_stmt *statement;

	std::vector<std::vector<std::string>> results;

	if(sqlite3_prepare_v2(db, query, -1, &statement, 0) == SQLITE_OK){
		int cols =sqlite3_column_count(statement);
		int result = 0;

		while(true){
			result = sqlite3_step(statement);

			if(result == SQLITE_ROW){

			   std::vector<std::string> values;
			   for(int col = 0; col < cols; col++){

				 std::string  val;
				 char * ptr = (char*)sqlite3_column_text(statement, col);

				 if(ptr){

				   val = ptr;
				 }
				 else val = ""; 

				 values.push_back(val);  
			   }
			   results.push_back(values);
			}
			else{
			   break;  
			}
		}
			sqlite3_finalize(statement);

	}
	
	return results;
}


void DatabaseHandler::CreateTrainerTable(void){

	char *sql = "CREATE TABLE TUTORIAL(" \
		"ID		INT PRIMARY KEY	NOT NULL," \
		"NAME	TEXT			NOT NULL);";
	CreateStatement(sql);

}

void DatabaseHandler::CreateProgramTable(void){
	char *sql = "CREATE TABLE PROGRAM(" \
		"ID		INT PRIMARY KEY NOT NULL, " \
		"TUTORIALID INT NOT NULL,"\
		"NAME	TEXT		NOT NULL," \
		"SITESWAP INT		NOT NULL," \
		"FOREIGN KEY(TUTORIALID)REFERENCES TUTORIAL(ID) );";
	CreateStatement(sql);
}

