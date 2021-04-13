//
//  srtLoader.h
//  IRiMaS
//
//  Created by Keitaro on 19/01/2020.
//

#ifndef srtLoader_h
#define srtLoader_h

#include "srtparser.h"

class srtLoader
{
public:
    srtLoader()
    {
        
    }
    
    ~srtLoader()
    {
        this->parserFactory.reset();
    }
    
    void openFile(std::string path)
    {
        this->path = path;
        
        File file (this->path);
        if(file.exists())
        {
            this->parserFactory.reset( new SubtitleParserFactory(path));
            SubtitleParser *parser = this->parserFactory->getParser();

            this->items = parser->getSubtitles();
        }
    }
    
    std::vector<SubtitleItem*> getSubtitleItems() { return this->items; }
    
private:
    std::string path;
    std::shared_ptr<SubtitleParserFactory> parserFactory;
    
    std::vector<SubtitleItem*> items;
};

#endif /* srtLoader_h */
