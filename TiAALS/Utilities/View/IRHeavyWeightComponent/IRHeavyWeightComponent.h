//
//  IROpenGLRenderer.h
//  IRiMaS
//
//  Created by Keitaro on 17/11/2019.
//

#ifndef IROpenGLRenderer_h
#define IROpenGLRenderer_h

#include "JuceHeader.h"

/*
    This class converts a light-weight juce::Component to heavy-weight Component by the power of OpenGL.
    It uses Objective-C++ to access NSOpenGLView->NSView and this source code supports macOS only.
    Inherit this class in your juce::Component based objects.
    Keitaro 2019 Nov
 */



class IRHeavyWeightComponent : OpenGLRenderer
{
public:
    IRHeavyWeightComponent(juce::Component* component, String name);
    virtual ~IRHeavyWeightComponent();
    
   //==================================================
    virtual void componentCreated() {};
    //==================================================

    void setHeavyWeightBackgroundAlpha(float alpha) { this->alpha = alpha; }
    
    //==================================================
    //OpenGL
    OpenGLContext ctx;
    void bringThisToFront(String flag = "") {
        
        this->name = flag;
        bringToFrontObj(this->component);
        this->component->toFront(true);
        //callback
        bringToFrontCompleted();
    }
    
    void heavyWeightRepaint(String flag = "")
    {
        
        //std::cout << flag << std::endl;
        this->ctx.triggerRepaint();
    }
    
    //==================================================
    
    virtual void bringToFrontCompleted() {}
    
    juce::Component* component;
    
    //==================================================

    // using Objective-C++ macOS only!!
    // set up alpha value of NSOpenGLView to make transparent background
    void setComponentAlpha(GLint aValue = 0);
    
private:
    
    // for background transparency
    float alpha = 0.0;
    String name;
    //==================================================

    // bring the juce::Component inheriting this class to the foreground of any other juce::Component or heavy-weight Components
    void bringToFrontObj(juce::Component* owner);


public:
    //==================================================


private:
    void newOpenGLContextCreated()override
    {
        setComponentAlpha(this->alpha);
        componentCreated();
    }
    
    virtual void renderOpenGL()override
    {
        // transparent background
        OpenGLHelpers::clear(Colours::transparentBlack);

    }
    
    virtual void openGLContextClosing() override {}

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRHeavyWeightComponent)

};

#endif /* IROpenGLRenderer_h */
