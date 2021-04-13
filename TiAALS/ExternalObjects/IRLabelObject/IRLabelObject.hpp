
#ifndef IRLabelObject_h
#define IRLabelObject_h

#include "IRNodeObject.hpp"
#include "IRLabelController.hpp"

class IRLabelObject : public IRNodeObject
{
    
public:
    
    IRLabelObject(Component* parent, IRStr* str, IRBoundType boundType = IRBoundType::ABSOLUTE);
    ~IRLabelObject();
    
    IRNodeObject* copyThisObject() override;

    t_json saveThisToSaveData() override;
    void loadThisFromSaveData(t_json data) override;

    void paint(Graphics &g) override;
    void paintOnWorkspace(Graphics& g, Component* workspace) override;
    void onResized() override;
    
    void mouseDownEvent(const MouseEvent& e) override;
    
    void IRChangeListenerCallback (ChangeBroadcaster* source) override;
    
    void setFont(Font font);
    Font getFont() const;
    
    void setAlign(int newAlign);
    
    Label label;
    
    // preference
    std::unique_ptr<IRLabelController> controller;

private:
    // ------------------------------------------------------------
    // call back function automatically called when the status of this object changed by others.
    // write some tasks here
    void statusChangedCallback(IRNodeComponentStatus status) override;
    
    Font font;
    
};




#endif /* IRLabelObject_h */




