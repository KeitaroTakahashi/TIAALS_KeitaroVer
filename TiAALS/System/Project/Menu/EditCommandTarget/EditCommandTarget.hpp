
#ifndef EditCommandTarget_hpp
#define EditCommandTarget_hpp

#include "JuceHeader.h"

#include "Menus.h"
#include "WindowCommandTarget.hpp"





class EditCommandTarget : public Component,
                          public ApplicationCommandTarget
{
    
public:
    
    EditCommandTarget(ApplicationCommandManager& m);
    
    void resized() override;
    void paint(Graphics& g)override;
    
    ApplicationCommandTarget* getNextCommandTarget() override;
    
    void getAllCommands(Array<CommandID>& c) override;
    void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) override;
    
    bool perform (const InvocationInfo& info) override;
    
    class Listener
    {
    public:
        virtual ~Listener() {}
        
        // write methods called by IRNodeComponent objects.
        virtual void performEditModeChange() {};
        virtual void performLinkModeChange() {};
        
    };
    
    virtual void addListener(Listener* newListener) { this->listeners.add(newListener); }
    virtual void removeListener(Listener* listener) { this->listeners.remove(listener); }
    
    std::function<void()> performEditModeChangeCompleted;
    std::function<void()> performLinkModeChangeCompleted;

    void callPerformEditModeChange(); // fire performEditModeChange() methods in Listener
    void callPerformLinkModeChange();
    
private:
    
    ApplicationCommandManager& commandManager;
    ListenerList<Listener> listeners;
    WindowCommandTarget windowCommandTarget;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditCommandTarget)
    
};




#endif /* EditCommandTarget_hpp */





