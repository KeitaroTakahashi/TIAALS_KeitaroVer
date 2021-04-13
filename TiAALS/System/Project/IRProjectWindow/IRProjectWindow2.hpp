//
//  IRProjectWindow2.hpp
//  IRiMaS
//
//  Created by Keitaro on 09/08/2019.
//

#ifndef IRProjectWindow2_hpp
#define IRProjectWindow2_hpp

#include "IRMainWindow.hpp"

class IRProjectWindow2 : public IRMainWindow,
public ChangeListener
{
public:
    IRProjectWindow2(String name, Rectangle<int> frameRect);
    ~IRProjectWindow2();
    // ==================================================
    void createInitialWorkspace();
    // ==================================================
    
    void initializeUI();
    // ==================================================
    void loadProjectFromSaveData(t_json saveData);
    
    void setProjectTitle(String title);
    void setProjectPath(String path);
    // ==================================================

    
    void windowMoveToPos(juce::Point<int>pos);
    
    // ==================================================

    // AudioApp Component
    AudioSource& getMixer() override { return this->comp->getMixer(); }

    // ==================================================
    
    class Listener
    {
    public:
        virtual ~Listener() {}
        
        virtual void closeThisWindow(IRMainWindow* window) = 0;
    };
    
    virtual void addListener(Listener* newListener) { this->listeners.add(newListener); }
    virtual void removeListener(Listener* listener) { this->listeners.remove(listener); }
    ListenerList<Listener> listeners;
    
    void callCloseThisWindow();
    
    void setNewProjectCallbackFunc(std::function<void()> callback);
    void setOpenProjectCallbackFunc(std::function<void()> callback);

    
    // ==================================================

    
private:
    
    void changeListenerCallback (ChangeBroadcaster* source) override;
    
    void closeButtonPressed() override;
    
    // ==================================================
    
    void newProjectCallbackAction();
    std::function<void()> newProjectCallback;
    void openProjectCallbackAction();
    std::function<void()> openProjectCallback;
    
    std::shared_ptr<IRWindowComponent> comp;
   
    // ==================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRProjectWindow2)

};

#endif /* IRProjectWindow2_hpp */
