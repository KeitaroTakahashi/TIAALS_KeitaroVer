
#ifndef IRGraphSelector_hpp
#define IRGraphSelector_hpp

#include "IRObjectSelection.hpp"
#include "IRMultiPurposeObject.hpp"





class IRGraphSelector : public IRObjectSelection<Component *>
{

public:
    
    IRGraphSelector();
    ~IRGraphSelector();
    
    void mouseDownHandler(const MouseEvent& e) override;
    void mouseDragHandler(const MouseEvent& e) override;
    void mouseUpHandler(const MouseEvent& e) override;
    
    void setMakeSquareObjectAfterSelection(bool flag);
    bool isMakeSquareObjectAfterSelection() const;

private:
    
    bool multiSelectionFlag = false;
    
    // make Component object at exactly the same place selection square is made.
    bool makeSquareObjectAfterSelection = false;

};

#endif /* IRGraphSelector_hpp */




