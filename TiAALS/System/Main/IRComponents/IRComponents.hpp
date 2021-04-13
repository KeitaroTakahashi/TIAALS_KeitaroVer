//
//  IRComponents.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 14/04/2019.
//
//
// Pack of essential components of IRiMaS interface
//

#ifndef IRComponents_hpp
#define IRComponents_hpp

#include "JuceHeader.h"
#include "IRFileManager.hpp"
#include "ColourLib.h"

class IRComponents
{
public:
    IRComponents() {}
    
    ~IRComponents() { /* no delete here! */}
    
    // --------------------------------------------------
    
    // set IRFileManager from IRProject
    void setIRFileManager(IRFileManager* manager);
    IRFileManager* getFileManager() { return this->fileManager; }
    
    void createFileManager();
    
    // use this only when you are sure that other objects are not refering this
    void deleteFileManager();
    
    IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();
    
    // --------------------------------------------------
    
    std::function<void(IRFileManager*)> fileManagerUpdated;
    
    // --------------------------------------------------
    
private:
    // IRFileManager is exclusive for each Project
    // DO NOT USE SHARED_PTR here but leave it as a simple pointer
    IRFileManager* fileManager;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRComponents)
};


#endif /* IRComponents_hpp */
