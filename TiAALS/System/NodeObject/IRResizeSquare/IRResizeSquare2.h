//
//  IRResizeSquare2.h
//  IRiMaS
//
//  Created by Keitaro on 27/11/2019.
//

#ifndef IRResizeSquare2_h
#define IRResizeSquare2_h

#include "JuceHeader.h"

class IRResizeSquare2 : public Component
{
public:
    
    enum MovableDirection
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
        
        Top,
        Bottom,
        Left,
        Right,
        None
    };
    
    IRResizeSquare2(Component* resizedComponent, Component* componentBindedOn) :
    resizedComponent(resizedComponent),
    componentBindedOn(componentBindedOn)
    {
        addMouseListener(componentBindedOn, false);
        addMouseListener(resizedComponent, false);
        createItems();
    }
    
    ~IRResizeSquare2()
    {
        for(auto item : this->items)
        {
            delete item;
        }
        this->items.clear();
    }
    
    // ==================================================
    
    void resized() override
    {
        int x = 0;//getX();
        int y = 0;//getY();
        auto t = this->items[0];
        t->setBounds(x, y, s, s);
    
        t = this->items[1];
        t->setBounds(x + getWidth()/2 - s/2, y, s, s);
        
        t = this->items[2];
        t->setBounds(x + getWidth() - s, y, s, s);
        
        t = this->items[3];
        t->setBounds(x + getWidth() - s, y + (getHeight()/2-s/2), s, s);
        
        t = this->items[4];
        t->setBounds(x + getWidth() - s, y + (getHeight() - s), s, s);
        
        t = this->items[5];
        t->setBounds(x + getWidth()/2 - s/2, y + (getHeight() - s), s, s);
        
        t = this->items[6];
        t->setBounds(x, y + (getHeight() - s), s, s);
        
        t = this->items[7];
        t->setBounds(x, y + (getHeight()/2 - s/2), s, s);
    }

    void paint(Graphics& g) override
    {
        g.fillAll(Colours::transparentBlack);
    }
   
    // ==================================================
    
    void setSquareColour(Colour colour)
    {
        this->squareColour = colour;
        for(auto item : this->items)
        {
            item->setSquareColour(this->squareColour);
        }
    }
    
    // ==================================================

    void createItems()
    {
        // top left
        this->items.push_back(new ResizingItem(Rectangle<int>(0, 0, s, s),
                                               TopLeft,
                                               this));
        
        this->items.push_back(new ResizingItem(Rectangle<int>(getWidth() / 2 - s/2, 0, s, s),
                                               Top,
                                               this));
        
        this->items.push_back(new ResizingItem(Rectangle<int>(getWidth()-s, 0, s, s),
                                               TopRight,
                                               this));
        
        this->items.push_back(new ResizingItem(Rectangle<int>(getWidth()-s, getHeight()/2 - s/2, s, s),
                                               Right,
                                               this));
        
        this->items.push_back(new ResizingItem(Rectangle<int>(getWidth()-s, getHeight()-s, s, s),
                                               BottomRight,
                                               this));
        
        this->items.push_back(new ResizingItem(Rectangle<int>(getWidth()/2-s/2, getHeight()-s, s, s),
                                               Bottom,
                                               this));
        
        this->items.push_back(new ResizingItem(Rectangle<int>(0, getHeight()-s, s, s),
                                               BottomLeft,
                                               this));
        
        this->items.push_back(new ResizingItem(Rectangle<int>(0, getHeight()/2-s/2, s, s),
                                               Left,
                                               this));
        
        for(auto item : this->items)
        {
            addAndMakeVisible(item);
        }
        
        showSquare(false);
         
    }
    
    // ==================================================

    void applyMouseListenerToIRNodeObject()
    {
        addMouseListener(componentBindedOn, false);
        addMouseListener(resizedComponent, false);
    }
    
    void applyMouseListenerToOtherObject(Component* comp)
    {
        removeMouseListener(resizedComponent);
        addMouseListener(comp, false);

    }
    
    // ==================================================

    void showSquare(bool flag)
    {
        if(!flag) toBack();
        
        for(auto item : this->items)
        {
            item->setVisible(flag);
        }
        
        this->isItemVisible = flag;
    }
    
    bool isVisible() const { return this->isItemVisible; }
    int getSquareSize() const { return this->s; }
    MovableDirection getDirection() const { return this->direction; }
    
    Component* getResizedComponent() { return this->resizedComponent; }
    
    Component* isComponentResizingItem(Component* component)
    {
        if(component == nullptr) return nullptr;
        
        auto p2 = dynamic_cast<ResizingItem*> (component);
        if(p2 != nullptr) return this->resizedComponent;
        else return nullptr;
    }

    // ==================================================

    class ResizingItem : public Component
    {
    public:
        ResizingItem(Rectangle<int> frameRect, MovableDirection direction, IRResizeSquare2* owner) :
        owner(owner),
        frameRect(frameRect),
        direction(direction),
        squareColour(Colours::black)
        {
            setSize(frameRect.getWidth(), frameRect.getHeight());
        }
        
        ~ResizingItem() {}
        // ==================================================

        void paint(Graphics& g) override
        {
            g.fillAll(Colours::transparentBlack);
            g.setColour(this->squareColour);
            g.drawRect(getLocalBounds(), 2.0);
        }
        
        void setSquareColour(Colour colour)
        {
            this->squareColour = colour;
        }
        
        // ==================================================

        void mouseDown(const MouseEvent& e) override
        {
            this->owner->itemClicked(this);
        }
        
        void mouseUp(const MouseEvent& e) override
        {
            this->owner->itemReleased(this);
        }
        
        void mouseDrag(const MouseEvent& e) override
        {
            this->owner->itemDragged(e);
        }
        // ==================================================

        int getPosX() const { return this->frameRect.getX(); }
        int getPosY() const { return this->frameRect.getY(); }
        
        MovableDirection getDirection() const { return this->direction; }
        
        Component* getNodeObject() { return this->owner->getResizedComponent(); }

    private:
        IRResizeSquare2* owner;
        Rectangle<int> frameRect;
        MovableDirection direction;
        
        Colour squareColour;

    };
    // ==================================================
public:
    std::function<void(MovableDirection)>   resizingSquareClicked;
    std::function<void(MovableDirection)>   resizingSquareReleased;
    std::function<void(MouseEvent)>  resizingSquareDragged;

    // ==================================================
private:
    void itemClicked(ResizingItem* item)
    {
        this->direction = item->getDirection();
        
        if(this->resizingSquareClicked != nullptr)
            this->resizingSquareClicked(this->direction);
        
        
        
        //callResizingSquareClicked(this->direction);
    }
    
    void itemReleased(ResizingItem* item)
    {
        this->direction = item->getDirection();
        
        if(this->resizingSquareReleased != nullptr)
            this->resizingSquareReleased(this->direction);
        //callResizingSquareReleased(this->direction);
    }
    
    void itemDragged(const MouseEvent& e)
    {
        if(this->resizingSquareDragged != nullptr)
            this->resizingSquareDragged(e);
        //callResizingSquareDragged(e);
    }
    // ==================================================

    // square size
    int s = 12;
    
    Colour squareColour;
    
    
    std::vector<ResizingItem* > items;
    bool isItemVisible = false;
    MovableDirection direction = None;
    
    Component* resizedComponent = nullptr;
    Component* componentBindedOn = nullptr;
};
#endif /* IRResizeSquare2_h */
