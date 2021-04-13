
#include "IRMultiPurposeObject.hpp"


IRMultiPurposeObject::IRMultiPurposeObject(Component* parent, IRStr* str, IRBoundType boundType)
: IRNodeObject(parent, "IRMultiPurposeObject", str, boundType)
{
    setObjectSize(100, 20);
}


IRMultiPurposeObject::~IRMultiPurposeObject()
{
    
}


IRNodeObject* IRMultiPurposeObject::copyContents(IRNodeObject *object)
{
    IRMultiPurposeObject* obj = new IRMultiPurposeObject(this->parent, getStr());
    obj->setBoundsInRatio(this->xRatio, this->yRatio, this->wRatio, this->hRatio);
    obj->setSelected(this->isSelected());
    obj->setBoundsRatio(this->isBoundsRatio());
    
    return obj;
}


void IRMultiPurposeObject::onResized()
{
    if (isBoundsRatio()) renewBounds();
}


void IRMultiPurposeObject::paint(Graphics& g)
{
    if (isSelected()) g.setColour(getStr()->SYSTEMCOLOUR.contents);
    else g.setColour(Colours::lightgrey);
    g.setOpacity(0.3);
    g.fillAll();
    
}


void IRMultiPurposeObject::setBoundsInRatio(float x, float y, float w, float h)
{
    this->xRatio = x;
    this->yRatio = y;
    this->wRatio = w;
    this->hRatio = h;
}


Rectangle<float> IRMultiPurposeObject::getBoundsInRatio() const
{
    return Rectangle<float> (this->xRatio, this->yRatio, this->wRatio, this->hRatio);
}


void IRMultiPurposeObject::renewBounds()
{
    setBoundsRelative(this->xRatio,
                      this->yRatio,
                      this->wRatio,
                      this->hRatio);
}


bool IRMultiPurposeObject::isBoundsRatio() const
{
    return this->boundsRatioFlag;
}


void IRMultiPurposeObject::setBoundsRatio(bool flag)
{
    this->boundsRatioFlag = flag;
}


void IRMultiPurposeObject::mouseDownEvent(const MouseEvent& e)
{
    
}


void IRMultiPurposeObject::mouseUpEvent(const MouseEvent& e)
{
    
}


// call back function automatically called when the status of this object changed by others.
// write some tasks here
//# MultiPurpose Object needs the opposite mouseListener structure to the IRNodeComponent
// # because MultiPurpose Object is added to the IRNodeObject.
void IRMultiPurposeObject::statusChangedWrapper(IRNodeComponentStatus status)
{
    switch (status)
    {
        case EditModeStatus:
            setMovable(false, false, false);
            
            //  ---- here we do not deselect objects ---- setSelected(false);
            
            if(isEditMode())
            {
                if(isMouseListenerFlag())
                {
                    removeMouseListener(this->parent);
                    setMouseListenerFlag(false);
                }
                for(auto comp : getChildren())
                {
                    comp->setInterceptsMouseClicks(true, true);
                }
                
                
            }else{
                if(! isMouseListenerFlag())
                {
                    addMouseListener(this->parent, true);
                    setMouseListenerFlag(true);
                }
                for(auto comp : getChildren())
                {
                    comp->setInterceptsMouseClicks(false, false);
                }
                
                
            }
            break;
        case SelectableStatus:
            break;
        default:
            break;
    }
}




