//
//  IRAutomationUIWithPreference.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 28/05/2019.
//

#ifndef IRAutomationUIWithPreference_hpp
#define IRAutomationUIWithPreference_hpp

#include "IRAutomationUI.hpp"
#include "IRAutomationObjectPreference.h"
#include "KeAnimationComponent.h"


class IRAutomationUIWithPreference : public IRAutomationUI,
private KeAnimationComponent,
private ChangeListener

{
public:
    // ==================================================

    IRAutomationUIWithPreference(IRNodeObject* nodeObject, IRStr* str);
    ~IRAutomationUIWithPreference();
    
    IRAutomationObjectPreference* getPreference() const { return this->preference.get(); }
    // ==================================================

private:
    
    void changeListenerCallback(ChangeBroadcaster* source) override;
    
    void hasDescriptorSelectedAction(FFTDescriptor descriptor);

    
    void openAudioFileAction();
    void fileImportCompletedAction() override;
    void updateAudioPreferenceUI();
    
    void updateAnimationFrame() override;
    
    // ==================================================
    bool isFileImportCompletedFlag = false;
    
    
    int fftsize = 2048;
    int hopsize = 1024;
    // ==================================================
    
    std::shared_ptr<IRAutomationObjectPreference> preference;
    // ==================================================

};
#endif /* IRAutomationUIWithPreference_hpp */
