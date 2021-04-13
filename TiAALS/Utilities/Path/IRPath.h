//
//  IRPath.h
//  TIAALS_LIGHT
//
//  Created by Keitaro on 09/03/2021.
//

#ifndef IRPath_h
#define IRPath_h

#include <JuceHeader.h>

class IRPath
{
public:
    IRPath() {}
    
    String getAppContentsDirectoryPath()
    {
        std::string appPath = File::getSpecialLocation(File::currentApplicationFile).getFullPathName().toStdString();
        // return only till app/
        return String(appPath.erase(appPath.find(".app/")+4));
    }
    
    
};

#endif /* IRPath_h */
