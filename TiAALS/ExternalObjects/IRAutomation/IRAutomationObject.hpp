//
//  IRAutomationObject.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 23/10/2018.
//

#ifndef IRAutomationObject_hpp
#define IRAutomationObject_hpp

#include "IRNodeObject.hpp"
#include "IRObjectSelection.hpp"
#include "IRAutomationObjectPreference.h"
#include "IRAUtomationUIWithPreference.hpp"

class IRAutomationObject : public IRNodeObject
{
public:
    IRAutomationObject(Component *parent, IRStr* str, IRBoundType boundType = IRBoundType::ABSOLUTE) :
    IRNodeObject(parent, "IRAutomation", str, boundType)
    {

        this->UI = new IRAutomationUIWithPreference(this, str);
        this->UI->setEditMode(isEditMode());
        this->UI->setBounds(this->xMargin,
                            this->yMargin,
                            getWidth()-(this->xMargin*2),
                            getHeight()-(this->yMargin*2));
        this->UI->addChangeListener(this);
        addAndMakeVisible(this->UI);
        childComponentManager(this->UI);
        //this->UI->demoData(10000);

        setObjectSize(400, 160);
    }
    
    ~IRAutomationObject()
    {
        //delete this->preference;
        delete this->UI;
    }
    
    // ------------------------------------------------------------
    IRNodeObject* copyThisObject() override
    {
        IRAutomationObject* newObj = new IRAutomationObject(this->parent, getStr());
        return newObj;
    }
    // ------------------------------------------------------------
    void loadThisFromSaveData(t_json saveData) override
    {
        
    }
    
    // ------------------------------------------------------------
    void paint(Graphics &g) override
    {
        g.fillAll(getStr()->SYSTEMCOLOUR.contents);
        //auto area = getLocalBounds().reduced (2);
            
       
    }
    // ------------------------------------------------------------
    void onResized() override
    {
        this->UI->setSize(getWidth(), getHeight());
    }
    // ------------------------------------------------------------
    
    void mouseDownEvent(const MouseEvent& e) override
    {
        //change preference Window if not yet
        if(getPreferenceWindow() != nullptr)
        {
            /*
            IRPreferenceSpace* space = getPreferenceWindow()->getPreferenceSpace();
            
            IRPreferenceObject* current = space->getPreferenceObj();
                    
            if(current != this->UI->getPreference()){
                space->setPreferenceObj(this->UI->getPreference());
            }*/
        }
        //getGlobalObjectFromParent();
       
    }
    
    // ------------------------------------------------------------

    void openAudioFileAction()
    {
        std::cout << "openAudilFileAction\n";
        this->UI->openFile();
    }
    
    void openAudioFileCompleted()
    {
        //this->preference->getUI()->getOpenAudioUI()->setAudioFileURL(this->UI->getFilePath());
        
        
    }
    
    //===============================================================
    //Listener
    void IRChangeListenerCallback (ChangeBroadcaster* source) override
    {
        if(source == this->UI)
        {
            if(this->UI->getStatus() == IRAutomationUI::AudioFileImportCompleted)
            {
                openAudioFileCompleted();
            }
        }
    }
    //===============================================================

    IRAutomationObjectPreference *preference;
    
    //===============================================================
// Global Object
    
    void getGlobalObjectFromParent()
    {
        // get
        IRObjectPtr val = nullptr;
        String id = "IRAnalysisMagnitude";
        this->callGetObjectGlobal(id);
        val = this->getGlobalObject();
        
        if(val != nullptr)
        {
            IRAnalysisDataStr* magData = static_cast<IRAnalysisDataStr*>(val);
            std::cout << "fftsize = " << magData->getFFTSize() << " : nframe = " << magData->getNumFrame() << std::endl;
            
            //this->UI->setDescriptor(magData);
        }else
        {
            std::cout << "Error : could not load " << id << std::endl;
        }
    }
    
    
    //===============================================================

    
private:
    
    /*
    bool keyPressed (const KeyPress& key,
                     Component* originatingComponent) override
    {
        
        return true;
    }*/
    
    
    // ------------------------------------------------------------
    // call back function automatically called when the status of this object changed by others.
    // write some tasks here
    void statusChangedCallback(IRNodeComponentStatus status) override
    {
        switch (status)
        {
            case EditModeStatus:
                if(isEditMode())
                {
                    setWantsKeyboardFocus(false);
                    //removeKeyListener(this);
                }else{
                    setWantsKeyboardFocus(true);
                    //addKeyListener(this);
                }
                
                break;
            case SelectableStatus:
                break;
            default:
                break;
        }
    }
    
    IRAutomationUIWithPreference *UI;
    
    // IRAudio from File Manger
    DataAllocationManager<IRAudio>* audioData = nullptr;

    
    int xMargin = 0;
    int yMargin = 0;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRAutomationObject)

};


#endif /* IRAutomationObject_hpp */
