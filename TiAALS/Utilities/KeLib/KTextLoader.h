//
//  KTextLoader.h
//  OpenGLProject
//
//  Created by Keitaro on 26/06/2019.
//

#ifndef KTextLoader_h
#define KTextLoader_h

#include <fstream>
#include <string>
#include "../JuceLibraryCode/JuceHeader.h"

class IRTextLoader
{
public:
    IRTextLoader()
    {
    }
    ~IRTextLoader() {}
    
    void load(std::string url)
    {
        std::ifstream myFile (url);
        std::string line;
        int numLine = 0;
        this->txtData.clear();
        if(myFile.is_open())
        {
            while (getline(myFile, line))
            {
                this->txtData += (line + "\n");
                numLine ++;
                
            }
        }
        
        myFile.close();
    }
    
    
    const char* getConstChar()
    {
        return this->txtData.c_str();
    }
    
    std::string getStdString() const
    {
        return this->txtData;
    }
    
private:
    
    std::string txtData;
};

#endif /* KTextLoader_h */
