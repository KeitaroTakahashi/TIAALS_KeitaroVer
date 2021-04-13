
#ifndef IRStarter_h
#define IRStarter_h

#include "JuceHeader.h"

#include "Menus.h"
#include "IRIconBank.hpp"
#include "IRImageButton.hpp"

class IRStarter : public Component,
                  public ChangeListener,
                  public ChangeBroadcaster
{
    
public:
    /*
    enum class MenuBarPosition
    {
        window, // for windows
        global, // for mac
        burger
    };
    */
    enum MenuActionStatus
    {
        CreateNewProjectAction,
        OpenProjectAction
    };
    
    IRStarter(Rectangle<int> frameRect);
    ~IRStarter();
    
    void paint(Graphics& g) override;
    void resized() override;

    void init();
    
    Image loadImage(String url);
    
    MenuActionStatus getMenuActionStatus() { return this->menu_action_status; }

private:
    
    void createNewProject();
    void openProject();
    
    void changeListenerCallback(ChangeBroadcaster* source) override;

    MenuActionStatus menu_action_status;
    
    // ====================== ============================
    Image logo;
    Rectangle<float> logoPos;
    Image title;
    
    IRIconBank::IRIconImage loadImageAndReturn(String url);
    IRIconBank::IRIconImage loadIconImage(String url);
    void createButton(IRImageButton* button, IRIconBank::IRIconImage img);


    IRIconBank::IRIconImage icon_newProject;
    IRIconBank::IRIconImage icon_openProject_arrow;
    IRImageButton newProjectButton;
    IRImageButton openProjectButton;
    Label newProjectLabel;
    Label openProjectLabel;
    //==================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRStarter)
};




#endif /* IRStarter_h */
