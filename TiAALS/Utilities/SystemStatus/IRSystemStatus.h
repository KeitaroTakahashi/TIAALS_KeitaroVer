//
//  IRSystemStatus.h
//  IRiMaS
//
//  Created by Keitaro on 23/11/2019.
//

#ifndef IRSystemStatus_h
#define IRSystemStatus_h

#include "JuceHeader.h"
#include "KLib.h"

class IRSystemStatus
{
public:
    IRSystemStatus()
    {
        
    }
    
    ~IRSystemStatus() {}
    
    SystemStats::OperatingSystemType getOS ()
    {
        return SystemStats::getOperatingSystemType();
    }
    
    void isValidOS()
    {
        if(getOS() >= SystemStats::OperatingSystemType::MacOSX_10_14)
        {

        }else
        {
            KLib().showInvalidSystemStatsMessage("TiAALS does NOT support your macOS " + SystemStats::getOperatingSystemName() + " and you are kindly requested to update your system to macOS 10.14 or later.");
        }
    }
    
};

#endif /* IRSystemStatus_h */
