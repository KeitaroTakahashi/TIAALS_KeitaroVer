//
//  IRJson.cpp
//  IRiMaS
//
//  Created by Keitaro on 17/06/2020.
//

#include "IRJson.hpp"

IRJson::IRJson()
{
    
}

IRJson::~IRJson()
{
    
}

void IRJson::writeSaveData(std::string filePath)
{
    std::ofstream myFile;
    // trunc mode : discard previous data and write new save data
    myFile.open(filePath, std::ofstream::trunc);
    myFile << this->data.dump();
    myFile.close();
    
   // std::cout << "========== save data for " << filePath << std::endl;
   // std::cout << this->data.dump() << std::endl;
   // std::cout << "========== end ========== \n" << std::endl;
}

void IRJson::readSaveData(std::string filePath)
{
    //init
    std::string readData;
       
    std::ifstream myFile(filePath);

    if(!myFile){
       std::cout << "Error : Could not open file " << filePath << std::endl;
       return;
    }

    std::string buf;
    while (!myFile.eof())
    {
       std::getline(myFile, buf);
       readData += buf;
    }

    myFile.close();

    std::string err;
    this->data = json11::Json::parse(readData,err);

    if(err.length() != 0)
    {
        std::cout << "Error IRJson readSaveData : " << err << std::endl;
    }
    
}
