//
//  IRNSViewManager_mac.m
//  IRiMaS
//
//  Created by Keitaro on 31/10/2019.
//

#import <AppKit/AppKit.h>
#include "IRNSViewManager.cpp"

void IRNSViewManager::bringOpenGLContextFront(juce::Component* owner, NSViewComponent* view)
{
    auto* peer = owner->getPeer();
    auto v = (NSView*) view->getView();
    

    if(v == nullptr) return;
    
    if(peer != nullptr)
    {
        auto peerView = (NSView*) peer->getNativeHandle();
       
        [v retain];
        [v removeFromSuperview];
        [peerView addSubview: v];
        [v release];
    }
   
    [v setHidden: ! owner->isShowing()];
    //[v acceptsFirstMouse: nullptr];

}
