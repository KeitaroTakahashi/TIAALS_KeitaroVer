//
//  IRImageButton.hpp
//  InteractiveAutomation - App
//
//  Created by Keitaro on 02/05/2019.
//

#ifndef IRImageButton_hpp
#define IRImageButton_hpp

#include "JuceHeader.h"

class IRImageButton : public Component
{
public:
    IRImageButton(String name = "");
    ~IRImageButton();
    
    void paint(Graphics& g) override;
    void resized() override;
    
    void setImage(Image img);
    
    virtual void mouseDown(const MouseEvent& e) override;
    virtual void mouseUp(const MouseEvent& e) override;
    
    std::function<void()> onClick = nullptr;
protected:
    virtual void clicked() {}

public:
    void setDrawCircle(bool flag) { this->drawCircle = flag; }
    void setDrawRoundedSquare(bool flag) { this->drawRoundedSquare = flag; }
    void setDrawColour(Colour colour) { this->drawColour = colour; }
    
    // --------------------------------------------------

    float getAspectRatio() const { return this->w_h_ratio; }
    
    // --------------------------------------------------

    bool isSelected() const { return this->isSelectedFlag; }
    void setSelected(bool flag) { this->isSelectedFlag = flag; }
    
    // --------------------------------------------------
    // VISUAL
    void mouseDownVisual() { this->mouseDownFlag = true; repaint(); }
    void mouseUpVisual() { this->mouseDownFlag = false; repaint(); }
    // --------------------------------------------------


private:
    String name;
    bool isSelectedFlag = false;
    
    
    float w_h_ratio = 1.0;
    Colour drawColour;
    
    Image buttonImage;
    
    bool drawCircle = true;
    bool drawRoundedSquare = false;
    
    bool mouseDownFlag = false;

};
#endif /* IRImageButton_hpp */
