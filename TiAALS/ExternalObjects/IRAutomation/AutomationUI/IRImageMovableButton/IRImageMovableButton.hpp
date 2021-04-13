//
//  IRImageMovableButton.hpp
//  InteractiveAutomation - App
//
//  Created by Keitaro on 20/05/2019.
//

#ifndef IRImageMovableButton_hpp
#define IRImageMovableButton_hpp

#include "IRImageButton.hpp"
#include "AutomationVertex.hpp"
#include "IRIconBank.hpp"

using namespace IRAutomation;

class IRImageMovableButton : public IRImageButton
{
public:
    IRImageMovableButton();
    ~IRImageMovableButton();
    
    void mouseDown(const MouseEvent& e) override;
    
    std::function<void(IRAutomation::movableStatus)> statusClicked;
    
    void setMovableStatus(movableStatus status) { this->status = status; setImageByStatus(); }
    
private:
    
    void setImageByStatus();
    IRIconBank& ImageBank = singleton<IRIconBank>::get_instance();

    
    movableStatus status = VERTICALMOVABLE;
    
};
#endif /* IRImageMovableButton_hpp */
