
#ifndef WindowCommandTarget_hpp
#define WindowCommandTarget_hpp

#include "JuceHeader.h"

#include "Menus.h"
#include "IRFileInspecterWindow.hpp"




class WindowCommandTarget : public Component, public ApplicationCommandTarget
{
    
public:
    
    WindowCommandTarget(ApplicationCommandManager& m);
    
    void resized() override;
    void paint(Graphics& g)override;
    
    ApplicationCommandTarget* getNextCommandTarget() override;
    
    void getAllCommands(Array<CommandID>& c) override;
    
    void getCommandInfo (CommandID commandID, ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo& info) override;
    
    // ==================================================

    void createIRInspecterWindow();
    
    
    // ==================================================

    
private:
    
    ApplicationCommandManager& commandManager;
    
    
    
};




#endif /* WindowCommandTarget_hpp */




