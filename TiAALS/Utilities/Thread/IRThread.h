//
//  IRThread.h
//  AudioRetriever
//
//  Created by Keitaro on 17/09/2020.
//

#ifndef IRThread_h
#define IRThread_h

#include "JuceHeader.h"

class IRThread : public Thread
{
public:
    IRThread(const String name) : Thread(name)
    {
        
    }
    
    virtual ~IRThread()
    {
        stopThread(timeout * 1000);
    }
    // --------------------------------------------------

    void startThreadTask()
    {
        this->taskRequested = true;
        startThread();
        notify();
    }
    
    bool checkForRequestedTask()
    {
        return this->taskRequested;
    }
    
    // --------------------------------------------------

protected:
    
    virtual void task() = 0; // called in executeTask called in run()
    
    void exitThread()
    {
        signalThreadShouldExit();
    }
    
    // --------------------------------------------------

private:
    
    void run() override
    {
        while(! threadShouldExit())
        {
            if(checkForRequestedTask())
            {
                this->taskRequested = false; // reset
                executeTask();
            }
            
            wait(500);
        }
        
    }
    
    
    
    void executeTask()
    {
        task();
    }
    
    // --------------------------------------------------
    double timeout = 4.0;
    bool taskRequested = false;
    
    
};

#endif /* IRThread_h */
