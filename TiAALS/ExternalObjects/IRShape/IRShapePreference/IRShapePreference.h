//
//  IRShapePreference.h
//  IRiMaS
//
//  Created by Keitaro on 26/07/2019.
//

#ifndef IRShapePreference_h
#define IRShapePreference_h

#include "IRPreferenceObject.hpp"
#include "IRShapePreferenceUI.hpp"

class IRShapePreference : public IRPreferenceObject
{
public:
    IRShapePreference(String title, Rectangle<int> frameRect, IRStr* str) :
    IRPreferenceObject(title, frameRect, str)
    {
        this->UI = std::make_shared<IRShapePreferenceUI>(str);
        addAndMakeVisible(this->UI.get());
    }
    ~IRShapePreference()
    {
        
    }
    
    void resized() override
    {
        this->UI->setBounds(0,0,getWidth(), getHeight());

    }
    
    void paint(Graphics& g) override
    {
        g.fillAll(getStr()->SYSTEMCOLOUR.contents.brighter());
    }
    
    IRShapePreferenceUI* getUI() const { return this->UI.get(); }
    
private:
    
    std::shared_ptr<IRShapePreferenceUI> UI;
    
};


#endif /* IRShapePreference_h */
