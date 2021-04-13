
#include "IRWaveformObject.hpp"


IRWaveformObject::IRWaveformObject(Component* parent, IRStr* str, IRBoundType boundType) :
IRNodeObject(parent, "IRWaveform", str, boundType)
{
    
    setOpaque(false);

    this->controller.reset(new IRWaveformController2(str));
    //this->controller->audioController.addChangeListener(this);
    this->controller->addChangeListenerToAudioController(this);
    setObjController(this->controller.get());
    
    createWaveform();
    
    this->selector = new IRObjectSelection<Component*>();
    
    
    setObjectBounds(0, 0, 400, 150);
 
}

IRWaveformObject::~IRWaveformObject()
{
    this->waveform.reset();
    delete this->selector;
    
    std::cout << "~IRWaveformObject()\n";
   
}

// copy constructor
IRNodeObject* IRWaveformObject::copyThisObject()
{
    std::cout << "IRWaveformObject copyThis " << this << std::endl;
    return new IRWaveformObject(this->parent, getStr());
}

IRNodeObject* IRWaveformObject::copyContents(IRNodeObject* object)
{
    IRWaveformObject* obj = static_cast<IRWaveformObject*>(object);

    // temporary set the same bounds to calculate all other child components at the right positions.
    obj->setObjectBounds(getLocalBounds());
    // open the same audio file
    obj->waveform->getWaveformUI()->openFile(this->waveform->getWaveformUI()->getPath());
    // add all selectionSquares
    for(auto o : this->waveform->getWaveformUI()->selectionSquareObjects)
    {
        Rectangle<int>rect(o->getX(), o->getY(), o->getWidth(), o->getHeight());
        obj->waveform->getWaveformUI()->createSquareObject(rect);
    }
    return obj;
}

IRNodeObject* IRWaveformObject::copyDragDropContents(IRNodeObject* object)
{
    //this->waveform->
    
    
    IRWaveformObject* obj = static_cast<IRWaveformObject*>(object);
    
    obj->waveform->getWaveformUI()->openFile(this->waveform->getWaveformUI()->getPath());
    
    for(auto o : this->waveform->getWaveformUI()->selectedSquareObjectList)
    {
        //obj->setBounds(o->getX(), o->getY(), o->getWidth() + (this->xMargin*2), o->getHeight() + (this->yMargin*2));
        
        //obj->setSize(o->getWidth() + (this->xMargin*2), o->getHeight() + (this->yMargin*2));
        obj->setObjectSize(o->getWidth() + // width
                           this->waveform->getGridSize() +
                           this->waveform->getXMargin()*2,
                           o->getHeight() + // height
                           this->waveform->getGridSize() +
                           this->waveform->getYMargin()*2 +
                           this->waveform->getScrollSpace());
        
        obj->waveform->setAutomationWidthRatio(this->waveform->getAutomationWidthRatio());

        Rectangle<float> bounds = o->getBoundsInRatio();
        double startms = ((double)this->waveform->getWaveformUI()->getStart() + (float)this->waveform->getWaveformUI()->getDisplayDuration()*bounds.getX());
        double durationms = ((double)this->waveform->getWaveformUI()->getDisplayDuration() * bounds.getWidth());
        obj->waveform->getWaveformUI()->setStart(startms);
        obj->waveform->getWaveformUI()->setDisplayDuration(durationms);
    }
    
    return obj;
}


t_json IRWaveformObject::saveThisToSaveData()
{
     //start making Json for Selections
 
    std::vector<t_json> selectionData;
    int index = 0;
    for(auto o : this->waveform->getWaveformUI()->selectionSquareObjects)
    {
        t_json d = t_json::object({
            {"rect_"+std::to_string(index), t_json::array({o->getX(), o->getY(), o->getWidth(), o->getHeight()})}
        });
        selectionData.push_back(d);
        
        index++;
    }
    
     //waveform
    Rectangle<int> wb = this->waveform->getBounds();
    t_json save_waveform = t_json::object({
        {"bounds", t_json::array({wb.getX(), wb.getY(), wb.getWidth(), wb.getHeight()})},
        {"start_ms",this->waveform->getWaveformUI()->getStart()},
        {"duration_ms", this->waveform->getWaveformUI()->getDisplayDuration()},
        {"filePath", this->waveform->getWaveformUI()->getPath().toStdString()},
        {"selectionObj", selectionData}
    });
    
    
    t_json save = t_json::object({
        {"waveform", save_waveform}
    });
    
    return save;
}


void IRWaveformObject::loadThisFromSaveData(t_json data)
{
    t_json w = data["waveform"];
    
    std::cout << "waveform : start ms = " << w["start_ms"].number_value() << std::endl;
    this->waveform->getWaveformUI()->setStart(w["start_ms"].number_value());
    this->waveform->getWaveformUI()->setDisplayDuration(w["duration_ms"].number_value());
    this->waveform->getWaveformUI()->openFile(w["filePath"].string_value());
    t_json::array selectionData = w["selectionObj"].array_items();
    std::cout << "selectionData count = " << selectionData.size() << std::endl;
    int index = 0;
    for(auto item : selectionData)
    {
        t_json s = item["rect_"+std::to_string(index)];
        
        Rectangle<int>rect(s[0].int_value(), s[1].int_value(), s[2].int_value(), s[3].int_value());
        
        this->waveform->getWaveformUI()->createSquareObject(rect);
        
        index++;
    }
    this->waveform->repaint();
    
}

// ==================================================
void IRWaveformObject::onResized()
{
    this->waveform->setSize(getWidth(), getHeight());
}


void IRWaveformObject::paint(Graphics& g)
{
    
    g.fillAll(getStr()->SYSTEMCOLOUR.background);
    if(isEditMode())
    {
        auto area = getLocalBounds();//.reduced (2);
        
        g.setColour (getStr()->SYSTEMCOLOUR.contents);
        //g.drawRoundedRectangle (area.toFloat(), 5.0f, 2.0f);
        g.drawRect(area.toFloat(), 1.0);
    }
}
// ==================================================

void IRWaveformObject::createWaveform()
{
    if(this->waveform.get() != nullptr)
    {
        removeAudioComponent(this->waveform->getWaveformUI()->getPlayer());
        this->waveform->getWaveformUI()->removeChangeListener(this);
        removeChildComponent(this->waveform.get());
    }
    
    this->waveform.reset( new IRWaveformObjectUI2(this, getStr()) );
    this->waveform->getWaveformUI()->addChangeListener(this);
    this->waveform->setBounds(this->xMargin,
                                this->yMargin,
                                getWidth()-(this->xMargin*2),
                                getHeight()-(this->yMargin*2));
    this->waveform->setEditMode(isEditMode());
    
    addAndMakeVisible(this->waveform.get());
    childComponentManager(this->waveform.get());
    
    // in case this object uses any AudioSources, we must register this to the internal mixer by this method.
    addAudioComponent(this->waveform->getWaveformUI()->getPlayer());
}

// ==================================================

// call back function automatically called when the status of this object changed by others.
// write some tasks here
void IRWaveformObject::statusChangedCallback(IRNodeComponentStatus status)
{
    switch (status)
    {
        case EditModeStatus:
            this->waveform->setEditMode(isEditMode());
            break;
        case SelectableStatus:
            break;
        default:
            break;
    }
}


// events
void IRWaveformObject::mouseDownEvent(const MouseEvent& e)
{
    std::cout << "IRWaveform Object mouse down\n";
    
    IRNodeObject::mouseDownEvent(e);
    if(this->waveform->getWaveformUI()->isWaveformPainted())
    {
        double displayedDuration = this->waveform->getWaveformUI()->getDisplayDuration();
        double mouseDownProportion = (double)e.getMouseDownX() / (double) getWidth();
        double startTime = displayedDuration * mouseDownProportion;
        //this->waveform->setStart(startTime);
    }
    
}

// ==================================================

void IRWaveformObject::audioFileOpenAction()
{
    // recreate waveform to initialize
    //createWaveform();
    if(!this->waveform->getWaveformUI()->openFile()) return;
    

    
    String path = this->waveform->getWaveformUI()->getPath();
    std::cout << path << std::endl;

    this->controller->getAudioController()->setLoadedAudioFilePath(path);
}

// received from AudioController
void IRWaveformObject::audioControllerChangeListener()
{
    auto status = this->controller->getAudioController()->getStatus();
    std::cout << "status = " << status << std::endl;
    using s = AudioObjectController::AudioObjectControllerStatus;

    switch(status)
    {
        case s::AudioFileOpen:
            audioFileOpenAction();
            break;
        case s::PLAY:
            this->waveform->getWaveformUI()->playFromBegin();
            
            break;
        case s::PAUSE:
            this->waveform->getWaveformUI()->pausing();
            break;
        case s::STOP:
            this->waveform->getWaveformUI()->stop();
            break;
            
        default:
            break;
    }
}

// ==================================================

void IRWaveformObject::IRChangeListenerCallback(ChangeBroadcaster* source)
{
    
    if(source == this->waveform->getWaveformUI())
    {
        switch(this->waveform->getWaveformUI()->status)
        {
            case IRWaveformObjectUI::DRAGOUT:
                // stop playing audio
                this->waveform->getWaveformUI()->stop();
                this->callDragOutNodeObjectFromParent();
                break;
            case IRWaveformObjectUI::DROPOUT:
                this->callDropOutNodeObjectFromParent();
                break;
            
            default:
                break;
        }
    }else if(source == this->controller->getAudioController())
    {
        audioControllerChangeListener();
    }
}
// ==================================================


int IRWaveformObject::getXMargin() const
{
    return this->xMargin;
}


int IRWaveformObject::getYMargin() const
{
    return this->yMargin;
}


/*
bool IRWaveformObject::keyPressed(const KeyPress& key, Component* originatingComponent)
{
    
    IRNodeObject::keyPressed(key, originatingComponent);
    return true;
}
*/



