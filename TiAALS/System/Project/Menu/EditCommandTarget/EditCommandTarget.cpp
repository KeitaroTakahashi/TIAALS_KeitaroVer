
#include "EditCommandTarget.hpp"





EditCommandTarget::EditCommandTarget(ApplicationCommandManager& m)
    : commandManager(m),
    windowCommandTarget(commandManager)
{
    // std::cout << "EditCommandTarget" << std::endl;
    commandManager.registerAllCommandsForTarget(this);
    
    addAndMakeVisible(this->windowCommandTarget);
}


void EditCommandTarget::resized()
{
    this->windowCommandTarget.setBounds(getLocalBounds().reduced (50));
}


void EditCommandTarget::paint(Graphics& g)
{
    
}


ApplicationCommandTarget* EditCommandTarget::getNextCommandTarget()
{
    return &this->windowCommandTarget;
}


void EditCommandTarget::getAllCommands(Array<CommandID>& c)
{
    Array<CommandID> commands
    {
        CommandIDs::EditMode,
        CommandIDs::LinkMode,
        CommandIDs::Undo,
        CommandIDs::Redo,
        CommandIDs::Cut,
        CommandIDs::Copy,
        CommandIDs::Paste,
        CommandIDs::Duplicate
    };
    c.addArray (commands);
}


void EditCommandTarget::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
    
    switch (commandID)
    {
        case CommandIDs::EditMode:
            result.setInfo("EditMode", "Switch Edit Mode", "Edit", 0);
            result.addDefaultKeypress('e', ModifierKeys::commandModifier);
            break;
        case CommandIDs::LinkMode:
            result.setInfo("LinkMode", "Switch Link Mode", "Link", 0);
            result.addDefaultKeypress('l', ModifierKeys::commandModifier);
            break;
        case CommandIDs::Undo:
            result.setInfo("Undo", "Sets the outer colour to red", "Edit", 0);
            result.addDefaultKeypress('z', ModifierKeys::commandModifier);
            break;
        case CommandIDs::Redo:
            result.setInfo("Redo", "Sets the outer colour to red", "Edit", 0);
            result.addDefaultKeypress('z', ModifierKeys::shiftModifier);
            break;
        case CommandIDs::Cut:
            result.setInfo("Cut", "Sets the outer colour to red", "Edit", 0);
            result.addDefaultKeypress('x', ModifierKeys::commandModifier);
            break;
        case CommandIDs::Copy:
            result.setInfo("Copy", "Sets the outer colour to red", "Edit", 0);
            result.addDefaultKeypress('c', ModifierKeys::commandModifier);
            break;
        case CommandIDs::Paste:
            result.setInfo("Paste", "Sets the outer colour to red", "Edit", 0);
            result.addDefaultKeypress('v', ModifierKeys::commandModifier);
            break;
        case CommandIDs::Duplicate:
            result.setInfo("Duplicate", "Sets the outer colour to red", "Edit", 0);
            result.addDefaultKeypress('d', ModifierKeys::commandModifier);
            break;
            
        default:
            break;
    }
}


bool EditCommandTarget::perform(const InvocationInfo& info)
{
    switch (info.commandID)
    {
        case CommandIDs::EditMode:
            callPerformEditModeChange();
            break;
        case CommandIDs::LinkMode:
            callPerformLinkModeChange();
            break;
        case CommandIDs::Undo:
            break;
        case CommandIDs::Redo:
            break;
        case CommandIDs::Cut:
            break;
        case CommandIDs::Copy:
            break;
        case CommandIDs::Paste:
            break;
        case CommandIDs::Duplicate:
            break;
        default:
            return false;
    }
    
    repaint();
    return true;
}


void EditCommandTarget::callPerformEditModeChange() // fire performEditModeChange() methods in Listener
{
    std::cout << "callPerformEditModeChange : " << std::endl;
    Component::BailOutChecker checker(this);
    //==========
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.performEditModeChange(); });
    //check again
    if(checker.shouldBailOut()) return;
    //std::function
    if(this->performEditModeChangeCompleted != nullptr) this->performEditModeChangeCompleted();
    
}

void EditCommandTarget::callPerformLinkModeChange()
{
    Component::BailOutChecker checker(this);
    //==========
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.performLinkModeChange(); });
    //check again
    if(checker.shouldBailOut()) return;
    //std::function
    if(this->performLinkModeChangeCompleted != nullptr) this->performLinkModeChangeCompleted();
    
    }
