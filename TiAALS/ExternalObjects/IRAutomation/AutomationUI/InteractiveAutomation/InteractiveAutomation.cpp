//
//  InteractiveAutomation.cpp
//  InteractiveAutomation - App
//
//  Created by Keitaro on 29/04/2019.
//

#include "InteractiveAutomation.hpp"

InteractiveAutomation::InteractiveAutomation(IRNodeObject* nodeObject, IRStr* str) :
IRUIFoundation(nodeObject, str)
{
        
    this->verteces.clear();
    this->selector = std::make_shared<VertecesSelector>(&this->verteces, this);
    this->selector->setShiftConstrainsDirection(true);
    this->selector->setConstrainBoundsToParent(true, {0,0,10,10});
    this->selector->setMovableDirection(true, false);
    
    this->controller = std::make_shared<AutomationController>(str);
    this->controller->setZoomInEvent([this]{ zoomInClicked(); });
    this->controller->setZoomOutEvent([this]{ zoomOutClicked(); });
    this->controller->setMovableEvent([this](IRAutomation::movableStatus status){ movableClicked(status); });
    this->controller->setCommentEvent([this]{ commentClicked(); });
    this->controller->setBezierEvent([this](IRAutomation::lineStatus status){ bezierClicked(status); });

    setWantsKeyboardFocus(true);
    //addKeyListener(this);
    
    //addAndMakeVisible(&this->mouseGrid);

    
}

InteractiveAutomation::~InteractiveAutomation()
{
    
    deleteAllVerteces();
    
}
// ==================================================

void InteractiveAutomation::initAutomation()
{
    deleteAllVerteces();
    this->MinVertexValue = 99999999;
    this->MaxVertexValue = -99999999;
    
    for(auto item : this->vertexBuffer) delete item;
    this->vertexBuffer.clear();
}

void InteractiveAutomation::paint(Graphics& g)
{
    if(this->isCalcPosFlag) reCalcPos();
    //std::cout << "+++++ InteractiveAutomation repaint() +++++ \n";

    g.fillAll(Colours::white);
    g.setColour(getStr()->SYSTEMCOLOUR.fundamental);
    g.drawRect(0, 0, getWidth(), getHeight(), 1);
    
  
    if(isBezierShow()) paintBezierLines(g);
    else drawLinesBetweenVerteces(g);
    //drawVerteces(g);
    
    if(isCommentShow()) paintComment(g);
  
    
    g.setColour(Colours::red);
    g.drawLine(this->playingLine.getX(),
               this->playingLine.getY(),
               this->playingLine.getWidth(),
               this->playingLine.getHeight(),
               3.0);
    
}

void InteractiveAutomation::paintComment(Graphics& g)
{
    g.setColour(getStr()->SYSTEMCOLOUR.contents);
    g.setOpacity(0.8);
    g.drawLine(0, this->currentMousePos.getY(), getWidth(), this->currentMousePos.getY(), 2);
    g.drawLine(this->currentMousePos.getX(), 0, this->currentMousePos.getX(), getHeight(), 2);
    
    // draw rect
    int rectX, rectY;
    if(this->currentMousePos.getX() > (this->visibleArea.getX() + this->visibleArea.getWidth()/2))
        rectX = this->currentMousePos.getX() - 50;
    else rectX = this->currentMousePos.getX();
    if(this->currentMousePos.getY() > (this->visibleArea.getY() + this->visibleArea.getHeight()/2))
        rectY = this->currentMousePos.getY() - 25;
    else rectY = this->currentMousePos.getY();
    
    g.fillRect(Rectangle<int>(rectX, rectY, 50, 25));
    
    Font f("Avenir Next",20, Font::plain);
    g.setColour(getStr()->SYSTEMCOLOUR.text);
    g.setFont(f);
    g.drawText("test", rectX, rectY, 50, 25, Justification::right,true);
}

void InteractiveAutomation::drawVerteces(Graphics& g)
{
    for(auto ver : this->verteces)
    {
        if(ver->getCondition() == uiSelected) g.setColour(Colours::red);
        else g.setColour(Colours::orange);
        
        //g.fillEllipse(ver->getCentreX(), ver->getCentreY(), ver->getWidth(), ver->getHeight());
    }
}

void InteractiveAutomation::drawLinesBetweenVerteces(Graphics& g)
{
    g.setColour(Colours::grey);
    
    Rectangle<int> v = this->visibleArea;
    
    for(int i=1;i<this->verteces.size();i++)
    {
        int wh = this->verteces[i-1]->getWidth()/2;
        int wh2 = this->verteces[i]->getWidth()/2;
        
        g.drawLine(this->verteces[i-1]->getX() + wh,
                   this->verteces[i-1]->getY() + wh,
                   this->verteces[i]->getX() + wh2,
                   this->verteces[i]->getY() + wh2,
                   2);
    }
    
    /*
    for(int i = 1; i < this->vertexBuffer.size(); i++)
    {
        float p_x = this->vertexBuffer[i-1]->pos.getX();
        float x   = this->vertexBuffer[i]->pos.getX();
        
        // draw lines only in the visible area
        if(p_x >= v.getX() &&
           x <= v.getX() + v.getWidth())
        {
        
            g.drawLine(this->vertexBuffer[i-1]->pos.getX(),
                       this->vertexBuffer[i-1]->pos.getY(),
                       this->vertexBuffer[i]->pos.getX(),
                       this->vertexBuffer[i]->pos.getY(),
                       2);
        }
        
     
    }
     */
    
    /*
     int wh = this->verteces[i-1]->getWidth()/2;
     int wh2 = this->verteces[i]->getWidth()/2;
     
     g.drawLine(this->verteces[i-1]->getX() + wh,
     this->verteces[i-1]->getY() + wh,
     this->verteces[i]->getX() + wh2,
     this->verteces[i]->getY() + wh2,
     2);
     */
}

void InteractiveAutomation::paintBezierLines(Graphics& g)
{
    g.setColour(Colours::grey);

    for(int i = 1; i < this->verteces.size(); i++)
    {
        /*
        Path path;
        //i
        float x = this->vertexBuffer[i]->pos.getX();
        float y = this->vertexBuffer[i]->pos.getY();

        // i-1
        float p_x = this->vertexBuffer[i-1]->pos.getX();
        float p_y = this->vertexBuffer[i-1]->pos.getY();

        path.startNewSubPath(p_x, p_y);
        
        float cx = p_x + (x - p_x) * 0.5;
        
        juce::Point<float> c1 (cx, p_y);
        juce::Point<float> c2 (cx, y);
        juce::Point<float> d (x, y);
         */
        
        /*
        int wh = this->vertex[i-1]->getWidth()/2;
        int wh2 = this->verteces[i]->getWidth()/2;
        
        path.startNewSubPath(this->verteces[i-1]->getX() + wh,
                             this->verteces[i-1]->getY() + wh);
        
        float cx = this->verteces[i-1]->getX() +
        (this->verteces[i]->getX() - this->verteces[i-1]->getX()) * this->verteces[i-1]->getBezierRatio();
        
        juce::Point<float> c1 (cx, this->verteces[i-1]->getY());
        juce::Point<float> c2 (cx, this->verteces[i]->getY());
        juce::Point<float> d (this->verteces[i]->getX() + wh2,
                        this->verteces[i]->getY() + wh2);
        */
        
        /*
        path.cubicTo(c1, c2, d);
        
        g.strokePath(path, PathStrokeType(2));
         
         */
    }
}

// ==================================================

void InteractiveAutomation::resized()
{

    if(getHeight() < 50) setBounds(getX(), getY(), getWidth(), 50);
    
    int s = getHeight();
    if(s > 50) s = 50;
    int y = getHeight() / 2 - s / 2;
    
    this->controller->setBounds(this->visibleArea.getX(), y, getWidth(), s);

    this->mouseGrid.setBounds(getLocalBounds());
    
    doReCalcPos();
    repaint();

}

void InteractiveAutomation::setVisibleArea(Rectangle<int> area) {
    int s = getHeight();
    if(s > 50) s = 50;
    int y = getHeight() / 2 - s / 2;
    this->visibleArea = area;
    this->controller->setBounds(this->visibleArea.getX(), y, getWidth(), s);
    
    this->previousOffsetX = this->visibleArea.getX();
    
    doReCalcPos();
}


void InteractiveAutomation::reCalcPos()
{
    std::cout << "reCalcPos\n";
    
    deleteAllVerteces();
    
    float boundsRatio_h;
    float boundsRatio_w;
    
    int v_size = (int)this->vertexBuffer.size(); //this->verteces.size();
    int w = getWidth();
    int h = getHeight();
    
    int visible_w = this->visibleArea.getWidth();
    int visible_h = this->visibleArea.getHeight();
    int visible_x = this->visibleArea.getX();
    int visible_y = this->visibleArea.getY();
    
    // if there is no verteces, then add two verteces with 0 values.
    if(v_size == 0)
    {
        createVertex(juce::Point<float>(0, h), false);
        createVertex(juce::Point<float>(w, h), false);
        reCalcPosDone();

        return;
    }
    int pw = this->previousBounds.getWidth();
    int ph = this->previousBounds.getHeight();
    
    if(ph > 0.0 && h > 0.0) boundsRatio_h = (float)h / (float)ph;
    else boundsRatio_h = 1.0;
    
    if(pw > 0.0 && w > 0.0) boundsRatio_w = (float)w / (float)pw;
    else boundsRatio_w = 1.0;
    
    // ------------------------------------------------------------
    // how many values in each pixel.
    // 1.0 means 1 data for each piexel, increment > 1.0 = more data in each pixel, so calculate average of them.
    float increment = (float)v_size / (float)w;
    float startIndex = (float)visible_x * increment;
    if(startIndex > 0) startIndex -= 1;
    float endIndex = (float)(visible_x + visible_w) * increment;
    if(endIndex < v_size) endIndex += 1;
    
    // draw point on each Vertex if increment is larger than 1 pixel.
    bool isPoint = true;
    if(increment < 1.0) isPoint = false;
    
    float currentIndex = startIndex;
    int previousIndex = -1;
    float accumVal = 0.0;
    int interval = 0;
    float max = -999999.9;
    float min = 999999.9;
    int i, j;

    for(i=0;i<visible_w;i++)
    {
        if(currentIndex >= v_size) break;
        
        int ci = floor(currentIndex);
        interval =  ci - previousIndex;

        if(interval > 0)
        {
            accumVal = 0;
            max = -999999.9;
            min = 999999.9;
            // make average
            for(j=0;j<interval;j++)
            {
                if(max < this->vertexBuffer[previousIndex + j + 1]->current_value)
                    max = this->vertexBuffer[previousIndex + j + 1]->current_value;
                if(min > this->vertexBuffer[previousIndex + j + 1]->current_value)
                    min = this->vertexBuffer[previousIndex + j + 1]->current_value;
                
                accumVal += this->vertexBuffer[previousIndex + j + 1]->current_value;
                //std::cout << "vertexBuffer[" << previousIndex + j + 1 << "] = " << this->vertexBuffer[previousIndex + j + 1]->current_value << std::endl;
            }
            //accumVal /= interval;
            
            //accumVal = h - (accumVal * h);
            accumVal = h - (max * h);
            
            //std::cout << "vertex["<<visible_x + i << "] = " << max << " : min = " << min << " : accum = " << accumVal <<" by interval " << interval << std::endl;
            
            createVertex(juce::Point<float>(visible_x + i, accumVal), false, false);
            
            previousIndex = currentIndex;

        }
        currentIndex += increment;
    }
        
    
    // sort
    ascendingSorter sorter;
    this->verteces.sort(sorter);

    // update previous bounds
    this->previousBounds = getLocalBounds();

    reCalcPosDone();
    repaint();
    

}

void InteractiveAutomation::mouseDown(const MouseEvent& e)
{
    this->currentMousePos = e.getEventRelativeTo(this).getPosition();
    
    if(e.mods.isCtrlDown())
    {
        std::cout << "show controller\n";
        addAndMakeVisible(this->controller.get());
    }else {
        if(this->controller->isVisible())
            removeChildComponent(this->controller.get());
    }
    
    this->selector->mouseDownHandler(e);
    addAndMakeVisible(this->selector.get());
}

void InteractiveAutomation::mouseDoubleClick(const MouseEvent& e)
{
    this->currentMousePos = e.getEventRelativeTo(this).getPosition();
    
    Rectangle<float> area ( this->currentMousePos.getX(),
                           this->currentMousePos.getY(),
                           1,1);
    
  
    if(!isHitAnyVerteces(area)) createVertex(this->currentMousePos.toFloat(), true);
    
    
    repaint();
    
}

void InteractiveAutomation::mouseUp(const MouseEvent& e)
{
    this->selector->mouseUpHandler(e);
    removeChildComponent(this->selector.get());
    
    repaint();
        
}
void InteractiveAutomation::mouseMove(const MouseEvent& e)
{
    this->currentMousePos = e.getEventRelativeTo(this).getPosition();
    repaint();
   // this->mouseGrid.setMousePosition(this->currentMousePos);
    
}
void InteractiveAutomation::mouseDrag(const MouseEvent& e)
{
    this->currentMousePos = e.getEventRelativeTo(this).getPosition();
    this->selector->mouseDragHandler(e);
    repaint();
}
// ==================================================

void InteractiveAutomation::createVertex(juce::Point<float> pos, bool isSelected, bool shouldSort)
{
    IRAutomationVertexComponent* obj = new IRAutomationVertexComponent (getStr(), this);
    obj->setPosition(pos);
    obj->setSelected(isSelected);
    obj->addMouseListener(this, true);
    addAndMakeVisible(obj);
    this->verteces.add( obj );

    // sort
    if(shouldSort)
    {
        ascendingSorter sorter;
        this->verteces.sort(sorter);
    }
    
    int index = this->verteces.indexOf(obj);
    // bezier
 
    if(index > 0)
    {
        IRAutomationVertexComponent* current = this->verteces[index];
        IRAutomationVertexComponent* previous = this->verteces[index - 1];
        
        //deallocate by IRAutomationVertecComponent
        std::shared_ptr<IRAutomationVertexComponent> b1 = std::make_shared<IRAutomationVertexComponent>(getStr(), this);
        std::shared_ptr<IRAutomationVertexComponent> b2 = std::make_shared<IRAutomationVertexComponent>(getStr(), this);

        int x_b1 = previous->getPosition().getX() +
                   (current->getPosition().getX() -
                    previous->getPosition().getX())/2;
        int y_b1 = previous->getPosition().getY();
        
        juce::Point<float> p1 (x_b1, y_b1);
        b1->setPosition(p1);
        
        int y_b2 = current->getPosition().getY();
        
        juce::Point<float> p2 (x_b1, y_b2);
        b2->setPosition(p2);
        
        current->setBezier(b1.get(), b2.get());
        
    }
 
}


void InteractiveAutomation::selectAllVerteces()
{
    for(auto v : this->selectedVerteces)
    {
        v->setSelected(true);
    }
    this->selectedVerteces.clear();
}

void InteractiveAutomation::deselectAllVerteces()
{
    for(auto v : this->selectedVerteces)
    {
        v->setSelected(false);
    }
    this->selectedVerteces.clear();
    
    doReCalcPos();
    repaint();
}

void InteractiveAutomation::deleteSelectedVerteces()
{
    int i = (int) this->verteces.size() - 1;
    
    while (i >= 0)
    {
        if(this->verteces[i]->isSelected())
        {
            removeChildComponent(this->verteces[i]);
            this->verteces.remove(i);
        }
        
        i --;
    }
    
    doReCalcPos();

    repaint();
}

void InteractiveAutomation::deleteAllVerteces()
{
    for(auto vertex : this->verteces)
    {
        removeChildComponent(vertex);
    }
    this->verteces.clear();
}

bool InteractiveAutomation::isHitAnyVerteces(Rectangle<float> area) const
{
    bool hitResult = false;
    
    for(auto v : this->verteces)
    {
        hitResult = v->hitTest(area);
        if(hitResult) return true;
    }
    
    return false;
}

void InteractiveAutomation::repaintAllverteces()
{
    for(auto v : this->verteces)
    {
        v->repaint();
    }
}

// ==================================================

void InteractiveAutomation::demoData(int num)
{
    
    float increment = (float) getWidth() / (float) num;
    initAutomation();
    
    //std::cout << "vertex num = " << num << std::endl;
    
    for(int i = 0; i < num ; i++)
    {
        float value = (rand() % (getHeight()));
        
        float x = (float)i * increment;
        //float value = (rand() % 1000) / 1000.0 * getHeight();

        //std::cout << i << " : value = " << value << std::endl;
        
        createVertex(juce::Point<float>(x, value), false);
        
        if(value < this->MinVertexValue) this->MinVertexValue = value;
        if(value > this->MaxVertexValue) this->MaxVertexValue = value;
    }
    
    deselectAllVerteces();
    //showVerteces();
    doReCalcPos();
    repaint();
}

void InteractiveAutomation::setDescriptor(IRDescriptorStr* data)
{
    
    std::cout << "setDescriptor \n";
    initAutomation();

    int num = data->getNumFrame();
    std::cout << "nframe = " << num << std::endl;
    float increment = (float) getWidth() / (float) num;

    //auto buffer = data.getNormalizedData()[0];
    auto buffer = data->getNormalizedData();
    
    float height = (float)getHeight();
    
    this->vertexBuffer.reserve(num);
    int i;
    for(i = 0; i < num ; i++)
    {
        float value = height - (buffer[i] * height);
        
        std::cout << i << " : " << buffer[i] << std::endl;
        //float value = (rand() % 1000) / 1000.0 * getHeight();

        //std::cout << "value = " << value << std::endl;
        
        this->vertexBuffer.emplace_back(new IRAutomationVertexPos (i,
                                                                   buffer[i],
                                                                   i,
                                                                   buffer[i])
                                        );

        //createVertex(juce::Point<float>((float)i * increment, value), false, false);
    
        if(value < this->MinVertexValue) this->MinVertexValue = value;
        if(value > this->MaxVertexValue) this->MaxVertexValue = value;
    }
    
    //std::cout << "setDescriptor done \n";

    //deselectAllVerteces();
    

    //showVerteces();
    doReCalcPos();
    std::cout << "reCalsPos done \n";
    repaint();
}

// ==================================================
/*
bool InteractiveAutomation::keyPressed(const KeyPress &key,
                                       Component* originatingComponent)
{
    int keyCode = key.getKeyCode();
    
    std::cout << "key code = " << keyCode << std::endl;
    if(keyCode == key.deleteKey || keyCode == key.backspaceKey)
    {
        deleteSelectedVerteces();
    }else if(key.getTextDescription() == "command + A")
    {
        for(auto v : this->verteces)
        {
            v->setSelected(true);
            v->repaint();
        }
    }
    
    return true;
}*/

void InteractiveAutomation::IRKeyPressed(int keyCode, String keyText)
{
    KeyPress key;

    std::cout << "key code = " << keyCode << std::endl;
    if(keyCode == key.deleteKey || keyCode == key.backspaceKey)
    {
        deleteSelectedVerteces();
    }else if(keyText == "command + A")
    {
        for(auto v : this->verteces)
        {
            v->setSelected(true);
            v->repaint();
        }
    }
    
}


void InteractiveAutomation::setMovable(bool movable, bool verticalMovable, bool horizontalMovable)
{
    this->selector->setMovableDirection(verticalMovable, horizontalMovable);
}

// ==================================================

void InteractiveAutomation::zoomInClicked()
{
    if(this->zoomInClickedCallback != nullptr) this->zoomInClickedCallback();
}
void InteractiveAutomation::zoomOutClicked()
{
    if(this->zoomOutClickedCallback != nullptr) this->zoomOutClickedCallback();
}
void InteractiveAutomation::movableClicked(IRAutomation::movableStatus status)
{
    if(this->movableClickedCallback != nullptr)
        this->movableClickedCallback(status);
}

void InteractiveAutomation::bezierClicked(IRAutomation::lineStatus status)
{
    
    switch (status)
    {
        case IRAutomation::lineStatus::LINEAR:
            setBezierShow(false);
            break;
        case IRAutomation::lineStatus::BEZIER:
            setBezierShow(true);
            break;
            
        default:
            break;
    }
}

void InteractiveAutomation::commentClicked()
{
    setCommentShow(!isCommentShow());
    
    std::cout << "comment show " << isCommentShow() << std::endl;
}

// ==================================================

