//
//  IRComponentBase.hpp
//  TiAALS - App
//
//  Created by Keitaro on 24/01/2021.
//

/*
 
    Handling basic status of the object such as xy-position, size etc.
 
 
 
 */

#ifndef IRComponentBase_hpp
#define IRComponentBase_hpp

#include "JuceHeader.h"
#include "IRStrComponent.hpp"

enum IRBoundType
{
    // absolute position in pixel based on the TOP LEFT
    ABSOLUTE,
    // relative to the width and height in percent
    RELATIVE
};

class IRObjectBase : public Component
{
public:
    IRObjectBase(Component *parent,
                 String name,
                 IRStr* str,
                 IRBoundType boundType);
    ~IRObjectBase();
    
    // ==================================================
    
    void setBoundType(IRBoundType type);
    IRBoundType getBoundType() const { return this->bType; }
    
    // min max setter
    void setMinimumSize(const float minWidth, const float minHeight);
    void setMaximumSize(const float maxWidth, const float maxHeight);
    void setMinimumWidth(const float newMin);
    void setMinimumHeight(const float newMin);
    void setMaximumWidth(const float newMax);
    void setMaximumHeight(const float newMax);
    
    // ==================================================
    // ABSOLUTE ----------
    void setObjectSize(int w, int h,
                       NotificationType n = dontSendNotification);
    void setObjectCentredPosition(int x, int y,
                                  NotificationType n = dontSendNotification);
    void setObjectBounds(Rectangle<int> bounds,
                         NotificationType n = dontSendNotification);
    void setObjectBounds(int x, int y, int w, int h,
                         NotificationType n = dontSendNotification);
    void setObjectTopLeftPosition(int x, int y,
                                  NotificationType n = dontSendNotification);
    void setObjectTopLeftPositionRelative(float x, float y);
    
    //RELATIVE ----------
    void setObjectBoundsRelative(Rectangle<float> ratioBounds);
    void setObjectBoundsRelative(float x, float y, float w, float h);
    Rectangle<float> getObjectBoundsRelative() const { return this->relativeBoundsToParent; }
    
    void setInitialBounds(Rectangle<float> initialBounds);
    Rectangle<float> getInitialBounds() const { return this->initialBounds; }
    
    
    // adjust object bounds to the width ratio
    // this methods does not update the initialBounds
    // Currently, only hZoom affects the result
    void zoomObjectByRatio(float ratio, bool wZoom, bool hZoom, bool isCallback = true);
    void setObjectBoundsByRatioChange(Rectangle<int>bounds);
    
    void setZoomRatio(float ratio, bool callback = true) { this->zoomRatio = ratio; if(callback) zoomRatioChanged(ratio); }
    float getZoomRatio() const { return this->zoomRatio; }
    
    void setZoomable(bool width, bool height);
    
    bool isWidthZoomable() const { return this->widthZoomable; }
    bool isHeightZoomable() const { return this->heightZoomable; }
    // ==================================================
    // use this method to paint something on this object
    virtual void paintOnThis(Graphics& g) {}
    // ==================================================
    
    bool isMovable() const;
    bool isVerticalMovable() const;
    bool isHorizontalMovable() const;
    // all setter
    void setMovable(bool movable, bool verticalMovable, bool horizontalMovable);
    bool isMoving() const;
    bool isDragging() const;

protected:
    virtual void onResized() {};
    virtual void onMoved() {};
    
    virtual void resizedOrMoved() {}; 
    virtual void ObjectPositionChanged(int x, int y) {}
    virtual void ObjectBoundsChanged(Rectangle<int> bounds) {}
    
    virtual void aboutToMoveAction() = 0;
    
    virtual void zoomRatioChanged(float ratio) {}

public:
    std::function<void()> onResizedCallback = nullptr;
    std::function<void()> abountToResizeCallback = nullptr;

    std::function<void()> onMovedCallback = nullptr;
    std::function<void()> aboutToMoveCallback = nullptr;

    // ==================================================
private:
    
    void paint(Graphics& g) override;

    void resized() override;
    void moved() override;
    
    // Bound type defines the way of coordinating Components on the parent space:
    IRBoundType bType = RELATIVE;
    
    Rectangle<float> initialBounds;
    Rectangle<float> relativeBoundsToParent;
    
    // Object appearance setup
    float minWidth = 10;
    float minHeight = 10;
    float maxWidth = 3000;
    float maxHeight = 3000;

    bool isMovableFlag = true;
    bool isVerticalMovableFlag = true;
    bool isHorizontalMovableFlag = true;
    bool movingFlag = false;
    
    bool draggingFlag = false;
    
    void aboutToResized();
    void hasResized();
    void aboutToMoved();
    void hasMoved();
    
    void boundChangeTask(Rectangle<int> bounds, NotificationType n = dontSendNotification);
    
    // =======================================================
    // rorate

    public:
        void setRotateAngle(float rotate);
        float getRotateAngle() const { return this->rotateAngle; }
    
    virtual void objectRotated(float rotate) {}
    private:
        float rotateAngle = 0.0;
        void doRotate(bool clockwise, float angle);
    void resetRotate();
    // ==================================================
    
    // ==================================================
    // ###### JUCE FUNCTIONS #####
    // ==================================================

    private:
        // disable JUCE size coordinate functions
    //use setObjectBounds
        void setSize(float width, float height);
    
    // use setObjectBounds
        void setBounds(Rectangle<int> bounds);
        void setBounds(int x, int y, int w, int h);
    // use setObjectCentredPosition
        void setCentredPosition(int x, int y);
        void setTopLeftPosition(int x, int y);
    
    // h / w
    float originalAspect = 1.0;
    
    float zoomRatio = 1.0;
    bool widthZoomable = true;
    bool heightZoomable = true;
    // ==================================================
    
    Rectangle<float> divRectangle(Rectangle<float> bounds, float ratio);

public:

    // ==================================================
    
    Component* parent = nullptr;
    String name;
    // ==================================================
    
    float angle = 0;

};

#endif /* IRComponentBase_hpp */
