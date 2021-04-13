//
//  IRSQLMaker.cpp
//  IRiMaS
//
//  Created by Keitaro on 03/09/2019.
//

#include "IRSQLMaker.hpp"

IRSQLMaker::IRSQLMaker(std::vector<SQLDataHeader> SQLHeader,
                       String databasePath,
                       String SQLPath) :
SQLHeader(SQLHeader),
databasePath(databasePath),
SQLPath(SQLPath)
{
    
}

IRSQLMaker::~IRSQLMaker()
{
    
}
// ==================================================

void IRSQLMaker::createTable(std::string tableName)
{
    char* err = nullptr;
    
    std::string tn = "DROP TABLE IF EXISTS " + tableName;
    const char *drop_table = tn.c_str();
    
    int rc = sqlite3_exec(this->DB, drop_table, NULL, NULL, &err);
    
    // table
    std::string table_Com = "CREATE TABLE IF NOT EXISTS " + tableName +
    "(IRID INTEGER PRIMARY KEY AUTOINCREMENT, ";
    for(auto sq : this->SQLHeader)
    {
        table_Com += sq.columnTitle + " ";
        table_Com += sq.getDataTypeInSQLString() + ", ";
    }
    table_Com += ")";
    
    rc = sqlite3_exec(this->DB,
                      table_Com.c_str(),
                      NULL,
                      NULL,
                      &err);
    if(rc != SQLITE_OK)
    {
        std::cout << "ERROR : SQLITE createTable Could not create a table : " << rc << std::endl;
        sqlite3_free(err);
        err = nullptr;
        return;
    }
    
    sqlite3_exec(this->DB,
                 "PRAGMA journal_mode = WAL;",
                 NULL,
                 NULL,
                 NULL);
    
    sqlite3_exec(this->DB,
                 "begin",
                 NULL,
                 NULL,
                 NULL);
    
}

void IRSQLMaker::loadCSV()
{
    //const int num = (const int)this->SQLHeader.size();
    //io::CSVReader<20> in(this->databasePath);
   // in.read_header(io::ignore_extra_column)
}
// ==================================================
