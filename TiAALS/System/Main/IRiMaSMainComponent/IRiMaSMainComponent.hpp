
#ifndef IRiMaSMain_hpp
#define IRiMaSMain_hpp
#include <filesystem>
#include "JuceHeader.h"

#include "IRSystemStatus.h"
#include "IRProjectWindow2.hpp"
#include "IRStartWindow.hpp"
#include "IRSaveLoadSystem.hpp"
#include "json11.hpp"
#include "singletonClass.hpp"
#include "IRObjectFactory2.hpp"


#include "ColourLib.h"

/*
 IRiMaSMainComponent : AudioAppComponent
 |                  |
 IRStartWindow      IRProjectWindow2
 |                  |
 IRStarter          IRWindowComponent -----------------------------------------------------------
                    |                       |                    |               |
                    IRMainSpace             IRTitleBar           IRLeftBar       IRRightBar
                    |                       |                    |
                    IRWorkspace             IRTitleBarComponent

IRMAIN class operates;
    creating new project
    opening a saved project

 */

// AudioAppComponent

class IRiMaSMainComponent : public AudioAppComponent,
                            public ChangeListener,
public IRProjectWindow2::Listener
{
    
public:
    IRiMaSMainComponent(const String applicationName);
    ~IRiMaSMainComponent();
    // =======================================================
    void initialise();
    // =======================================================
    // System
    // Save Action is managed by each project
    void createNewProject();
    void createNewProjectFromSaveData(std::string path);
    void openProject();
    void closeProject(DocumentWindow* closingWindow);
    // =======================================================

    
private:
    // =======================================================
    //AudioAppComponent
    AudioEngine mixer;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override;
    void releaseResources() override;
    
    // AudioAppComponent
    void audioSetup();
    void closeAudioSetup();
    // =======================================================

    void changeListenerCallback(ChangeBroadcaster* source) override;
    // =======================================================
    
    IRProjectWindow2* createProjectObject(String projectName = "project");

    // from IRProjectWindow2 Listener method
    void closeThisWindow(IRMainWindow* closeWindow) override;
    
    String applicationName;
    std::string saveDataPath { "" };
    
    // storing all project windows
    std::vector<IRProjectWindow2* >projectLib;
 
    // PreferenceWindow* preferenceWindow;
    std::shared_ptr<PreferenceWindow> preferenceWindow;
    
    // start window initially opened when launching this app
    std::unique_ptr<IRStartWindow> startWindow;
    // =======================================================

    // for save and load projects
    IRSaveLoadSystem saveLoadClass;
    json11::Json saveData;
    // =======================================================

    IRObjectFactory2& IRFactory2 = singleton<IRObjectFactory2>::get_instance();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRiMaSMainComponent)
    // =======================================================

};





#endif /* IRiMaSMain_hpp */




