//
//  IRWindowComponent.cpp
//  IRiMaS
//
//  Created by Keitaro on 09/08/2019.
//

#include "IRWindowComponent.hpp"

// ==================================================
// FUNDAMENTAL
// ==================================================

IRWindowComponent::IRWindowComponent(String projectName,
                                     Rectangle<int> frameRect) :
projectName(projectName),
frameRect(frameRect)
{
    initialize();
    createComponents();

    //initially set object menu on t
    this->leftBar->toObjectMenuAction(true);
    
    audioSetup();
}
// ----------------------------------------

IRWindowComponent::~IRWindowComponent()
{
    closeAudioSetup();

    this->mainSpace.reset();
    this->bar.reset();
    this->leftBar.reset();
    this->rightBar.reset();
    
    this->iconBank.reset();
    this->ir_str.reset();
    
    
}

// ----------------------------------------

void IRWindowComponent::paint(Graphics& g)
{
    //g.fillAll(this->ir_str->SYSTEMCOLOUR.fundamental);
    g.fillAll(this->ir_str->SYSTEMCOLOUR.fundamental);
    
    g.fillAll(Colours::yellow);
    //g.fillAll(Colours::transparentWhite);
    
    
}
// ----------------------------------------

void IRWindowComponent::resized() 
{
    int w = getWidth();
    int h = getHeight();
    
    this->mainComponentHeight = h - this->barHeight;
    
    this->bar->setBounds(0, 0, w, this->barHeight);
    this->mainSpace->setBounds(this->leftBarWidth, this->barHeight,
                               w - this->leftBarWidth, this->mainComponentHeight);
    
    
    int lw = (this->leftBar->getWidth() >= this->leftBarWidth) ? this->leftBar->getWidth() : this->leftBarWidth;
    this->leftBar->setBounds(0, this->barHeight,
                             lw, 
                             h - this->barHeight);
    
    int rw = this->rightBar->getWidth();
    this->rightBar->setBounds(getWidth() - rw, this->barHeight,
                              rw, getHeight() - this->barHeight);
    this->rightBar->setInitialPos(juce::Point<int>(getWidth(), this->barHeight));
    

}
// ----------------------------------------

void IRWindowComponent::initialize()
{
    
    //keyListener setup
    //setWantsKeyboardFocus(true);
    //addKeyListener(this);
    
    // create IRMasterStr
    this->ir_str.reset(new IRMasterStr());
    this->ir_str->projectOwner = this;
    this->ir_str->setKeyListener(this);
    this->ir_str->setMouseListener(this);
    this->ir_str->projectName = this->projectName;
    this->ir_str->SYSTEMCOLOUR = IR::darkGraySet();
    
    this->iconBank.reset( new IRIconBank() );
    this->ir_str->ICONBANK = this->iconBank.get();
    
    Font f;
    this->ir_str->fontFamilyList = f.findAllTypefaceNames();
        
    //lookandfeelcolour
    
    updateAppearance();
    
}

void IRWindowComponent::initializeUI()
{
    
}

// ----------------------------------------
// should be called after rightBar created
void IRWindowComponent::createBarComponent()
{
    if(this->bar.get() != nullptr)
    {
        if(this->bar->isVisible())
        {
            removeChildComponent(this->bar.get());
        }
    }
    
    
    this->bar.reset(new IRTitleBar(this->ir_str.get(), "Untitled"));
    this->bar->addChangeListener(this);
    auto gridArea = this->bar->getGridAreaComponent();
    gridArea->GridLabelChangedCallback = [this] (int val) { GridLabelChanged(val); };
    gridArea->GuideLabelChangedCallback = [this] (int val) { GuideLabelChanged(val); };
    
    
    
    addAndMakeVisible(this->bar.get());
    // title bar and right bar (link)
    this->bar->comp.rightBarButtonCallback = [this](bool flag){
        this->rightBar->openSpaceAction(flag);
    };
    this->bar->comp.editModeButtonCallback = [this] { editModeButtonClicked(); };

    // connect to the title component callbacks
    this->bar->getProjectButtonComponent()->closeButtonCallback = [this] { closeButtonClicked(); };
    this->bar->getProjectButtonComponent()->newSlideButtonCallback = [this] { newSlideButtonClicked(); };
    this->bar->getProjectButtonComponent()->newProjectButtonCallback = [this] { newProjectButtonClicked(); };
    this->bar->getProjectButtonComponent()->saveButtonCallback = [this] { saveButtonClicked(); };
    this->bar->getProjectButtonComponent()->saveasButtonCallback = [this] { saveasButtonClicked(); };
    this->bar->getProjectButtonComponent()->openButtonCallback = [this] { openButtonClicked(); };
    this->bar->getProjectButtonComponent()->exportButtonCallback = [this] { exportButtonClicked(); };

    

    //currently this is not active
    this->bar->titleDoubleClickedCallback = [this] { titleDoubleClicked(); };
    

}

void IRWindowComponent::createLeftComponent()
{
    if(this->leftBar.get() != nullptr)
    {
        if(this->leftBar->isVisible())
        {
            removeChildComponent(this->leftBar.get());
        }
    }
    
    this->leftBar.reset(new IRLeftBar(this->ir_str.get()));
    this->leftBar->addChangeListener(this);
    addAndMakeVisible(this->leftBar.get());
    
    this->leftBar->workspaceSelectedCallback = [this](IRWorkspace* space) { workspaceSelected(space); };
    this->leftBar->workspaceDeleteCallback = [this](IRWorkspace* space) { deleteWorkSpace(space); };

}

void IRWindowComponent::createComponents()
{
    this->rightBar.reset(new IRRightBar(this->ir_str.get()));
    this->rightBar->addMouseListener(this, true);
    this->mainSpace.reset(new IRMainSpace(this->ir_str.get()));
    
    this->mixer.addAudioSource(&this->mainSpace->getMixer());
    this->mainSpace->addListener(this);
    this->mainSpace->addListener(this->rightBar.get());
    this->mainSpace->addMouseListener(this, true);
    
    // main space is back
    addAndMakeVisible(this->mainSpace.get());
    addAndMakeVisible(this->rightBar.get());

    
    //this should be called after rightBar created
    createBarComponent();
    createLeftComponent();
        
}
// ----------------------------------------

void IRWindowComponent::changeListenerCallback (ChangeBroadcaster* source)
{
    if(source == this->bar.get())
    {
        if(this->bar->getStatus() == IRWindowBarActionStatus::MoveWindow)
        {
            if(this->windowMoveAction != nullptr)
                this->windowMoveAction(this->bar->pos);
        }
    }
    else if(source == this->leftBar.get())
    {
        if(this->leftBar->getStatus() == IRWindowBarActionStatus::MoveWindow)
        {
            if(this->windowMoveAction != nullptr)
            {
                this->windowMoveAction(this->leftBar->pos);
            }
        }
    }
}
// ----------------------------------------

// ==================================================
// KeyEvent
// ==================================================

bool IRWindowComponent::keyPressed(const KeyPress& key, Component* originatingComponent)
{
    std::cout << "IRWindowComponent keyPressed() : " << key.getKeyCode() << " : " << key.getTextDescription() << ", " << key.getTextCharacter() <<   std::endl;
    
    if(key.getKeyCode() == key.deleteKey || key.getKeyCode() == key.backspaceKey)
    {
        DeleteKeyPressed();
    }
    
    if(key.getTextDescription() == "command + E")
    {
        CommandEPressed();
        return true;
    }
    
    if(key.getTextDescription() == "command + S")
    {
        CommandSPressed();
        return true;
    }
    
    // full screen
    if(key.getTextDescription() == "command + F")
    {
        if(this->mainSpace.get() != nullptr)
        {
            this->mainSpace->fullScreenWorkspace();
            return true;
        }
    }
    
    if(key.getTextDescription() == "command + W")
    {
        return true;
    }
    
    if(CommandShiftNumber(key)) return true;
 
    return false;
}
// ----------------------------------------

void IRWindowComponent::modifierKeysChanged(const ModifierKeys &mod)
{
    
}

// ----------------------------------------

// ==================================================
// MOUSE EVENT
// ==================================================

void IRWindowComponent::mouseDrag(const MouseEvent& e)
{
    auto pos = e.getEventRelativeTo(this).getPosition();
    
    if(this->isResizable)
    {
       juce::Point<int> delta = pos - this->prevPos;
        
        int newW = this->prevSize.getX() + delta.getX();
        int newH = this->prevSize.getY() + delta.getY();
        if(newW < this->minWidth) newW = this->minWidth;
        if(newH < this->minHeight) newH = this->minHeight;
        
        setSize(newW, newH);
    }
    
}

// ----------------------------------------

void IRWindowComponent::mouseUp(const MouseEvent& e)
{
    if(this->isResizable)
    {
        this->isResizable = false;
        if(this->mainSpace->getTopWorkspace() != nullptr)
            this->mainSpace->getTopWorkspace()->setResizing(false);
    }
}
// ----------------------------------------

void IRWindowComponent::mouseDown(const MouseEvent& e)
{
    auto pos = e.getEventRelativeTo(this).getPosition();
    this->prevPos = pos;
     
    // store current window size
    this->prevSize =juce::Point<int> (getWidth(), getHeight());
    
    if(pos.getX() > getWidth() - this->resizableMargin &&
       pos.getY() > getHeight() - this->resizableMargin)
    {
        this->isResizable = true;
        if(this->mainSpace->getTopWorkspace() != nullptr)
            this->mainSpace->getTopWorkspace()->setResizing(true);
    }else
    {
        this->isResizable = false;
        if(this->mainSpace->getTopWorkspace() != nullptr)
            this->mainSpace->getTopWorkspace()->setResizing(false);
    }
    
    //close menu if it is opened
    this->leftBar->closeObjectMenu();
}
// ----------------------------------------

void IRWindowComponent::mouseMove(const MouseEvent& e)
{
    
}
// ----------------------------------------

// ==================================================
// CHILD COMPONENTS
// ==================================================

void IRWindowComponent::setComponentsHeight(int barHeight, int mainHeight)
{
    this->barHeight = barHeight;
    this->mainComponentHeight = mainHeight;
}
// ----------------------------------------


// ==================================================
// WORKSPACE
// ==================================================

void IRWindowComponent::createNewWorkspace()
{
    this->mainSpace->createNewWorkspace();
}

void IRWindowComponent::createNewWorkspace(int sortIndex)
{
    
    this->mainSpace->createNewWorkspace(sortIndex);
}
// ----------------------------------------

// ----------------------------------------
// ----------------------------------------
// ----------------------------------------
// ----------------------------------------

// ==================================================
// WORKSPACE
// ==================================================

void IRWindowComponent::setEditMode(bool flag)
{
    this->isEditModeFlag = flag;
    
    this->bar->comp.setEditMode(flag);
    
    for(auto space : this->mainSpace->getWorkspaces())
    {
        space->setEditMode(flag);
    }
}

// ==================================================
// PROJECT
// ==================================================
void IRWindowComponent::openProject()
{
   
}
void IRWindowComponent::closeProject(DocumentWindow* closingWindow)
{

}

void IRWindowComponent::createNewProject()
{
    
}

// ==================================================
//IRMainSpace Listener
void IRWindowComponent::nodeObjectSelectionChange(IRNodeObject* obj)
{
    

}

void IRWindowComponent::nodeObjectGetFocused(IRNodeObject* obj)
{
    
}

void IRWindowComponent::nothingSelected()
{
    if(this->rightBar.get() != nullptr)
    {
        //this->rightBar->showNothingSelectedUI();
        auto workspace = this->mainSpace->getTopWorkspace();
        if(workspace != nullptr)
        {
            this->rightBar->showWorkspaceController(workspace->getController());
        }
    }
}

void IRWindowComponent::newWorkspaceCreated(IRWorkspace* space)
{
    std::cout << "IRWindowComponent::newWorkspaceCreated\n";
    if(this->leftBar.get() == nullptr) return;
    
    this->leftBar->addNewWorkspaceSlide(space);
    
    //updateScreenshotInAnotherThread();
    
}



void IRWindowComponent::workspaceEditModeChanged(IRWorkspace* changedSpace)
{
    std::cout << "IRWindowComponent::workspaceEditModeChanged\n";
    this->isEditModeFlag = changedSpace->isEditMode();
        
    for(auto space : this->mainSpace->getWorkspaces())
    {
        if(space != changedSpace)
            space->setEditMode(this->isEditModeFlag);
    }
}


// ==================================================



// ==================================================
// SYSTEM
// ==================================================
// Audio
void IRWindowComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    
    std::cout << "sampleRate = " << sampleRate << std::endl;

    this->mixer.getAudioSource().prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void IRWindowComponent::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
{
    this->mixer.getAudioSource().getNextAudioBlock(bufferToFill);
}

void IRWindowComponent::releaseResources()
{
    this->mixer.getAudioSource().releaseResources();
}

// AudioAppComponent
void IRWindowComponent::audioSetup()
{
    //setAudioChannels(0, 2);
}


void IRWindowComponent::closeAudioSetup()
{
    //shutdownAudio();
}

// ==================================================
// project
void IRWindowComponent::closeButtonClicked()
{
    // if not yet saved after any changes
    if(!this->ir_str->isProjectSaved)
    {
        
    }else // saved!
    {
        closeProject();
    }
}

void IRWindowComponent::closeProject()
{
    if(this->closeProjectCallback != nullptr)
        this->closeProjectCallback();
}

void IRWindowComponent::editModeButtonClicked()
{
    if(this->mainSpace->getWorkspaces().size() > 0)
    {
        /*
        bool em = this->mainSpace->getTopWorkspace()->isEditMode();
        this->mainSpace->getTopWorkspace()->setEditMode(!em);
        this->bar->comp.setEditMode(!em);
         */
        
        setEditMode(!isEditMode());
    }
}

void IRWindowComponent::titleDoubleClicked()
{
   
    Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
    
    if(r.getWidth() == getWidth() && r.getHeight() == getHeight())
    {
        
        if(this->previousSize.getX() > 0 && this->previousSize.getY() > 0)
            setSize(this->previousSize.getX(), this->previousSize.getY());
    }else
    {
        this->previousSize =juce::Point<int>(getWidth(), getHeight());
        setSize(r.getWidth(), r.getHeight());
        if(this->windowMoveAction != nullptr)
            this->windowMoveAction(juce::Point<int>(0,0));
    }
  
}

void IRWindowComponent::newSlideButtonClicked()
{
    std::cout << "IRWindowComponent::newSlideButtonClicked\n";
    this->mainSpace->createNewWorkspace();
}
void IRWindowComponent::newProjectButtonClicked()
{
    if(this->newProjectCallback != nullptr)
        this->newProjectCallback();
}
void IRWindowComponent::saveButtonClicked()
{
    saveProject();
}
void IRWindowComponent::saveasButtonClicked()
{
    saveAsProject();
}

void IRWindowComponent::openButtonClicked()
{
    if(this->openProjectCallback != nullptr)
        this->openProjectCallback();
    
}

void IRWindowComponent::exportButtonClicked()
{
    if(this->exportCallback != nullptr)
        this->exportCallback();
    
    exportTopWorkspaceToImage();
    
}

void IRWindowComponent::GridLabelChanged(int val)
{
    this->mainSpace->setWorkspaceGrid(val);
}

void IRWindowComponent::GuideLabelChanged(int val)
{
    this->mainSpace->setWorkspaceGuid(val);
}


// ==================================================

// called from IRLeftBar
void IRWindowComponent::workspaceSelected(IRWorkspace* space)
{
    std::cout << "workpsaceSelected " << space << std::endl;
    this->mainSpace->setTopWorkspace(space);

}

void IRWindowComponent::deleteWorkSpace(IRWorkspace* space)
{
    this->mainSpace->deleteWorkspace(space);
    
}
// ==================================================


void IRWindowComponent::updateAppearance()
{
    getLookAndFeel().setColour(ComboBox::backgroundColourId, this->ir_str->SYSTEMCOLOUR.fundamental);
    getLookAndFeel().setColour(ComboBox::textColourId, this->ir_str->SYSTEMCOLOUR.text);
    getLookAndFeel().setColour(PopupMenu::backgroundColourId, this->ir_str->SYSTEMCOLOUR.contents);
    getLookAndFeel().setColour(PopupMenu::highlightedBackgroundColourId, this->ir_str->SYSTEMCOLOUR.fundamental);

    getLookAndFeel().setColour(ColourSelector::backgroundColourId, this->ir_str->SYSTEMCOLOUR.fundamental);
    getLookAndFeel().setColour(Slider::backgroundColourId, this->ir_str->SYSTEMCOLOUR.fundamental);
    getLookAndFeel().setColour(Slider::thumbColourId, this->ir_str->SYSTEMCOLOUR.contents.brighter());
    getLookAndFeel().setColour(Slider::trackColourId, this->ir_str->SYSTEMCOLOUR.text);
    
    getLookAndFeel().setColour(TextButton::buttonColourId, this->ir_str->SYSTEMCOLOUR.fundamental);
    getLookAndFeel().setColour(TextButton::buttonOnColourId, this->ir_str->SYSTEMCOLOUR.contents);
    getLookAndFeel().setColour(TextButton::textColourOnId, this->ir_str->SYSTEMCOLOUR.text);
    //getLookAndFeel().setColour(Slider::backgroundColourId, this->ir_str->SYSTEMCOLOUR.fundamental);
    
    getLookAndFeel().setColour(Label::textColourId, this->ir_str->SYSTEMCOLOUR.text);
    

    /*
    getLookAndFeel().setColour(ComboBox::focusedOutlineColourId, this->ir_str->SYSTEMCOLOUR.contents);
    getLookAndFeel().setColour(ComboBox::arrowColourId, this->ir_str->SYSTEMCOLOUR.text);
    getLookAndFeel().setColour(ComboBox::buttonColourId, this->ir_str->SYSTEMCOLOUR.fundamental);
    getLookAndFeel().setColour(ComboBox::outlineColourId, this->ir_str->SYSTEMCOLOUR.contents);
     */
    
    if(this->leftBar.get() != nullptr)
    {
        this->leftBar->repaint();
    }
    if(this->rightBar.get() != nullptr)
    {
        this->rightBar->repaint();
    }
    if(this->bar.get() != nullptr)
    {
        this->bar->repaint();
    }
    
    repaint();
    
}

// ==================================================
// save
json11::Json IRWindowComponent::saveAction(String projectPath, String projectTitle)
{
    if(projectPath.length() == 0)
    {
        std::cout << "Error : wrong projectPath : empty path\n";
        return json11::Json();
    }
    
    if(projectTitle.length() == 0)
    {
        std::cout << "Error : wrong projectTitle : empty title\n";
        return json11::Json();
    }
    
    this->projectPath = projectPath;
    this->projectTitle = projectTitle;
    
    if(!this->saveLoadClass.createProjectDirectory(projectPath.toStdString()))
    {
        std::cout << "Error : could not create a project directory of " << projectPath << std::endl;
        return json11::Json();
    }
    
    Rectangle<int> b = getBounds();
    
    // creat header data
    t_json header = json11::Json::object({
           {"Project", json11::Json::object({
               {"projectName",     projectTitle.toStdString()},
               {"author",          "test"},
               {"date",            "26.11.2019"},
               {"osType",          "macOS"},
               {"osVersion",       "10.15.1"},
               {"IRVersion",       "0.0.2"},
               {"bounds",          json11::Json::array({0, 0, b.getWidth(), b.getHeight()})}
           })},
       });
       
    this->saveLoadClass.setHeader(header);
    
    json11::Json::object buffer;
    auto workspaces = this->mainSpace->getWorkspaces();
    int index = 0;
    
    KLib k;
    for(auto space : workspaces)
    {
        // generate workspace-00000 to workspace-99999
        std::string s = k.GetNextNumber("workspace-", index, 5);
        buffer[s] = space->makeSaveDataOfThis();
    }
    
    // unify all json data
    //json11::Json::object jo(buffer.begin(), buffer.end());
    
    json11::Json saveData = buffer;
    
    this->saveLoadClass.createWorkspaces(buffer);

    auto sb = KLib().StringSplit(projectPath.toStdString(), '/');
    std::string filename = sb[sb.size()-1] + ".irimas"; // same to the project name
    filename = projectPath.toStdString() + "/" + projectTitle.toStdString() + ".irimas";
    std::cout << "save file name = " << filename << std::endl;
    this->saveLoadClass.writeSaveData(filename);
    
    
    return buffer;
    
}


void IRWindowComponent::saveProject()
{
    std::cout << "IRWindowComponent::saveProject : path = " << this->projectPath << std::endl;
    // if this is the first time to save, then open the dialog window
    // else simply goes to the save action with the same project path.
    if (this->projectPath.length() == 0)
    {
        OpenDialogToSaveProject();
    }else{
        saveAction(this->projectPath, this->projectTitle);
    }
}

void IRWindowComponent::saveAsProject()
{
    //No matter if this proejct directory has been already created,
    // it operates the full save process.
    OpenDialogToSaveProject();
}

void IRWindowComponent::OpenDialogToSaveProject()
{
    // create new save data file with an extension of ".irimas by default
    FileChooser chooser("Save project...",
                        {},
                        "");

    if (chooser.browseForFileToSave(true))
    {
        auto file = chooser.getResult();
        auto path = file.getFullPathName();
        auto filename = file.getFileName();
        std::cout << "file path = " << path << std::endl;
        this->projectPath = path.toStdString();
        this->projectTitle = filename.toStdString();
        
        saveAction(this->projectPath, this->projectTitle);
        this->bar->comp.setTitle(this->projectTitle);
        
    } else { // in case cancelled
        std::cout << "Could not open any files." << std::endl;
    }
   
}
// ==================================================

void IRWindowComponent::setProjectTitle(String title)
{
    if(this->bar.get() != nullptr)
        this->bar->comp.setTitle(title);
}

// ==================================================

// ==================================================

void IRWindowComponent::loadProjectFromSavedData(t_json saveData)
{
   
    std::cout << "========== loadWorkspaces ==========" << std::endl;
    
    // sort map
    
    for (auto it = saveData["Workspaces"].object_items().cbegin(); it != saveData["Workspaces"].object_items().cend(); ++it)
    {
        std::string id = static_cast<std::string>(it->first);
        std::cout << " ########## " << id << " ########## " << std::endl;
        
        // retrieve save data of the workspace
        json11::Json data = saveData["Workspaces"][id].object_items();
        
        // retrieve save data of worksapce appearance
        json11::Json appearance = data["Appearance"];
        std::cout << " # Appearance " << std::endl;
        std::cout << " ## backgroundColour = " << appearance["backgroundColour"].string_value() << std::endl;
        
        // ===== create worksapce =====
        createNewWorkspace(appearance["sortIndex"].int_value());
        // get created workspace
        IRWorkspace* currentSpace = static_cast<IRWorkspace*>(this->mainSpace->getTopWorkspace());
        
        currentSpace->loadThisFromSaveData(data);
        /*
        // do not use setOriginalBounds to set the workspace bounds but use setUserDefineRatio to calculate original bounds
        json11::Json ap = appearance["aspectRatio"].array_items();
        Rectangle<float> aspectRatio = Rectangle<float>(0,0,ap[0].number_value(), ap[1].number_value());
        currentSpace->setUserDefinedRatio(aspectRatio);
        //currentSpace->setZoomRatio(appearance["zoomRatio"].number_value());
        
        std::cout << " ## Aspect ratio = "<< aspectRatio.getWidth() << ", " << aspectRatio.getHeight() << std::endl;
        std::cout << " ## Zoom ratio = " << currentSpace->getZoomRatio() << std::endl;
        currentSpace->setZoomRatio(1.0);

        //auto ob = appearance["originalBounds"].array_items();
        //currentSpace->setOriginalBounds(Rectangle<int>(ob[0].int_value(), ob[1].int_value(), ob[2].int_value(), ob[3].int_value()));

        // retrieve save data of objects on the workspace
        json11::Json Objects = data["Objects"];
        // the object data is stored in array
        json11::Json::array objectArray = Objects.array_items();
        
        std::cout << " ## Object count = " << objectArray.size() << std::endl;
        std::cout << "\n";
        
        for (int i = 0; i < objectArray.size(); i++) // for each item of the array...
        {
            for (auto it = objectArray[i].object_items().cbegin(); it != objectArray[i].object_items().cend(); ++it)
            {
                
                std::cout << " ===== " << it->first << " ===== " << std::endl;
                
                // ===== create object =====
                std::string objectTypeId = it->second["objectType"].string_value();
                IRNodeObject* obj = static_cast<IRNodeObject*>(this->ir_str->createNewObject(objectTypeId, currentSpace, this->ir_str.get()));
                
                json11::Json arrangeCtl = it->second["ArrangeController"];
                obj->setZoomRatio(1.0);
                obj->loadArrangeControllerSaveData(arrangeCtl);

                currentSpace->createObject(obj);

                // load save dada
                obj->loadThisFromSaveData(it->second["ObjectDefined"]);
                
                // ===== END =====
            }
        }
        //reset zoom ratio
        currentSpace->setZoomRatio(1.0);
        //currentSpace->setZoomRatio(appearance["zoomRatio"].number_value());

        
       // currentSpace->manageHeavyWeightComponents(true);
        
        //as default, a workspace is in control mode
        //currentSpace->setEditMode(false);
         
         */
        
    }
    
    
    // initialize this Project
    initProjectAfterLoading();
    // set project save path
    //projectWindow->getProjectComponent()->setProjectPath(directoryPath);
}

void IRWindowComponent::loadArrangeControllerSaveData(IRNodeObject* obj, t_json arrangeCtl)
{
    auto b = arrangeCtl["bounds"].array_items();
    auto rb = arrangeCtl["relativeBounds"].array_items();
    
    // relative first
    obj->setObjectBoundsRelative(rb[0].number_value(), rb[1].number_value(),
                                 rb[2].number_value(), rb[3].number_value());
    
    // absolute second
    obj->setObjectBounds(b[0].int_value(), b[1].int_value(),
                         b[2].int_value(), b[3].int_value());
    
    std::cout << "arrangeCTL bounds = " << b[0].int_value() << ", " << b[1].int_value() << ", " << b[2].int_value() << ", " << b[3].int_value() << std::endl;

        
    auto wrap = arrangeCtl["wrap"].int_value();
    // give wrap only when wrap is TRUE because the oridinary bounds of the enclosed mode does not have the initial bounds. It gets the bounds only when it transfers to enclose mode.
    if(wrap == 1) obj->setEncloseMode(true);
    
    //std::cout << "wrap = " << wrap << std::endl;
    
    
    auto wrapColour = arrangeCtl["wrapColour"].array_items();
    obj->setEncloseColour(Colour((uint8)wrapColour[0].int_value(),
                                 (uint8)wrapColour[1].int_value(),
                                 (uint8)wrapColour[2].int_value(),
                                 (uint8)wrapColour[3].int_value()));
}


void IRWindowComponent::initProjectAfterLoading()
{
    
}

// ==================================================

void IRWindowComponent::exportTopWorkspaceToImage()
{
    if(this->mainSpace.get() != nullptr)
        this->mainSpace->exportTopWorkspaceToImage();
}
// ==================================================

