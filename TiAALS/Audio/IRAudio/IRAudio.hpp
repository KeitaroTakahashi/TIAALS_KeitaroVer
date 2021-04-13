//
//  IRAudio.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 25/03/2019.
//

#ifndef IRAudio_hpp
#define IRAudio_hpp

#include "JuceHeader.h"
#include "IRAudioReader.hpp"
#include "IRDescriptor.h"
#include "IRDescriptorBank.hpp"
#include "IRAudioDescriptor.hpp"
#include "KLib.h"
#include "KeAnimationComponent.h"
// ===========================================================================
// import audio file
// ===========================================================================

class IRAudio : public Component,
public ChangeBroadcaster,
private KeAnimationComponent,
private Thread
{
public:
    // Constructing IRAudio and Thread class
    IRAudio();
    
    // stop thread processing...
    ~IRAudio();
    
    // clear ReferenceCountedBuffer::Ptr here
    void clear(ReferenceCountedBuffer::Ptr currentBuffer);
    
    // get Thumbnail of audio data, it returns nullptr if not exists
    AudioThumbnail* getThumbnail();
    
    // =================================================================
    // audio file reader
    // -----------------------------------------------------------------
    // open dialog to select a file
    bool openFile(bool threadSafe = true);
    // open audio file by path
    bool openFileFromPath(String path, bool threadSafe = true);
    // open audio file by File
    bool loadFile(File file, bool threadSafe = true);
    
    // -----------------------------------------------------------------
    // getter of the audio file info
    // -----------------------------------------------------------------
    double getSampleRate() const { return this->sampleRate; }
    
    int getNumChannels() const { return this->numChannels; }
    
    int64 getNumSamples() const { return this->numSamples; }
    
    unsigned int getBitsPerSample() const { return this->bitsPerSample; }
    
    String getPath() const { return this->filePath; }
    
    //String getFileName() const { return this->fileName; }
    
    // print audio file info for debug
    void showAudioFileInfo();
    // ------------------------------------------------------------------
    // getter of the audio file buffer
    // ------------------------------------------------------------------
    AudioSampleBuffer* getAudioBuffer()
    {
        return this->currentBuffer->getAudioSampleBuffer();
        
    }
    
    // return audio buffer in vector<float> data type
    std::vector<float> getAudioBufferInVector();
    
    // get component which eimit any events via Listener
    Component* getEmittingComponent() { return this->emittingComponent; }
    // ===========================================================================
    // Listener
    class Listener
    {
    public:
        virtual ~Listener() {}
        // called when audio file has been loaded
        virtual void fileImportCompleted(IRAudio *obj) {};
        // called when file status changed (will be loaded, completed, deleted etc.)
        // give IRAudio* which is THIS object, in order to notify when this object is deallocated by giving nullptr. see deconstructer of this class
        virtual void fileStatusChanged(IRAudio *obj) {};
        
        // called when zoom in or out action operated in a component which holds IRAudio
        virtual void zoomInOutOperatedFromComponent(IRAudio* obj) {}
        virtual void audioPlayOperatedFromComponent(IRAudio* obj) {}
        virtual void viewPortPositionFromComponent(IRAudio* obj) {}
    };
    
    void addListener(Listener* newListener) { this->ImportAudioListeners.add(newListener);
        std::cout << "IRAudio listener " << this->ImportAudioListeners.size() << std::endl;
    }
    void removeListener(Listener* listener) { this->ImportAudioListeners.remove(listener); }
    
    // ---------------------------------------------------------------------------
    
    std::function<void()> onImportCompleted;
    
    // ===========================================================================
    // public members
    bool isFileOpened = false;
    bool isFileLoadCompleted = false;
    bool isFileLoadFailed = false;
    
    File getFile() const { return this->file; }
    
    //IRDescriptor* getDescriptor() { return this->descriptor.get(); }
    // ===========================================================================

    bool operateAnalysis(FFTDescriptor descriptor, int fftsize, int hopsize);
    bool operateFFTAnalysis(int fftsize, int hopsize);
    void operateLinearPower(int fftsize, int hopsize);

    void operateBasicDescriptors();
    void operateFlatness();
    
    // bool
    bool isCalculated(FFTDescriptor d, int fftsize = 2048);
    
    //get descriptor
    IRDescriptorStr* getDescriptor(FFTDescriptor d, int fftsize);
    
    // descriptor list
    Array<std::string> getDescriptorNameList() const { return this->analyzer.getDescriptorNameList(); }
    
    // ===========================================================================
    // shared Information
    void linkZoomInOutWithSharedComponents(Component* comp);
    void linkAudioPlaywithSharedComponents(Component* comp);
    void linkViewPortPositionWithSharedComponents(Component* comp);
    Component* emittingComponent = nullptr;
    
    
    void setZoomInfo(float w, float h);
    void setZoomInfo(juce::Point<float> zoom);
    juce::Point<float> getZoomInfo() const { return this->zoomInfo; }
    void setCurrentPlayedFrame(int64 frame) { this->currentPlayedFrame = frame; }
    int64 getCurrentPlayedFrame() const { return this->currentPlayedFrame; }
    void setCurrentPlayedPosRatio(float ratio) { this->currentPlayedPosRatio = ratio; }
    float getCurrentPlayedPosRatio() const { return this->currentPlayedPosRatio; }
    void setViewPortPosition(juce::Point<int> pos) { this->viewPortPos = pos; }
    juce::Point<int> getViewPortPosition() const { return this->viewPortPos; }
    
    // ===========================================================================


    
private:
    // ===========================================================================
    //thread related methods
    // ---------------------------------------------------------------------------
    // check
    void run() override;
    
    void checkForBuffersToFree();
    
    // impoart audio file and read the data
    void checkForPathToOpen();
    void OpenPath(File file);
    
    void mainThreadAudioLoader();
    
    // to check when file import completed
    void updateAnimationFrame() override;
    
    // ---------------------------------------------------------------------------
    void callFileImportCompleted();
    void callFileStatusChanged(IRAudio* obj);
    
    void callZoomInOutOperatedFromComponent();
    void callAudioPlayOperatedFromComponent();
    void callViewPortPositionFromComponent();
    
    // ---------------------------------------------------------------------------
    // sharedInformation
    
    int64 currentPlayedFrame = 0;
    float currentPlayedPosRatio = 0.0;
    juce::Point<int> viewPortPos;
    
    juce::Point<float> zoomInfo;
    // ---------------------------------------------------------------------------

    File file;
    String path;
    String filePath;
    String fileName;
    double sampleRate = 0;
    int numChannels = 0;
    int64 numSamples = 0;
    unsigned int bitsPerSample = 0;
    
    // ===========================================================================
    // listner
    ListenerList<Listener> ImportAudioListeners;
    
    // ===========================================================================
    // thread safe reference pointer
    
    //std::unique_ptr<AudioFormatReaderSource> readerSource;
    //AudioFormatReader *reader = nullptr;
    
    ReferenceCountedArray<ReferenceCountedBuffer> buffers;
    ReferenceCountedBuffer::Ptr currentBuffer; // AudioBuffer<float>
    
    AudioFormatManager formatManager;
    
    //thumbnail
    AudioThumbnail* thumbnail = nullptr;
    
    //std::shared_ptr<IRFFTDescriptor> analyzer;
    
    IRDescriptorBank analyzer;
    
    // ===========================================================================
    // descriptor
    //std::shared_ptr<IRDescriptor> descriptor;

    // ===========================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRAudio)
    
};
#endif /* IRAudio_hpp */
