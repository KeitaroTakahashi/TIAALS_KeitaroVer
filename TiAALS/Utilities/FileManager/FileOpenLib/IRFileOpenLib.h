//
//  FileOpenLib.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 24/05/2019.
//

#ifndef FileOpenLib_h
#define FileOpenLib_h

#include "JuceHeader.h"

class IRFileOpenLib
{
public:
    IRFileOpenLib(IRFileManager* fileManager, IRNodeObject* parent)
    {
        this->fileManager = fileManager;
        this->parent = parent;
    }
    
    ~IRFileOpenLib()
    {
        if(this->hasFileLoaded)
        {
            getFileManager()->discardFilePtr(IRFileType::IRAUDIO, this->audioData, this->parent, this->file);
        }
    }
    
    // @param1 "Select a file..."
    // @param2 "*.wav, *.aif, *.aiff, *.mp3"
    void openFile(String messageText, String fileFormat, std::function<void()>callback = nullptr)
    {
        FileChooser chooser(messageText,
                            {},
                            fileFormat);
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
                getFilePtr(this->file, callback);
            }
        }
    }
    
    void getFilePtr(File file, std::function<void()>callback)
    {
        
        std::cout << "getFilePtr\n";
        // set a callback function which is called when file load is completed.
        // get a pointer of the audio file
        std::function<void()> callback = [this]{fileImportCompleted();};
        // create random ID to identify the retrieved ptr.
        KeRandomStringGenerator a;
        this->randomIDForPtr = a.createStrings(10);
        
        getFileManager()->getFilePtrWithCallBack(IRFileType::IRAUDIO,
                                                 file,
                                                 this->parent,
                                                 this->randomIDForPtr,
                                                 callback);
    
        this->hasFileLoaded = true;
        // notify changes to IRProject to update IRFileInspecter
        this->parent->notifyNodeObjectModification();
        
    }
    
    File getFile() const { return this->file; }
    String getPath() const { return this->p; }
    
private:
    
    IRFileManager* fileManager;
    IRNodeObject* parent;
    File file;
    String p;
    
    std::string randomIDForPtr;
    
    bool hasFileLoaded = false;
    
};

#endif /* FileOpenLib_h */
