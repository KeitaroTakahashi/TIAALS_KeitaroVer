//
//  PropertyComponent.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 13/03/2019.
//

#ifndef PropertyComponent_hpp
#define PropertyComponent_hpp

#include "IRFileManager.hpp"


// propertyComponent for IRFileManager

class IRPropertyComponent : public PropertyComponent
{
public:
    IRPropertyComponent(const String &propertyName, juce::Point<int>Marge, Rectangle<int> objectBounds = Rectangle<int>(0,0,0,0), int preferredHeight = 25);
    ~IRPropertyComponent();
    
    void resized() override;
    void paint(Graphics& g) override;
    
    void refresh() override;
    
    // ==================================================
    
    void setMarge(int x, int y);
    
    void setObjectPosition(Rectangle<int> bounds);
    
    // ==================================================

private:
    
    Label title;
    
    int xMarge = 0;
    int yMarge = 0;
    
    Rectangle<int> objectBounds;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRPropertyComponent)
};


#endif /* PropertyComponent_hpp */
