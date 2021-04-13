
#include "IRiMaSApplication.hpp"





IRiMaSApplication::IRiMaSApplication()
{
    
}


const String IRiMaSApplication::getApplicationName()
{
    return ProjectInfo::projectName;
}


const String IRiMaSApplication::getApplicationVersion()
{
    return ProjectInfo::versionString;
}


bool IRiMaSApplication::moreThanOneInstanceAllowed()
{
    return false;
}


void IRiMaSApplication::initialise(const String& commandLine)
{
    this->mainComponent.reset(new IRiMaSMainComponent(getApplicationName()));
}


void IRiMaSApplication::shutdown()
{
    this->mainComponent = nullptr;
}


void IRiMaSApplication::systemRequestedQuit()
{
    quit();
}


void IRiMaSApplication::anotherInstanceStarted(const String& commandLine)
{
    
}




