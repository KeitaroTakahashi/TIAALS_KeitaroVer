//
//  IRShapePreferenceUI.hpp
//  IRiMaS
//
//  Created by Keitaro on 26/07/2019.
//

#ifndef IRShapePreferenceUI_hpp
#define IRShapePreferenceUI_hpp

#include "JuceHeader.h"
#include "IRStrComponent.hpp"
class IRShapePreferenceUI : public Component,
public IRStrComponent,
public ChangeBroadcaster,
public ChangeListener,
private ComboBox::Listener
{
    
public:
    
    enum IRShapePreferenceUIStatus
    {
        ColourChanged,
        FillMenuSelected,
        LineWidthChanged,
        ShapeMenuSelected,
        BorderWidthChanged
    };
    
    IRShapePreferenceUI(IRStr* str);
    
    ~IRShapePreferenceUI();
    // ==================================================
    
    void resized() override;
    void paint(Graphics& g) override;
    
    // ==================================================
    
    void setColour(Colour colour) { this->shapeColour.setCurrentColour(colour); }
    Colour getColour() const { return this->shapeColour.getCurrentColour(); }
    void setLineWidth(float width) { this->lineWidth = width; }
    float getLineWidth() const { return this->lineWidth; }
    void setFillShape(bool flag);
    bool isFillShape() const { return this->isFill; }
    int getSelectedShapeIndex() const { return this->shapeMenu.getSelectedId(); }
    
    void setShape(int index);

    
    int getFillMenuIndex() const { return this->fillMenu.getSelectedId(); }
    void lineWidthChanged();
    
    IRShapePreferenceUIStatus getStatus() const { return this->status; }
    
private:
    
    // ==================================================
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
    void changeListenerCallback(ChangeBroadcaster* source) override;

    
    // ==================================================

    IRShapePreferenceUIStatus status;
    
    
    Label LabelTitle; 
    Label shapeMenuLabel;
    ComboBox shapeMenu;
    
    Label fillLabel;
    ComboBox fillMenu;
    bool isFill = false;
    
    Label lineWidthLabel;
    Label lineWidthInput;
    float lineWidth = 4;
    
    Label shapeColourLabel;
    void shapeColourChanged();
    ColourSelector shapeColour
    {
        ColourSelector::showSliders
        | ColourSelector::showColourspace
        | ColourSelector::showAlphaChannel
    };
    // ==================================================

    
    IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();
    // ==================================================

};

#endif /* IRShapePreferenceUI_hpp */
