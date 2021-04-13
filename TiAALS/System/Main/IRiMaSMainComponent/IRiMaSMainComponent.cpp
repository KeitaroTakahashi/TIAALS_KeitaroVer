
#include "IRiMaSMainComponent.hpp"





IRiMaSMainComponent::IRiMaSMainComponent(const String applicationName)
{
    
    // OS version Check
    IRSystemStatus().isValidOS();
    
    this->applicationName = applicationName;
    
    //ObjectFactoryInitializer(); // this will create a singleton and initialise the object palette
    
    this->initialise();
    
}


IRiMaSMainComponent::~IRiMaSMainComponent()
{
    //closeAudioSetup();

    for (auto win : this->projectLib)
    {
        this->mixer.removeSource(&win->getMixer());
        delete win;
    }
    
    this->projectLib.clear();
    
    singleton<IRObjectFactory2>::explicitlyDestroy();
    
    closeAudioSetup();
    
    // finalize singlton
    SingletonFinalizer::finalize();
    
}


void IRiMaSMainComponent::initialise()
{
    
    this->startWindow.reset(new IRStartWindow(applicationName, Rectangle<int>(640, 480)));
    this->startWindow->addChangeListener(this);
    
    audioSetup();
}


void IRiMaSMainComponent::createNewProject()
{
    std::cout << "Creating new project... projectWindow" << std::endl;

    int size = (int)this->projectLib.size();
    
    auto projectWindow2 = createProjectObject();
    
    projectWindow2->setTopLeftPosition(10 * size, 10 * size);
    projectWindow2->addListener(this);
    std::function<void()> callback = [this] { createNewProject(); };
    projectWindow2->setNewProjectCallbackFunc(callback);
    std::function<void()> openCallback  = [this] { openProject(); };
    projectWindow2->setOpenProjectCallbackFunc(openCallback);
    this->projectLib.push_back(projectWindow2);
    projectWindow2->initializeUI();
    projectWindow2->toFront(true);
    projectWindow2->createInitialWorkspace();
    
   // this->mixer.addAudioSource(&projectWindow2->getMixer());
}


void IRiMaSMainComponent::createNewProjectFromSaveData(std::string path)
{
    std::cout << "========== createNewProjectFromSaveData ==========" << std::endl;
    
    
    IRSaveLoadSystem::dataStr data = this->saveLoadClass.getSaveDataStr();
    IRSaveLoadSystem::headerStr header = data.header;
    
    t_json saveData = this->saveLoadClass.getSaveData();
    
    // get project window bounds
    Rectangle<int>bounds = header.bounds;
    
    IRProjectWindow2* projectWin = createProjectObject(header.projectName);
    
    // when loaded, the position of the proejct window is initialized to (0, 0)
    projectWin->setTopLeftPosition(0, 0);
    projectWin->addListener(this);
    std::function<void()> callback = [this] { createNewProject(); };
    projectWin->setNewProjectCallbackFunc(callback);
    std::function<void()> openCallback  = [this] { openProject(); };
    projectWin->setOpenProjectCallbackFunc(openCallback);
    this->projectLib.push_back(projectWin);
    projectWin->initializeUI();
    projectWin->toFront(true);
    projectWin->loadProjectFromSaveData(saveData);
    File f (path);
    projectWin->setProjectPath(f.getParentDirectory().getFullPathName());
    projectWin->setProjectTitle(f.getFileName());
    
    this->startWindow->setVisible(false);
}


void IRiMaSMainComponent::openProject()
{
    std::cout << "Opening a project..." << std::endl;
    
    FileChooser chooser("Select a project file...",
                        {},
                        "*.irimas");
    
    if (chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();
        auto path = file.getFullPathName();
        path.swapWith(path);
        std::string p = path.toStdString();
        std::cout << "load file " << p << std::endl;
        this->saveLoadClass.readSaveData(p);
        createNewProjectFromSaveData(p);
        
    }else
    {
        std::cout << "Could not open any files." << std::endl;
    }
}

void IRiMaSMainComponent::closeProject(DocumentWindow* closingWindow)
{
    /*
    auto it = std::find(this->projectLib.begin(), this->projectLib.end(), closingWindow);
    if (it != this->projectLib.end())
    {
        this->projectLib.erase(it);
    }
    else
    {
        std::cout << "IRiMaSMainComponent : closeProject : Could not find window of " << closingWindow << std::endl;
    }
    
    
    if (this->projectLib.size() == 0)
    {
        this->startWindow->setVisible(true);
    }*/
}

// =======================================================
// *** PRIVATE METHODS

IRProjectWindow2* IRiMaSMainComponent::createProjectObject(String projectName)
{
    Rectangle<int> frameRect (0,
                              0,
                              1280,
                              800);
    
    IRProjectWindow2* projectWin = new IRProjectWindow2(projectName, frameRect);
    this->mixer.addAudioSource(&projectWin->getMixer());
    return projectWin;
}



void IRiMaSMainComponent::changeListenerCallback (ChangeBroadcaster* source)
{
    if (this->startWindow.get() == source)
    {
        if (this->startWindow->getMenuActionStatus() == IRStarter::MenuActionStatus::CreateNewProjectAction)
        {
            createNewProject();
        }
        else if (this->startWindow->getMenuActionStatus() == IRStarter::MenuActionStatus::OpenProjectAction)
        {
            openProject();
        }
    }
    
}


void IRiMaSMainComponent::closeThisWindow(IRMainWindow* closeWindow)
{
    std::cout << "IRiMaSMainComponent::closeThisWindow\n";
    
    bool isClose = KLib().showOKCancelMessage("Do you want to close project?");
    
    if(!isClose) return;
    
    auto it = std::find(this->projectLib.begin(), this->projectLib.end(), closeWindow);
    if (it != this->projectLib.end())
    {
        //remove AudioSource
        this->mixer.removeSource(&closeWindow->getMixer());
        
        this->projectLib.erase(it);
        delete closeWindow;
        std::cout << "closed\n";

    }
    else
    {
        std::cout << "IRiMaSMainComponent : closeThisWindow : Could not find window of " << closeWindow << std::endl;
    }
    
    if (this->projectLib.size() == 0)
    {
        this->startWindow->setVisible(true);
    }
    std::cout << "IRiMaSMainComponent::closeThisWindow done\n";

}

// ==================================================
// SYSTEM
// ==================================================
// Audio

void IRiMaSMainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    this->mixer.getAudioSource().prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void IRiMaSMainComponent::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
{
    this->mixer.getAudioSource().getNextAudioBlock(bufferToFill);
}

void IRiMaSMainComponent::releaseResources()
{
    this->mixer.getAudioSource().releaseResources();
}

// AudioAppComponent
void IRiMaSMainComponent::audioSetup()
{
    setAudioChannels(0, 2);
}


void IRiMaSMainComponent::closeAudioSetup()
{
    shutdownAudio();
}

// ==================================================
