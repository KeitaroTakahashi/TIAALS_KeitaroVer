
/*
 check belows forum where discussing how to implement different colours for each text fragments.
 https://forum.juce.com/t/need-to-change-text-in-order-for-text-editor-to-change-text-color/18931/2
 
 */

#ifndef IRTextEditorObject_h
#define IRTextEditorObject_h

#include "IRNodeObject.hpp"
#include "IRTextEditorController.hpp"

class IRTextEditorObject : public IRNodeObject
{
public:
    
    enum MODE
    {
        NODEOBJECT,
        ANNOTATION
    };
    
    IRTextEditorObject(Component* parent, IRStr* str, IRBoundType boundType = IRBoundType::ABSOLUTE);
    ~IRTextEditorObject();
    // ------------------------------------------------------------

    IRNodeObject* copyThisObject() override;
    
    t_json saveThisToSaveData() override;
    void loadThisFromSaveData(t_json data) override;
    
    void copyData(IRTextEditorObject* data);
    // ------------------------------------------------------------

    virtual void paint(Graphics &g) override;
    virtual void onResized() override;

    
    // ------------------------------------------------------------

    void mouseDownEvent(const MouseEvent& e) override;
    // ------------------------------------------------------------

    void IRChangeListenerCallback(ChangeBroadcaster* source) override;
    // from IRNodeObject
    void arrangeControllerChangedNotify() override;

    // ------------------------------------------------------------

    void setFont(Font font);
    void setTypeFaceName(const String typefaceName);
    void setTypeFaceStyle(const String typefaceStyle);
    void setFontSize(int height);
    
    void setAlign(int id);
    void setTextColour(Colour colour);
    void setTextColour(Colour colour, float alpha);
    void setTextColour(uint8 red, uint8 green, uint8 blue, float alpha);
    
    void setTextContents(String content);

    void applyColourToAllText(Colour colour);
    void applyColourToAllText(Colour colour, float alpha);
    void applyColourToAllText(uint8 red, uint8 green, uint8 blue, float alpha);

    void setBackgroundColour(Colour colour);
    void setBackgroundColour(Colour colour, float alpha);
    void setBackgroundColour(uint8 red, uint8 green, uint8 blue, float alpha);
    // ------------------------------------------------------------

    Font getFont() const;
    Colour getTextColour() const;
    Colour getBackgroundColour() const;
    int getAlignId() const;
    
    void showTextContents();
    
    int getTextWidth() const;
    int getTextHeight() const;
    
    int getCaretPosition(); // in index
    void setCaretPosition(int newIndex);
    // ------------------------------------------------------------

    //void onReturnKeyAction();
    //void onTextChangeAction();
    
    std::function<void()> onReturnKey;
    std::function<void()> onTextChange;
    // ------------------------------------------------------------

    TextEditor textEditor;
    // ------------------------------------------------------------

    // preference
    std::unique_ptr<IRTextEditorController> controller;
    
    // ------------------------------------------------------------

    void statusInEditMode();
    void statusInControlMode();
    
    // ------------------------------------------------------------
    
    void applyFontFromController();
protected:
    
    void selectedChangedAction(bool flag) override;
    // ------------------------------------------------------------
    // call back function automatically called when the status of this object changed by others.
    // write some tasks here
    void statusChangedCallback(IRNodeComponentStatus status) override;
    void fontControllerChangedCallback(FontController* source);
    // ------------------------------------------------------------
    void textArrangeChanged();
    
    // ------------------------------------------------------------

    
    Font font;
    Colour textColour;
    Colour backgroundColour;
    int alignId;
    
    int originalFontSize = 14;
    
    // ------------------------------------------------------------
    // Arrange
    void encloseStatusChangedListener();
    // ------------------------------------------------------------
    void zoomRatioChanged(float ratio) override;
    // ------------------------------------------------------------
    // ------------------------------------------------------------

    
};




#endif /* IRTextEditorObject_h */




