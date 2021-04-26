
#include "IRNodeComponent.hpp"

IRNodeComponent::IRNodeComponent(Component* parent,
                                 String name,
                                 IRStr* str,
                                 IRBoundType boundType) :
IRObjectBase(parent, name, str, boundType),
IRObjectResizer(this, parent, 20, 3000, 20, 3000),
IRStrComponent(str),
resizingArea(25, 25)
{
    StopWatch bench; bench.start();
    //default size
    setObjectSize(100, 100);
    this->name = name;
    this->mixer.reset( new MixerAudioSource() );
    
    this->parent = parent;
    
    /*
    this->menu.reset( new PopupMenu() );
    this->menu->addItem(999, name); // do nothing
    this->menu->addSeparator();
    this->menu->addItem(1, "Bring to Front");
    this->menu->addItem(2, "Send to Back");
    this->menu->addSeparator();
    this->menu->addItem(3, "Cut");
    this->menu->addItem(4, "Copy");
    this->menu->addItem(5, "Paste");
    this->menu->addItem(6, "Duplicate");
     */
    bench.result("x x x x x x x xx x : IRNodeComponent");
    
    
    //only resizingSquare and not squares at the corners
    bindObjectResizer();
    
}


IRNodeComponent::~IRNodeComponent()
{

    this->mixer.reset();
    
    //this->menu.reset();
  
    std::cout << "~IRNODECOMPONENT DESTRUCTOR CALLED" << std::endl;
    
}

void IRNodeComponent::setPreferenceWindow(PreferenceWindow* preferenceWindow)
{
    this->preferenceWindow = preferenceWindow;
}


PreferenceWindow* IRNodeComponent::getPreferenceWindow()
{
    return this->preferenceWindow;
}


void IRNodeComponent::updateFileManager(IRFileManager& fileManager)
{
    FILEMANAGER = &fileManager;
    //setIRFileManager(fileManager);
    if(this->fileManagerUpdated != nullptr) this->fileManagerUpdated(&fileManager);
}

// paint
void IRNodeComponent::paint(Graphics& g)
{
    g.fillAll(Colours::transparentBlack);

    auto area = getLocalBounds();//.reduced (0);

    if (isEditMode())
    {
        g.setColour (getStr()->SYSTEMCOLOUR.contents);
        g.drawRoundedRectangle (area.toFloat(), 5.0f, 2.0f);
    }
    
    //g.setColour (this->isSelected()? Colours::white : SYSTEMCOLOUR.titleText);
    //g.drawFittedText ("NodeObject", area, Justification::centred, 1);
    
}



// Child Component Management
void IRNodeComponent::childComponentManager(Component* comp)
{
    comp->addMouseListener(this, true);
    if (isEditMode())
    {
        comp->setInterceptsMouseClicks(false, false);
    }
    else
    {
        comp->setInterceptsMouseClicks(true, false);
    }
}


// Audio source
void IRNodeComponent::addAudioComponent(AudioSource *source)
{
    this->mixer->addInputSource(source, false);
    this->containAudioSourceFlag = true;
}


void IRNodeComponent::removeAudioComponent(AudioSource *source) // FD ADDON
{
    this->mixer->removeInputSource(source); // which will be deleted automatically
    this->containAudioSourceFlag = false;

}


MixerAudioSource* IRNodeComponent::getAudioSource() const
{
    return this->mixer.get();
}


// check if any AudioSources are added in this NodeObject.
bool IRNodeComponent::isContainAudioSource() const
{
    return this->containAudioSourceFlag;
}


// interaction
void IRNodeComponent::mouseDown(const MouseEvent& e)
{
    //std::cout << "IRNodeComponent mouseDown\n";
    mouseDownNodeEvent(e);
    mouseDownEvent(e);
}


void IRNodeComponent::mouseMove(const MouseEvent& e)
{
    //mouseUpNodeEvent(e);
    mouseMoveNodeEvent(e);
    mouseMoveEvent(e);
}


void IRNodeComponent::mouseUp(const MouseEvent& e)
{
    mouseUpNodeEvent(e);
    mouseUpEvent(e);
    mouseUpCompleted(e);
}

void IRNodeComponent::mouseDoubleClick(const MouseEvent& e)
{
    mouseDoubleClickNodeEvent(e);
    mouseDoubleClickEvent(e);
}


void IRNodeComponent::mouseDrag(const MouseEvent& e)
{
    mouseDragNodeEvent(e); // defines fundamental behavior
    mouseDragEvent(e); // defined by an unique Node object
}

void IRNodeComponent::mouseEnter(const MouseEvent& e)
{
    mouseEnterEvent(e);
}
void IRNodeComponent::mouseExit(const MouseEvent& e)
{
    mouseExitEvent(e);

}
void IRNodeComponent::mouseMagnify(const MouseEvent& e, float scaleFactor)
{
    mouseMagnifyEvent(e, scaleFactor);
}

// ------------------------------------------------------------

// resizing area
juce::Point<float> IRNodeComponent::getResizingArea() const
{
    return this->resizingArea;
}


void IRNodeComponent::setResizingArea(juce::Point<float> area)
{
    this->resizingArea = area;
}


// EVENTS FOR OVERRIDE
void IRNodeComponent::mouseDownEvent(const MouseEvent& e)
{
    
}


void IRNodeComponent::mouseMoveEvent(const MouseEvent& e)
{
    
}


void IRNodeComponent::mouseDoubleClickEvent(const MouseEvent& e)
{
    
}


void IRNodeComponent::mouseUpEvent(const MouseEvent& e)
{
    
}


void IRNodeComponent::mouseDragEvent(const MouseEvent& e)
{
    
}

void IRNodeComponent::mouseEnterEvent(const MouseEvent& e)
{
    
}
void IRNodeComponent::mouseExitEvent(const MouseEvent& e)
{
    
}

void IRNodeComponent::mouseMagnifyEvent(const MouseEvent& e, float scaleFactor)
{
    
}

// CALLBACK FUNCTIONS
void IRNodeComponent::statusChangedCallback(IRNodeComponentStatus status)
{
   
}

/*
// Change status

bool IRNodeComponent::isMovable() const
{
    return this->isMovableFlag;
}


bool IRNodeComponent::isVerticalMovable() const
{
    return this->isVerticalMovableFlag;
}


bool IRNodeComponent::isHorizontalMovable() const
{
    return this->isHorizontalMovableFlag;
}

void IRNodeComponent::setResizable(bool flag, bool isWidthResizableFlag, bool isHeightResizableFlag)
{
    this->isResizableFlag = flag;
    this->isWidthResizableFlag = isWidthResizableFlag;
    this->isHeightResizableFlag = isHeightResizableFlag;
}


// all setter
void IRNodeComponent::setMovable(bool movable, bool verticalMovable, bool horizontalMovable)
{
    this->isMovableFlag = movable;
    this->isVerticalMovableFlag = verticalMovable;
    this->isHorizontalMovableFlag = horizontalMovable;
}


bool IRNodeComponent::isMoving() const
{
    return this->movingFlag;
}


bool IRNodeComponent::isDragging() const
{
    return this->draggingFlag;
}
*/

// ==================================================
/*
bool IRNodeComponent::isResizable() const
{
    return this->isResizableFlag;
}


// return a flag shows whether this Component is being resized or not. Default is false.
bool IRNodeComponent::isResizing() const
{
    return this->resizingFlag;
}

void IRNodeComponent::setResizingStart(bool flag)
{
    if(flag)
    {
        this->isMovableFlag = false;
        this->resizingFlag = true;
        // store the current size
        this->previousWidth = getWidth();
        this->previousHeight = getHeight();
        this->previousX = getX();
        this->previousY = getY();
        sendChangeMessage();
    }else{
        recoverEventStatus();
    }
}
*/

void IRNodeComponent::setResizingStartFunc()
{
    resizingStartAction();
    sendChangeMessage();// to Workspace
}

void IRNodeComponent::setResizingCompletedFunc()
{
    resizingCompletedAction();
    
}
// ==================================================

// return a flag shows whether this Component is being selected or not. Default is false.
bool IRNodeComponent::isSelected() const
{
    return this->selectedFlag;
}


// return a flag shows whether the belonging workspace is on edit mode or not.
bool IRNodeComponent::isEditMode() const
{
    return this->editModeFlag;
}


// if edit mode is true, this object does not receive any Mouse/Keyboard events
// if false, this object receive Mouse/Keyboard events
void IRNodeComponent::setEditMode(bool flag)
{
    setEditModeToResizeSquare(flag);
    // disable resizingSquare in Control mode

    this->editModeFlag = flag;
    statusChangedWrapper(IRNodeComponentStatus::EditModeStatus);
    editModeChangedEvent();
    repaint();
}

bool IRNodeComponent::isCopied() const
{
    return this->copiedFlag;
}


bool IRNodeComponent::isCopiable() const
{
    return this->isCopiableFlag;
}

bool IRNodeComponent::isMouseListenerFlag() const
{
    return this->mouseListenerFlag;
}


void IRNodeComponent::setMouseListenerFlag(bool flag)
{
    this->mouseListenerFlag = flag;
}

//unique ID
void IRNodeComponent::setUniqueID(String id)
{
    this->uniqueID = id;
}


void IRNodeComponent::setUniqueID(std::string id)
{
    this->uniqueID = String(id);
}


String IRNodeComponent::getUniqueID() const
{
    return this->uniqueID;
}

void IRNodeComponent::setActive(bool active)
{
    
    this->isActiveFlag = active;
}

void IRNodeComponent::hide(bool flag)
{
    
    //std::cout << "IRNodeComponent::hide of " << this->name << " : isVisible() = " << isVisible() << " : new flag = " << flag << std::endl;
    //setVisible(flag);
    setSelected(false);

    // hide only, do not show
    if(flag)
    {
        setVisible(flag);
        //this->parent->addMouseListener(this, true);
        //this->parent->addAndMakeVisible(this);
    }else
    {
        showSquare(flag);
        setVisible(flag);
        //this->parent->removeMouseListener(this);

        //this->parent->removeChildComponent(this);
    }
    
}


// user defined popup menu events
void IRNodeComponent::popupMenuEvents()
{
    
}

// **** BELOW ALREDY DONE BY K

void IRNodeComponent::statusChangedWrapper(IRNodeComponentStatus status)
{
    switch (status)
    {
        case EditModeStatus:
            // cancel selection
            setSelected(false);
            
            if(isEditMode())
            {
                if(! this->mouseListenerFlag)
                {
                    addMouseListener(this->parent, true);
                    this->mouseListenerFlag = true;
                }
                
                for(auto comp : getChildren())
                {
                    
                    //std::cout<<"statusChangedWrapper " << comp << std::endl;
                    comp->setInterceptsMouseClicks(false, false);
                }
                
                
            }else{
                
                if(this->mouseListenerFlag)
                {
                    removeMouseListener(this->parent);
                    this->mouseListenerFlag = false;
                }
                
                for(auto comp : getChildren())
                {
                    comp->setInterceptsMouseClicks(true, true);
                }
                
               
            }
            
            break;
        default:
            break;
    }
    
    // callback function :: used in IRUIFoundation to inform any of IRNodeObject's status change
    if(this->statusChangeCompleted != nullptr)
        statusChangeCompleted(status);
    
    // call statusChangeCallback
    statusChangedCallback(status);
}


// =============================================


void param_register(std::string id, int data)
{
    t_json save = t_json::object({
        {id, data}
    });
}

// =============================================

void IRNodeComponent::bringToFront(bool registerZIndex)
{
    
    std::cout << "IRNodeComponent::bringToFront\n";
    toFront(true);
   
    if(isSelected()) bringSquareToFront();
    
    // inform IRWorkspaceComponent 
    moveToFrontEvent(registerZIndex);
}
void IRNodeComponent::bringToBack()
{
    
    std::cout << "IRNodeComponent::bringToBack\n";
    toBack();
    
    moveToBackEvent();
    // after all others are to front
    if(isSelected()) bringSquareToBack();

}


// =============================================

void IRNodeComponent::aboutToMoveAction()
{
    updateResizingSquare();
}


// =============================================

// =============================================

void IRNodeComponent::resizingSquareDraggedAction(MouseEvent e)
{
    resizingAction();
}

void IRNodeComponent::objectRotated(float angle)
{
    

    int x = this->resizingSquare.getBounds().getCentreX();
    int y = this->resizingSquare.getBounds().getCentreY();
    this->resizingSquare.setTransform(AffineTransform::rotation(angle * float_Pi / 180.0, x, y));
    setAngle(angle);

}
