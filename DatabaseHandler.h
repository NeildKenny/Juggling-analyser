#pragma once

/*
Author: Neil Kenny 

Database handler class, required to handle connection and query database

Tutorial refrences:
http://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm

*/
#include "stdAfx.h"
#include "sqlite3.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
class DatabaseHandler
{

private:

	int rc;
	char *zErrMsg;
	sqlite3 *db;


public:
	
	
	

	/**
	Connects to database and failing that creates it
	*/
	DatabaseHandler(void);

	/**
	Closes database connection
	*/
	~DatabaseHandler(void);
	
	/*
	Contains sql statement to create the trainer table and 
	calls for it to be created
	**/
	void CreateTrainerTable(void);
	
	/*
	Contains sql statement to create the program table and 
	calls for it to be created
	**/
	void CreateProgramTable(void);

	/**
	Runs sql statememnt to create the table
	@param [in] sql statement
	*/
	void CreateStatement(char *sql);
	
	
	/**
	Runs sql statememnt for insert update and deletion on tables
	@param [in] sql statement
	*/
	void SUDSatement(char *sql);

	/**
	Statement for querying the database
	@param [in]  a select statement as a string of characters
	@return [out] a vector of vector of strings

	
	*/
	std::vector<std::vector<std::string>> Query(char *query);

};

