//
//  AutomationVertex.hpp
//  InteractiveAutomation - App
//
//  Created by Keitaro on 01/05/2019.
//

#ifndef AutomationVertex_hpp
#define AutomationVertex_hpp

#include "JuceHeader.h"
#include "IRStrComponent.hpp"

namespace IRAutomation {
    
    enum uiCondition
    {
        uiOrdinary,
        uiSelected
    };
    
    
    enum movableStatus
    {
        NOTMOVABLE,
        HORIZONTALMOVABLE,
        VERTICALMOVABLE,
        CROSSMOVABLE
    };
    
    enum lineStatus
    {
        LINEAR,
        BEZIER
    };
    
    struct IRAutomationVertexPos
    {
        int original_i;
        float original_value;
        
        int current_i;
        float current_value;
        
        uiCondition condition = uiOrdinary;
        
        IRAutomationVertexPos()
        {
            this->original_i = 0; this->original_value = 0;
            this->current_i = 0; this->current_value = 0;

        }
        
       
        
        IRAutomationVertexPos(float original_i, float original_value,
                              float current_i,
                              float current_value,
                              uiCondition condition = uiOrdinary)
        {
            
            this->original_i = original_i;
            this->original_value = original_value;
            this->current_i = current_i;
            this->current_value = current_value;
            this->condition = condition;
        }
        
    };
    
    
    class IRAutomationVertexComponent : public Component,
    public IRStrComponent
    {
        
    public:
        // --------------------------------------------------
        
        IRAutomationVertexComponent(IRStr* str, Component* parent);
        ~IRAutomationVertexComponent();
        
        // --------------------------------------------------
        
        void paint(Graphics& g) override;
        
        void resized() override;
        // must be implemented in resized() method in the parent
        void parentResized();
        
        void mouseDownNodeEvent(const MouseEvent& e); // make another method to avoid spaghetti codes
        void mouseMoveNodeEvent(const MouseEvent& e); // make another method to avoid spaghetti codes
        void mouseDoubleClickNodeEvent(const MouseEvent& e); // make another method to avoid spaghetti codes
        void mouseUpNodeEvent(const MouseEvent& e); // make another method to avoid spaghetti codes
        void mouseDragNodeEvent(const MouseEvent& e); // make another method to avoid spaghetti codes
        void recoverEventStatus();
        
        void mouseDown(const MouseEvent& e) override; // JUCE oriented
        void mouseMove(const MouseEvent& e) override; // JUCE oriented
        void mouseUp(const MouseEvent& e)override; // JUCE oriented
        void mouseDoubleClick(const MouseEvent& e) override; // JUCE oriented
        void mouseDrag(const MouseEvent& e) override; // JUCE oriented
        
        // --------------------------------------------------

        bool hitTest(Rectangle<float> area) const;
        
        // --------------------------------------------------
        
        void setSelected(bool flag);
        bool isSelected();
        void setMouseDownPos(juce::Point<int> pos);
        juce::Point<int> getMouseDownPos() const;
        void moveThisComponentEvent(const MouseEvent& e);
        
        // --------------------------------------------------
        
        uiCondition getCondition() const { return this->condition; }
        
        // --------------------------------------------------
        // operator for sorting vertex
        bool operator < (const IRAutomationVertexComponent& rhs) const {
            return getX() < rhs.getX();
        }
        // utility
        void showRect()
        {
            std::cout << getX() << ", " << getY() << ", " << getWidth() << ", " << getHeight() << std::endl;
        }
        
        // --------------------------------------------------
        
        // change status
        // return a flag shows whether this Component is movable or not. Default is true.
        bool isMovable() const;
        bool isVerticalMovable() const;
        bool isHorizontalMovable() const;
        // all setter
        void setMovable(bool movable, bool verticalMovable, bool horizontalMovable);
        bool isMoving() const;
        bool isDragging() const;
        
        bool isPoint() const { return this->isPointFlag; }
        void setPoint(bool p) { this->isPointFlag = p; }
        // --------------------------------------------------
        
        
        void setPosition(juce::Point<float>pos);
        void setPosition(juce::Point<int>pos);

        juce::Point<float> getPosition();
        
        void setPositionEx(juce::Point<float>pos);
        
        void setBezierRatio(float ratio) { this->bezierRatio = ratio; }
        float getBezierRatio() const { return this->bezierRatio; }
        // --------------------------------------------------
        
        void calcBezier(IRAutomationVertexComponent* previous);
        void setBezier(IRAutomationVertexComponent* a, IRAutomationVertexComponent* b)
        {
            this->bezier1 = a;
            this->bezier2 = b;
        }
    
    private:
        
        juce::Point<float> position;
        
        ComponentBoundsConstrainer constrainer;
        ComponentDragger dragger;
        bool draggingFlag = false;
        
        // --------------------------------------------------
        
        bool movingFlag = false;
        bool isMovableFlag = true;
        bool isVerticalMovableFlag = true;
        bool isHorizontalMovableFlag = true;
        
        bool isPointFlag = true;

        // --------------------------------------------------

        uiCondition condition = uiOrdinary;
        juce::Point<int> mouseDownPos = {0, 0};
        int selectedSize = 10;
        int ordinarySize = 5;
        
        // --------------------------------------------------
        
        IRAutomationVertexComponent* bezier1 = nullptr;
        IRAutomationVertexComponent* bezier2 = nullptr;
        // in case this object is used for bezier points.
        float bezierRatio = 0.5;
        // --------------------------------------------------

    };
}
#endif /* AutomationVertex_hpp */
