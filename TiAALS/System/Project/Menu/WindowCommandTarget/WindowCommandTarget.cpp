
#include "WindowCommandTarget.hpp"




WindowCommandTarget::WindowCommandTarget(ApplicationCommandManager& m) : commandManager(m)
{
    commandManager.registerAllCommandsForTarget(this);
}


void WindowCommandTarget::resized()
{
    
}


void WindowCommandTarget::paint(Graphics& g)
{
    
}


ApplicationCommandTarget* WindowCommandTarget::getNextCommandTarget()
{
    return findFirstTargetParentComponent();
}


void WindowCommandTarget::getAllCommands(Array<CommandID>& c)
{
    Array<CommandID> commands { CommandIDs::fileInspecterWindow,
                                CommandIDs::menuPreferenceWindow
                                };
    c.addArray (commands);
}


void WindowCommandTarget::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
    switch (commandID)
    {
        case CommandIDs::fileInspecterWindow:
            result.setInfo ("fileInspecter Window", "Sets the outer colour to red", "Window", 0);
            result.addDefaultKeypress ('8', ModifierKeys::commandModifier);
            break;
            
        case CommandIDs::menuPreferenceWindow:
            result.setInfo ("Preference Window", "Sets the outer colour to red", "Window", 0);
            result.addDefaultKeypress ('9', ModifierKeys::commandModifier);
            break;

        default:
            break;
    }
}


bool WindowCommandTarget::perform(const InvocationInfo& info)
{
    switch(info.commandID)
    {
        
        case CommandIDs::fileInspecterWindow:
            std::cout << "window menu perform" << std::endl;
            break;
        case CommandIDs::menuPreferenceWindow:
            break;
        default:
            return false;
    }
    
    repaint();
    return true;
}




