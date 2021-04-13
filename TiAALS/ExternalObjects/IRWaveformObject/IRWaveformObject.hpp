
#ifndef IRWaveformObject_hpp
#define IRWaveformObject_hpp

#include "IRNodeObject.hpp"
#include "IRWaveformObjectUI2.hpp"
#include "IRWaveformController2.hpp"
#include "IRObjectSelection.hpp"

class IRWaveformObject : public IRNodeObject,
                                IRNodeObject::Listener
{
    
public:
    
    IRWaveformObject(Component* parent, IRStr* str, IRBoundType boundType = IRBoundType::ABSOLUTE);
    ~IRWaveformObject();
    
    
    IRNodeObject* copyThisObject() override; // copy constructor
    IRNodeObject* copyContents(IRNodeObject* object) override;
    IRNodeObject* copyDragDropContents(IRNodeObject* object) override;

    t_json saveThisToSaveData() override;
    void loadThisFromSaveData(t_json data) override;
    
    void onResized() override;
    void paint(Graphics& g) override;
    
    void statusChangedCallback(IRNodeComponentStatus status) override;
    
    // events
    void mouseDownEvent(const MouseEvent& e) override;
    
    void IRChangeListenerCallback (ChangeBroadcaster* source) override;
    
    int getXMargin() const;
    int getYMargin() const;

    std::shared_ptr<IRWaveformObjectUI2> waveform;
    void createWaveform();

    //preference
    std::unique_ptr<IRWaveformController2> controller;

private:
    // ==================================================
    // for audioControllerChangeListener
    void audioFileOpenAction();
    // ==================================================

    // ==================================================

    
    IRObjectSelection<Component* >* selector;
    bool selectFlag = true;
    bool isSelectMode = false;
    
    int xMargin = 0;
    int yMargin = 0;
    
    // ==================================================

    void audioControllerChangeListener();
    
    // ==================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRWaveformObject)
};




#endif /* IRWaveformObject_hpp */




