//
//  IRMainSpace.hpp
//  IRiMaS
//
//  Created by Keitaro on 27/08/2019.
//

#ifndef IRMainSpace_hpp
#define IRMainSpace_hpp

#include "JuceHeader.h"
#include "IRWindowHeader.h"
#include "IRIconBank.hpp"
#include "IRImageButton.hpp"
#include "IRWorkspace2.hpp"
#include "KeAnimationComponent.h"
#include "IRWorkspaceListViewer.h"

class IRMainSpace : public Component,
public AudioSource,
public ChangeBroadcaster,
public ChangeListener,
private KeAnimationComponent,
private IRWorkspaceComponent::Listener
{
public:
    //==================================================
    IRMainSpace(IRStr* str);
    ~IRMainSpace();
    
    void paint(Graphics& g) override;
    void resized() override;
    
    //==================================================
    // IRWorkspace
    void createNewWorkspace();
    void createNewWorkspace(int sortIndex);

    void addAndMakeVisibleWorkspace(IRWorkspace* space);
    void deleteWorkspace(IRWorkspace* space);
    
    void fullScreenWorkspace();
    void fullScreenWorkspace(IRWorkspace* space, bool isFullScreen);
    
    //==================================================
    // switch slide
    void moveToHigherWorkspace();
    void moveToLowerWorkspace();
    
private:
    void resetAllFullscreenWorkspace(IRWorkspace* exception);
    
public:
    std::vector<IRWorkspace* > getWorkspaces() const { return this->workspaces; }
    IRWorkspace* getTopWorkspace() const { return this->topWorkspace; }
    void setTopWorkspace(IRWorkspace* topSpace);
    
    void giveKeyboardFocusOnTopWorkspace();
    
    // workspace grid and guid
    void setWorkspaceGrid(int grid);
    void setWorkspaceGuid(int guid);
    
    
    void exportTopWorkspaceToImage();
    //==================================================
    void mouseDown(const MouseEvent& e) override;
    void mouseMagnify(const MouseEvent& e, float scaleFactor) override;
    void mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& w) override;
    //==================================================
    //==================================================
    //==================================================
    // ==================================================
    // AudioApp Component
    AudioSource& getMixer() { return this->mixer.getAudioSource(); }
    // ==================================================

    //Listener
    class Listener
    {
    public:
        virtual ~Listener() {}
        
        virtual void nodeObjectSelectionChange(IRNodeObject* obj) {};
        virtual void nodeObjectGetFocused(IRNodeObject* obj) {};
        
        virtual void nothingSelected() {};

        
        virtual void newWorkspaceCreated(IRWorkspace* space) {};
        virtual void workspaceWillDeleted(IRWorkspace* space) {};
        virtual void workspaceHasDeleted() {};
        virtual void workspaceEditModeChanged(IRWorkspace* changedSpace) {};

    };
    
    ListenerList<Listener> listeners;
    
    virtual void addListener(Listener* newListener);
    virtual void removeListener(Listener* listener);
    
    void callNodeObjectSelectionChange(IRNodeObject* obj);
    void callNodeObjectGetFocused(IRNodeObject* obj);
    void callnewWorkspaceCreated(IRWorkspace* space);
    void callWorkspaceWillDeleted(IRWorkspace* space);
    void callWorkspaceHasDeleted();

    void callNothingSelected();

    void callWorkspaceEditModeChanged(IRWorkspace* space);

    // ==================================================

private:
    // ==================================================

    IRStr* ir_str;
    // ==================================================
    //IRWorkspace
    // getting to know when the selection status of a NodeObject has been changed.
    // This function is called when an object is either selected or unselected.
    // this function is, for instance, used to update the Object Controller in the IRRightBar
    void nodeObjectSelectionChange(IRNodeObject* obj) override;
    void nodeObjectGetFocused(IRNodeObject* obj)override;
    void nothingSelected() override;
    void editModeChanged(IRWorkspaceComponent* changedSpace) override;

    // ==================================================
    //AudioAppComponent
    AudioEngine mixer;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override;
    void releaseResources() override;

    //==================================================
    void changeListenerCallback (ChangeBroadcaster* source) override;
    void updateAnimationFrame() override;

    //==================================================
    // Workspace
    std::vector<IRWorkspace*> workspaces;
    IRWorkspace* topWorkspace = nullptr;
    
    //==================================================
    // for Reference manual
    Image loadImage(String url);
    Image getReferenceOfIndex(int index);
    Image referenceImage;
    //==================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRMainSpace)
};


#endif /* IRMainSpace_hpp */
