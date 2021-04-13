//
//  IRFileInspecterWindow.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 11/03/2019.
//

#ifndef IRFileInspecterWindow_hpp
#define IRFileInspecterWindow_hpp

#include "JuceHeader.h"
#include "IRFileInspecter.hpp"
#include "IRFileManager.hpp"

class IRFileInspecterWindow : DocumentWindow
{
public:
    IRFileInspecterWindow(String name);
    ~IRFileInspecterWindow();
    
    // ==================================================
    void closeButtonPressed() override;
    
    void show();
    
    void updateInspecter();
    
    // ==================================================
    
    void setFileManager(IRFileManager* fileManager);

private:
    
    std::shared_ptr<IRFileInspecter> fileInspecter;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRFileInspecterWindow)
};

#endif /* IRFileInspecterWindow_hpp */
