//
//  IRWebComponent.h
//  IRIMAS2020July
//
//  Created by Keitaro on 29/07/2020.
//

#ifndef IRWebComponent_h
#define IRWebComponent_h

#include "JuceHeader.h"
#include "KLib.h"
#include "IRNSViewManager.hpp"

class IRWebComponent : public Component
{
public:
    IRWebComponent()
    {
        createBrowser();
    }
    
    ~IRWebComponent()
    {
        this->browser.reset();
    }
    
    // ==================================================
    
    
    WebBrowserComponent* getBrowser() { return this->browser.get(); }
    // ==================================================
    void bringViewToFront()
    {
        
        // **** add following code in juce::VideoComponent
        /*
         
         void*  getPimpl() {
             if(pimpl.get() != nullptr)
                 return pimpl.get();
             else return nullptr;
         }
         
         */
        /*
    #if JUCE_MAC
        
        if(this->browser.get() == nullptr) return;
        
        NSViewComponent* view = static_cast<NSViewComponent*>(this->browser->getPimpl());
        if(view == nullptr) return;
        IRNSViewManager manager;
        manager.bringOpenGLContextFront(this, view);
        
    #endif*/
        
    }
    // ==================================================

private:
    
    void paint(Graphics& g) override
    {
     
    }
    
    void resized() override
    {
        this->browser->setBounds(getLocalBounds());
    }
    
    // ==================================================
    void mouseDown(const MouseEvent& e) override
    {
        std::cout << "IRWebComponent::mouseDown\n";
    }

    
    // ==================================================

    void createBrowser()
    {
        this->browser.reset( new WebBrowserComponent() );
        addAndMakeVisible(this->browser.get());
        
        this->browser->setInterceptsMouseClicks(true, true);

    }
    
    
    std::shared_ptr<WebBrowserComponent> browser;
    
};

#endif /* IRWebComponent_h */
