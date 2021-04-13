//
//  IRAudioReader.hpp
//  Thread safe audio file reader
//
//  Created by Keitaro on 17/08/2018.
//

#ifndef IRAudioReader_hpp
#define IRAudioReader_hpp


#include "JuceHeader.h"


// ===========================================================================
// Thread Safe Reference Buffer class for Audio Reader : Do NOT REMOVE IT FROM HERE!
// ===========================================================================

class ReferenceCountedBuffer: public ReferenceCountedObject
{
public:
    typedef ReferenceCountedObjectPtr<ReferenceCountedBuffer> Ptr;
    ReferenceCountedBuffer (const String& nameToUse,
                            int numChannels,
                            int numSamples)
    : name(nameToUse),
    buffer(numChannels, numSamples)
    {
        DBG(String("Buffer named '") + name + "' constructed. numChannels = " + String(numChannels) + ", numSamples = " + String(numSamples));
    }
    
    ~ReferenceCountedBuffer()
    {
        DBG(String("Buffer named '") + name + "' destroyed");
    }
    
    AudioSampleBuffer* getAudioSampleBuffer()
    {
        return &buffer;
    }
    
    int position = 0;
    
private:
    String name;
    AudioSampleBuffer buffer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReferenceCountedBuffer)
    
};

// ===========================================================================
// Thread Safe Reference Buffer class for Thumbnail Reader : Do NOT REMOVE IT FROM HERE!
// ===========================================================================

class ReferenceCountedThumbnail: public ReferenceCountedObject
{
public:
    typedef ReferenceCountedObjectPtr<ReferenceCountedThumbnail> Ptr;
    ReferenceCountedThumbnail (const String& nameToUse)
    : name(nameToUse),
    thumbnailCache(5),
    thumbnail(512, formatManager, thumbnailCache)
    {
        this->formatManager.registerBasicFormats();
        DBG(String("Thumbail named '") + name + "' constructed.");
    }
    
    ~ReferenceCountedThumbnail()
    {
        DBG(String("Thumbail named '") + name + "' destroyed");
    }
    
    AudioThumbnail* getThumbnail()
    {
        return &thumbnail;
    }
    
    int position = 0;
    
private:
    String name;
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbnailCache;
    AudioThumbnail thumbnail;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReferenceCountedThumbnail)
    
};



#endif /* IRAudioReader_hpp */
