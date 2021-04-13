//
//  IRJson.hpp
//  IRiMaS
//
//  Created by Keitaro on 17/06/2020.
//

#ifndef IRJson_hpp
#define IRJson_hpp

#include <stdio.h>
#include <fstream>
#include "JuceHeader.h"
#include "KLib.h"
#include "json11.hpp"

typedef json11::Json t_json;

class IRJson
{
  
public:
    
    IRJson();
    ~IRJson();
    
    void writeSaveData(std::string filePath);
    
    void readSaveData(std::string filePath);
    
    void setData(t_json data) { this->data = data; }
    t_json getData() { return this->data; }
    
private:
    t_json data;
    
    
    
};

#endif /* IRJson_hpp */
