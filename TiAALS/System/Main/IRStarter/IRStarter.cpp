
#include "IRStarter.hpp"

#include <random>

IRStarter::IRStarter(Rectangle<int> frameRect)
{
    
    // load icon
    String url = "/materials/Images/icon/menu/icon_openProject_arrow";
    this->icon_openProject_arrow = loadImageAndReturn(url);
    createButton(&this->openProjectButton, this->icon_openProject_arrow);
    this->openProjectButton.setDrawCircle(false);
    this->openProjectButton.setDrawRoundedSquare(true);
    this->openProjectButton.setDrawColour(Colour(130,130,130));
    addAndMakeVisible(&this->openProjectButton);
    this->openProjectButton.onClick = [this] { openProject(); };
    
    this->newProjectLabel.setText("New Project", dontSendNotification);
    this->newProjectLabel.setColour(Label::textColourId, Colour(130,130,130));
    this->newProjectLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&this->newProjectLabel);


    url = "/materials/Images/icon/menu/icon_NewProject";
    this->icon_newProject = loadImageAndReturn(url);
    createButton(&this->newProjectButton, this->icon_newProject);
    this->newProjectButton.setDrawCircle(false);
    this->newProjectButton.setDrawRoundedSquare(true);
    this->newProjectButton.setDrawColour(Colour(130,130,130));
    addAndMakeVisible(&this->newProjectButton);
    this->newProjectButton.onClick = [this] { createNewProject(); };

    
    this->openProjectLabel.setText("Open Project", dontSendNotification);
    this->openProjectLabel.setColour(Label::textColourId, Colour(130,130,130));
    this->openProjectLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&this->openProjectLabel);
    
    //size
   
    int w = frameRect.getWidth();
    int h = frameRect.getHeight();
    
    setBounds(w / 2, h / 2, w, h);
    
    init();
    setWantsKeyboardFocus(true);
}


IRStarter::~IRStarter()
{

    
}


void IRStarter::paint(Graphics& g)
{
    g.fillAll(Colours::white);
    g.drawImage(this->logo, this->logoPos);
}

void IRStarter::resized()
{
    int buttonX = getWidth() / 3;
    int h = 40;
   juce::Point<int> bs =juce::Point<int> ((float)h / this->newProjectButton.getAspectRatio(), h);

    this->newProjectButton.setSize(bs.getX(), bs.getY());
    this->newProjectButton.setCentrePosition(buttonX, getHeight() - 80);
    this->newProjectLabel.setSize(bs.getX() * 2, 30);
    this->newProjectLabel.setCentrePosition(buttonX, getHeight() - 40);
    this->openProjectButton.setSize(bs.getX(), bs.getY());
    this->openProjectButton.setCentrePosition(buttonX * 2, getHeight() - 80);
    this->openProjectLabel.setSize(bs.getX() * 2, 30);
    this->openProjectLabel.setCentrePosition(buttonX * 2, getHeight() - 40);

}


void IRStarter::init()
{
    // randomly chose a logo from 15 variations.
    std::random_device rnd;
    String index = String(rnd() % 15 + 1);
    
    
#if JUCE_MAC
    
    String url = "/Contents/Resources/materials/Images/Logo/logo_" + index + ".png";
    this->logo = loadImage(url);
    
#elif JUCE_IOS
    
    String url = "/materials/Images/Logo/logo_" + index + ".png";
    
#endif
    
    if (this->logo.getWidth() == 0 || this->logo.getHeight() == 0)
    {
        std::cout << "Error : could not load image data of " << url << std::endl;
    }
    //std::cout << "logo width = " << this->logo.getWidth() << std::endl;
    
    
    float w = 140.0f;
    float h = w * (static_cast<float>(this->logo.getHeight()) / static_cast<float>(this->logo.getWidth()));
    float x = static_cast<float>(getWidth()) / 2.0f - w / 2.0f;
    float y = static_cast<float>(getHeight()) / 2.0f - h / 2.0f;
    this->logoPos = Rectangle<float>(x, y - 20, w, h);
}


Image IRStarter::loadImage(String url)
{
    File file = File(IRPath().getAppContentsDirectoryPath() + url);
    return ImageFileFormat::loadFrom(file);
}


// **** **** PRIVATE METHODS **** **** //


void IRStarter::createNewProject()
{
    std::cout << "Creating new project... in Starter" << std::endl;
    this->menu_action_status = MenuActionStatus::CreateNewProjectAction;
    sendChangeMessage();
}


void IRStarter::openProject()
{
    std::cout << "Opening a project..." << std::endl;
    this->menu_action_status = MenuActionStatus::OpenProjectAction;
    sendChangeMessage();
}


void IRStarter::changeListenerCallback(ChangeBroadcaster* source)
{
    
}



// ==================================================
// icon loader

IRIconBank::IRIconImage IRStarter::loadImageAndReturn(String url)
{
#if JUCE_MAC
    return loadIconImage("/Contents/Resources" + url);
#elif JUCE_IOS
    return loadIconImage(url);
#endif
    return IRIconBank::IRIconImage();
}


IRIconBank::IRIconImage IRStarter::loadIconImage(String url)
{
    IRIconBank::IRIconImage img;
    
    String url_white = url + "_white.png";
    String url_black = url + ".png";
    String url_gray  = url + "_gray.png";
    
    // white image
    File file = File(IRPath().getAppContentsDirectoryPath() + url_white);
    if(!file.exists()) std::cout << "Error : IRIconBank : file does not exist!! " << file.getFullPathName() << std::endl;
    
    img.white = ImageFileFormat::loadFrom(file);
    
    // black image

    file = File(IRPath().getAppContentsDirectoryPath() + url_black);
    if(!file.exists()) std::cout << "Error : IRIconBank : file does not exist!! " << file.getFullPathName() << std::endl;

    img.black = ImageFileFormat::loadFrom(file);
    
    // gray image

    file = File(IRPath().getAppContentsDirectoryPath() + url_gray);
    if(!file.exists()) std::cout << "Error : IRIconBank : file does not exist!! " << file.getFullPathName() << std::endl;

    img.gray = ImageFileFormat::loadFrom(file);
    
    return img;
}

//==================================================


void IRStarter::createButton(IRImageButton* button, IRIconBank::IRIconImage img)
{
    button->setImage(img.gray);
    
    //button->setDrawCircle(false);
    addAndMakeVisible(button);
}
