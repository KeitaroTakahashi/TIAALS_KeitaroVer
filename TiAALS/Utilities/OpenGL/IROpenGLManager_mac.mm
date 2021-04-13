//
//  glTest_mac.cpp
//  IRiMaS
//
//  Created by Keitaro on 31/10/2019.
//

//#import <AppKit/NSOpenGL.h>
#import <AppKit/AppKit.h>

#include "IROpenGLManager.cpp"

void IROpenGLManager::setOpenGLContextAlpha(GLint aValue)
{
    NSOpenGLContext* context = (NSOpenGLContext*)this->context->getRawContext();
    
    if(context != nullptr)
        [context setValues:&aValue forParameter:NSOpenGLCPSurfaceOpacity];
    else
        std::cout << "Error : IROpenGLManager::setOpenGLContextAlpha() : could not get NSOpenGLContext : " << this->name << " nullptr\n";
    
}

void IROpenGLManager::bringOpenGLContextFront(juce::Component* owner)
{
    
    NSOpenGLContext* context = (NSOpenGLContext*)this->context->getRawContext();
    if(context == nullptr)
    {
        std::cout << "Error : IROpenGLManager::bringOpenGLContextFront() : could not get NSOpenGLContext : " << this->name << " nullptr\n";
        return;
    }
    
        
    
    auto* peer = owner->getPeer();
    if(peer != nullptr)
    {
        
        auto peerView = (NSView*) peer->getNativeHandle();
        [context.view retain];
        [context.view removeFromSuperview];
        [peerView addSubview: context.view];
        [context.view release];
        
    }
    
    [context.view setHidden: ! owner->isShowing()];
}
