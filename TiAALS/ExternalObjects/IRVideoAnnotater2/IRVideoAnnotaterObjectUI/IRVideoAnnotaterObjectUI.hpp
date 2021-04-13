//
//  IRVideoAnnotaterObjectUI.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 19/03/2021.
//

#ifndef IRVideoAnnotaterObjectUI_hpp
#define IRVideoAnnotaterObjectUI_hpp

#include "IRStrComponent.hpp"
#include "IRImageButton.hpp"
#include "IRIconBank.hpp"
#include "VideoAnnotaterWindow.hpp"

class IRVideoAnnotaterObjectUI : public Component,
public IRStrComponent
{
public:
    IRVideoAnnotaterObjectUI(IRStr* str);
    ~IRVideoAnnotaterObjectUI();
    
    std::function<void()> openVideoButtonClicked = nullptr;
    
    void openVideoAnnotater();
    
    void setVideoAnnotaterWindow(VideoAnnotaterWindow* window);
    
    
private:
    
    void paint(Graphics& g) override;
    void resized() override;


    IRImageButton openVideoButton;
    
    void openVideoButtonClickedAction();
    
    bool clickedFlag = false;
    
    VideoAnnotaterWindow* videoAnnotaterWindow = nullptr;

    
};
#endif /* IRVideoAnnotaterObjectUI_hpp */
