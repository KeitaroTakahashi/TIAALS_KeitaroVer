
#include "IRImageLoader.hpp"

IRImageLoader::IRImageLoader(IRNodeObject* parent, IRStr* str) :
IRUIFoundation(parent, str)
{
    this->parent = parent;
}

IRImageLoader::~IRImageLoader()
{
    // remove pointer
    if(this->imgData != nullptr)
        getFileManager().discardFilePtr(IRFileType::IRIMAGE, this->imgData, this->parent, this->file);
}


bool IRImageLoader::open()
{
    this->isFileLoadCompleted = false;
    
    FileChooser chooser("Select an image file...",
                        {},
                        "*.png, *.jpg, *.jpeg");
    if (chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();
        this->file = file;
        auto p = file.getFullPathName();
        this->path = p;
        
        String pathToOpen;
        pathToOpen.swapWith(p);
        
        if(pathToOpen.isNotEmpty())
        {
            this->isFileOpened = true;

            this->imgData = static_cast<DataAllocationManager<IRImage>*>(getFileManager().getFilePtr(IRFileType::IRIMAGE,
                                                                                                     file,
                                                                                                    this->parent));
            this->isFileLoadCompleted = true;
        
            // notify modification
            this->parent->notifyNodeObjectModification();
            
        
        }else{
            
            if(!this->isFileOpened)
                this->imgData = nullptr;
            this->isFileOpened = false;
            
        }
        
        sendChangeMessage();
    }
    
    if(this->isFileOpened) return true;
    else return false;
}


bool IRImageLoader::open(String pathToOpen)
{
    this->isFileLoadCompleted = false;
    this->path = pathToOpen;
    pathToOpen.swapWith(this->path);
    
    if(pathToOpen.isNotEmpty())
    {
        this->isFileOpened = true;
        
        File file(this->path);
        
        if(file.exists())
        {
        
            this->imgData = static_cast<DataAllocationManager<IRImage>*>(getFileManager().getFilePtr(IRFileType::IRIMAGE, file, this->parent));
            this->isFileLoadCompleted = true;
            // notify
            this->parent->notifyNodeObjectModification();
        }else{
            KLib().showErrorMessage("Image data " + pathToOpen + " does not exist!");
            
            std::cout << "file " << file.getFullPathName() << " not exist.\n";
            return false;
        }
       

    }else{
        this->isFileOpened = false;
        this->imgData = nullptr;
        return false;
    }
    
    sendChangeMessage();
    return true;
}


void IRImageLoader::resized(int w, int h)
{

}

juce::Point<int> IRImageLoader::sizeFix()
{
    // image size
    int img_w = getData()->getImageData().getWidth();
    int img_h = getData()->getImageData().getHeight();
    
    this->aspectRatio = (double) img_w / (double) img_h;
    std::cout << "aspectRatio = " <<this->aspectRatio << " : w = " << img_w << std::endl;
    if (img_w > this->maxWidth)
    {
        img_w = this->maxWidth;
        img_h = (double)this->maxWidth / this->aspectRatio;
    }
    
    if (img_h > this->maxHeight)
    {
        img_w = (double)this->maxHeight * this->aspectRatio;
        img_h = this->maxHeight;
    }
    
    return juce::Point<int> (img_w, img_h);
}


double IRImageLoader::getAspectRatio() const
{
    return this->aspectRatio;
}


IRImage* IRImageLoader::getData()
{
    return this->imgData->getData();
}


String IRImageLoader::getPath() const
{
    return this->path;
}




