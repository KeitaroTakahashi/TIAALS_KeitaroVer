
#ifndef MenuObject_hpp
#define MenuObject_hpp

#include "JuceHeader.h"

#include "MenusListBox.h"




class MenuObject : public Component,
public ChangeListener,
public ChangeBroadcaster
{
    
public:
    
    MenuObject(Component* parent);
    ~MenuObject();
    
    void paint (Graphics& g) override;
    void resized() override;
    
    virtual void selectedItemChanged(int itemIndex) = 0;
    virtual void selectedItemDoubleClicked(int itemIndex) = 0;
    
    virtual void menuScrolled();
    
    void showWindow();
    void closeWindow(); // when X button pressed and menu selection interrupted.
    void completeSelection(); // when Done button pressed and menu selection completed.
    
    void setListBoxComponent(IRTableListBox* menu);
    
    IRTableListBox* getListMenu();
    MenuObjectStatus getStatus() const;
   
    
private:
    
    void changeListenerCallback (ChangeBroadcaster* source) override;
    
    
    Component* parent;
    
    IRTableListBox* ListMenu = nullptr;
    
    MenuObjectStatus status;
    
    /*
     BackForwardButton *closeButton = nullptr;
     
     TextButton menuOKButton;
     
     Image backgroundImage;
     bool isBackgroundImage = false;
     */

};

#endif /* MenuObject_hpp */




