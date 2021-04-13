//
//  IRSQLMaker.hpp
//  IRiMaS
//
//  Created by Keitaro on 03/09/2019.
//

#ifndef IRSQLMaker_hpp
#define IRSQLMaker_hpp

#include "JuceHeader.h"
#include "SQLDataHeader.h"
#include "sqlite3.h"
#include "csv.h"


class IRSQLMaker
{
public:
    IRSQLMaker(std::vector<SQLDataHeader> SQLHeader,
               String databasePath,
               String SQLPath);
    ~IRSQLMaker();
    
    // ==================================================
    
    
    //Create SQL Table.
    // IRSQL accepts a column holding NULL value (empty)
    void createTable(std::string tableName);
    void loadCSV();
    
    // ==================================================

private:
    // ==================================================
    std::vector<SQLDataHeader> SQLHeader;
    String databasePath;
    String SQLPath;
    
    // ==================================================
    sqlite3* DB;

    // ==================================================
    // ==================================================

};

#endif /* IRSQLMaker_hpp */
