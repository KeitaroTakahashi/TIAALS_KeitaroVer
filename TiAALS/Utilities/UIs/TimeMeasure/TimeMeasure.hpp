//
//  TimeMeasure.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 03/04/2021.
//

#ifndef TimeMeasure_hpp
#define TimeMeasure_hpp

#include <JuceHeader.h>

class TimeMeasure : public Component
{
public:
    
    TimeMeasure();
    ~TimeMeasure();
    
    void setLengthInSec(float sec);
    void setIntervalInSec(float sec);
    
private:
    
    void resized() override;
    void paint(Graphics& g) override;
    
    void drawIntervalLine(Graphics& g);
    
    float shortLineRatio = 0.5;
    float longLineRatio = 1.0;
    
    float length = 0;
    float interval = 1;
    
    
};

#endif /* TimeMeasure_hpp */
