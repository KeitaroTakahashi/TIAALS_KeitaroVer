
#include "IRImageViewer.hpp"

IRImageViewer::IRImageViewer(IRNodeObject* parent, IRStr* str) :
IRUIFoundation(parent, str),
imgLoader(parent, str)
{
    this->parent = parent;
    //setSize(100,100);
    addAndMakeVisible(&this->openButton);
    this->openButton.setButtonText("open image");
    
    // ===========================================================================
    // system appearance
    this->setEnabled(true);
    this->openButton.onClick = [this]{ openFile(); };
    this->imgLoader.addChangeListener(this);
}


IRImageViewer::~IRImageViewer()
{
    
}


void IRImageViewer::paint(Graphics& g)
{
    
    if (this->imgRef != nullptr)
    {
        g.drawImageTransformed (this->imgRef->getImageData(),
                                AffineTransform::scale (getWidth()  / (float) this->imgRef->getWidth(),
                                                        getHeight() / (float) this->imgRef->getHeight()), false);
    }
    
}


void IRImageViewer::resized()
{
    this->openButton.setBounds(getLocalBounds());
}


void IRImageViewer::openFile()
{
    bool isOk = this->imgLoader.open();
    if(!isOk) return;
    // receive pointer of the image file from FileManager
    this->imgRef = this->imgLoader.getData();
    
    if(this->imgRef == nullptr)
    {
        std::cout << "Image data not loaded!\n";
        return;
    }
    
    juce::Point<int> fixedSize = this->imgLoader.sizeFix();
    
    setSize(fixedSize.getX(), fixedSize.getY());
    
    std::cout << "openFIle fixedSize = " << fixedSize.getX() << ", " << fixedSize.getY() << std::endl;
}


void IRImageViewer::openFile(String filePath)
{
    if(this->imgLoader.open(filePath))
    {
        this->imgRef = this->imgLoader.getData();
    }else this->imgRef = nullptr;
}


void IRImageViewer::changeListenerCallback (ChangeBroadcaster* source)
{
    if(source == &this->imgLoader)
    {
        if(this->imgLoader.isFileLoadCompleted)
        {
            removeChildComponent(&this->openButton);
            
            //inform parent the size change
            sendChangeMessage();
        }
    }
}


double IRImageViewer::getAspectRatio() const
{
    return this->imgLoader.getAspectRatio();
}


String IRImageViewer::getFilePath() const
{
    return this->imgLoader.getPath();
}


void IRImageViewer::setFilePath(String path)
{
    this->imgLoader.open(path);
}



