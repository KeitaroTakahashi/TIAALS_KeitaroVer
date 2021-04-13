//
//  IROpenGLRenderer.m
//  IRiMaS
//
//  Created by Keitaro on 17/11/2019.
//

#import <AppKit/AppKit.h>
#include "IRHeavyWeightComponent.cpp"

IRHeavyWeightComponent::IRHeavyWeightComponent(juce::Component* component, String name) :
component ( component ),
name(name)
{
    this->ctx.setRenderer(this);
    this->ctx.attachTo(*component);
    this->ctx.setContinuousRepainting(false);
        
}

IRHeavyWeightComponent::~IRHeavyWeightComponent()
{

    this->ctx.detach();
    std::cout << "OpenGL Context detached! : " << this->name << std::endl;
}

void IRHeavyWeightComponent::setComponentAlpha(GLint aValue)
{
    NSOpenGLContext* context = (NSOpenGLContext*)this->ctx.getRawContext();
    
    if(context != nullptr)
        [context setValues:&aValue forParameter:NSOpenGLCPSurfaceOpacity];
    else
        std::cout << "Error : IRHeavyWeightComponent::setOpenGLContextAlpha() : could not get NSOpenGLContext : nullptr in " << this->name << std::endl;
}

void IRHeavyWeightComponent::bringToFrontObj(juce::Component* owner)
{
    
    NSOpenGLContext* context = (NSOpenGLContext*)this->ctx.getRawContext();
    
    if(context == nullptr)
    {
        std::cout << "Error : IRHeavyWeightComponent::bringOpenGLContextFront() : could not get NSOpenGLContext : nullptr in " << this->name << std::endl;
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
    // re-setup component alpha
    setComponentAlpha(this->alpha);

    // reset repainting 
    this->ctx.setContinuousRepainting(false);

}

