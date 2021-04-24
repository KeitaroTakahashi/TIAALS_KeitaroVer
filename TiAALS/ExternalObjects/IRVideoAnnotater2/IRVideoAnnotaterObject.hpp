//
//  IRVideoAnnotaterObject.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 19/03/2021.
//

#ifndef IRVideoAnnotaterObject_hpp
#define IRVideoAnnotaterObject_hpp

#include "IRNodeObject.hpp"
#include "IRVideoAnnotaterObjectUI.hpp"
#include "IRVideoAnnotaterController.hpp"


class IRVideoAnnotater : public IRNodeObject
{
public:
    IRVideoAnnotater(Component* parent, IRStr* str, IRBoundType boundType = IRBoundType::ABSOLUTE);
    ~IRVideoAnnotater();
    // ----------------------------------------
    
    t_json saveThisToSaveData() override;
    void loadThisFromSaveData(t_json data) override;
private:

    void onResized() override;
    void paint(Graphics& g) override;
    
    // ----------------------------------------

    std::unique_ptr<IRVideoAnnotaterObjectUI> UI;
    
    std::shared_ptr<IRVideoAnnotaterController> controller;
    
    std::shared_ptr<VideoAnnotaterWindow> videoAnnotaterWindow;

    // ----------------------------------------
    
    void IRChangeListenerCallback (ChangeBroadcaster* source) override;
    void videoAnnotaterControllerChangeListener();
    void arrangeControllerChangeListener();

    // ----------------------------------------
    void loadSaveDataAfterVideoLoadCompleted();
    t_json squareWorkspace_temporalbuf;
    // ----------------------------------------
    // ----------------------------------------

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRVideoAnnotater)

    
};
#endif /* IRVideoAnnotaterObject_hpp */
