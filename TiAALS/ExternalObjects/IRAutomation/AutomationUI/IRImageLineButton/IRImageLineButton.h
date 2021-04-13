//
//  IRImageLineButton.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 21/05/2019.
//

#ifndef IRImageLineButton_h
#define IRImageLineButton_h

#include "IRImageButton.hpp"
#include "AutomationVertex.hpp"
#include "IRIconBank.hpp"

using namespace IRAutomation;

class IRImageLineButton : public IRImageButton
{
public:
    IRImageLineButton()
    {
        setImageByStatus();
    }
    
    ~IRImageLineButton()
    {
        
    }
    
    // =======================================================
    
    void mouseDown(const MouseEvent& e) override
    {
        this->status = static_cast<lineStatus>((static_cast<int>(this->status) + 1) % 2);
        setImageByStatus();
        if(this->statusClicked != nullptr) statusClicked(this->status);
    }
    
    void setLineStatus(lineStatus status) { this->status = status; setImageByStatus(); }
    
    
    // =======================================================

    std::function<void(lineStatus)> statusClicked;
    // =======================================================

private:
    void setImageByStatus()
    {
        switch(this->status)
        {
            case LINEAR:
                setImage(ImageBank.getLinear().white);
                break;
            case BEZIER:
                setImage(ImageBank.getBezier().white);
                break;
            default:
                break;
        }
    }
    IRIconBank& ImageBank = singleton<IRIconBank>::get_instance();
    
    
    lineStatus status = LINEAR;
};

#endif /* IRImageLineButton_h */
