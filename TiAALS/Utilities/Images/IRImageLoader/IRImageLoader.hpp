
#ifndef IRImageLoader_hpp
#define IRImageLoader_hpp

#include "JuceHeader.h"

#include "IRUIFoundation.hpp"
#include "IRNodeObject.hpp"


class IRImageLoader : public IRUIFoundation,
public ChangeBroadcaster
{
public:
    
    IRImageLoader(IRNodeObject* parent, IRStr* str);
    ~IRImageLoader();

    bool open();
    bool open(String pathToOpen);
    
    void resized(int w, int h);
    juce::Point<int> sizeFix();

    double getAspectRatio() const;
    
    IRImage* getData();
    String getPath() const;
    
    bool isFileLoadCompleted = false;
    bool isFileOpened = false;
    
private:
    
    IRNodeObject* parent;
    
    String path;
    File file;
    
    DataAllocationManager<IRImage>* imgData = nullptr;
    //IRImage* imgData = nullptr;
        
    double aspectRatio = 0;
    
    // define max size of the loaded picture to avoid erroneous size change
    int maxWidth = 300;
    int maxHeight = 300;
        
};



#endif /* IRImageLoader_hpp */



