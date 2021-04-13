
#ifndef ObjectListMenu_hpp
#define ObjectListMenu_hpp

#include "JuceHeader.h"

#include "ObjectListMenuObject.hpp"




class ObjectListMenu : public MenuObject
{
    
public:
    
    ObjectListMenu(Component* parent, Rectangle<int>frameRect);
    ~ObjectListMenu();
    
    void paint (Graphics& g) override;
    void resized() override;
    
    void selectedItemChanged(int itemIndex) override;
    void selectedItemDoubleClicked(int itemIndex) override;
    
    void menuScrolled() override;
    
    int getSelectedIndex() const;
    std::string getSelectedId() const;
    
    class Listener
    {
    public:
        virtual ~Listener() {}
        
        virtual void itemSelectionAction(ObjectListMenu* ) = 0;
        virtual void itemHasSelectedAction(ObjectListMenu* ) = 0;
    };
    
    virtual void addListener(Listener* newListener);
    virtual void removeListener(Listener* listener);
    
    void callItemSelectionAction();
    void callItemHasSelectedAction();
    
    
private:
    
    ListenerList<Listener> listeners;
    
    int selectedIndex = 0;
    std::string selectedID;
    Rectangle<int> frameRect;
    
    ObjectListMenuObject* menu;
    
    // system appearance
    IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();
};

#endif /* ObjectListMenu_hpp */



