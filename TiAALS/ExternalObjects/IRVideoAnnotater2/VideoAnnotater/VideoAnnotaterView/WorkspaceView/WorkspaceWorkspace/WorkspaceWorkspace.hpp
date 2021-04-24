//
//  WorkspaceWorkspace.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 26/03/2021.
//

#ifndef WorkspaceWorkspace_hpp
#define WorkspaceWorkspace_hpp


#include "IRWorkspaceComponent.hpp"
#include "VideoAnnotaterDelegate.hpp"
#include "IRAnnotationWorkspace.hpp"
#include "VideoAnnotaterWindowController.hpp"

#include "TimeMeasure.hpp"

class WorkspaceWorkspace : public IRAnnotationWorkspace,
public VideoAnnotaterDelegate
{
public:
    WorkspaceWorkspace(String title,
                            Rectangle<int> draggableMargin,
                            IRStr* str,
                            VideoAnnotaterBase* base,
                            int index = 0);
    ~WorkspaceWorkspace();
    
    
    void onPaint(Graphics& g) override;
    void onResized() override;

    std::function<void()> openVideoFileCallback = nullptr;
    // --------------------------------------------------
    
    void createNodeObjectOnWorkspace(IRNodeObject* nodeObj);
    void createNodeObjectFromAnnotation(IRNodeObject* annotation);
    // --------------------------------------------------
    void setAnnotationWorkspace(IRWorkspaceComponent* annotationWorkspace);
    void removeAnnotationWorkspace();
    // --------------------------------------------------

    
    void setPlayPosition(double pos);
    
    void setVideoLength(double length);
    
    // --------------------------------------------------
    
    
    void setMeasureHeight(int height);
    
    void updateObjectOf(IRNodeObject* obj);
    
    // --------------------------------------------------

    t_json getSaveData();
    void loadFromSaveData(t_json data);
    // --------------------------------------------------
    private:

    void loadThisFromSaveData(t_json saveData) override;
    
    IRNodeObject* loadObjectSaveData(t_json objData);

private:
    
    void IRChangeListenerCallback(ChangeBroadcaster* source) override;

    void videoLoadCompleteAction();
    // --------------------------------------------------
    IRWorkspaceComponent* annotationWorkspace = nullptr;
    // --------------------------------------------------

    IRNodeObject* createTextObject();
    IRNodeObject* createTextSequenceObject();
    IRNodeObject* createShapeObject();
    IRNodeObject* createImageObject();
    IRNodeObject* createMediumTextObject();
    IRNodeObject* createSmallTextObject();

    
    IRNodeObject* createTextObjectFromAnnotation(IRNodeObject* annotaiton);
    IRNodeObject* createShapeObjectFromAnnotation(IRNodeObject* annotaiton);
    IRNodeObject* createImageObjectFromAnnotation(IRNodeObject* annotaiton);

    void setupEventObject(IRNodeObject* annotation, IRNodeObject* event);

    void getParametersFromAnnotation(IRNodeObject* target, IRNodeObject* annotation);
    
    void command1Pressed() override;
    void command2Pressed() override;
    void command3Pressed() override;

    
    void adjustObjectWidthToLength(IRNodeObject* event);
    void adjustStartPosition(IRNodeObject* event);
    
    void calcEventTimeFromBounds(IRNodeObject* event);
    // --------------------------------------------------
    // annotation modification
    void nodeObjectModifiedAction(IRNodeObject* obj) override;
    
    // event modification called when moved
    void nodeObjectModifiedNotification(IRNodeObject* event) override;
    // called when event's start and end position changed
    void nodeObjectStartEndTimeChanged(IRNodeObject* event) override;
    
    void nodeObjectDragged(IRNodeObject* event) override;
    void nodeObjectDraggedCompleted(IRNodeObject* event) override;

    // nodeObject resizing
    void nodeObjectResizingStart(IRNodeObject* event) override;
    void nodeObjectBeingResized(IRNodeObject* event) override;
    void nodeObjectResizingCompleted(IRNodeObject* event) override;
    // --------------------------------------------------

    TimeMeasure measure;
    int measureHeight = 40;
    
    // --------------------------------------------------
    // mssage shown before deleting an object
    String beforeDeleteObjectMessage = "You are about to delete the selected sequencer object(s), which will also delete corresponding annotation(s) on the video player. Do you really want to proceed it?";
    // --------------------------------------------------
    void editModeChangedAction() override;
    
    double currentPlayingPosition = 0;
    double videoLength = 0;
    
    class redLine : public Component
    {
    public:
        redLine() { setOpaque(false); }
        ~redLine() {}
        void paint(Graphics& g) override
        {
            g.fillAll(Colours::transparentWhite);
            
            g.setColour(Colours::red);
            //int x = (double)getWidth() * (this->currentPlayingPosition / this->videoLength);
            g.drawLine(0, 0, 0, getHeight(), 4);
        }
       
        
        double currentPlayingPosition = 0.0;
        double videoLength = 0.0;
        void setPlayPosition(double pos) { this->currentPlayingPosition = pos; }
        void setVideoLength(double length) { this->videoLength = length; }
        
    };
    
    redLine line;
};



#endif /* WorkspaceWorkspace_hpp */
