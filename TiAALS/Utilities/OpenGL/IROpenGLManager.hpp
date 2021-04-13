//
//  glTest.hpp
//  IRiMaS
//
//  Created by Keitaro on 31/10/2019.
//

#ifndef glTest_hpp
#define glTest_hpp

#include "JuceHeader.h"

/*
    IROpenGLManager is responsible for all tasks regarding with juce::OpenGLContext.
    
    The methods defined in this class are OS related, and therefore, we need to implement the methods for all OS respectively.
 
    Currently, only macOS is available.
 */


class IROpenGLManager
{
public:
    IROpenGLManager(OpenGLContext* context, String name) :
    context(context),
    name(name)
    {
        
    }
    ~IROpenGLManager()
    {
        
    }
    
    void setOpenGLContextAlpha(GLint aValue = 0);
    void bringOpenGLContextFront(juce::Component* owner);
    
private:
    OpenGLContext* context;
    String name;
};

#endif /* glTest_hpp */
