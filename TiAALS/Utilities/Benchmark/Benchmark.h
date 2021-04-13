//
//  Benchmark.h
//  IRiMaS
//
//  Created by Keitaro on 26/07/2019.
//

#ifndef Benchmark_h
#define Benchmark_h

using namespace std::chrono;

class StopWatch{
public:
    void start(){timeStamp = system_clock::now();};
    double stop(){return (system_clock::now()-timeStamp).count() / 1000.0;};
    
    void result(std::string text)
    {
        std::cout << text << " " << stop() << std::endl;
    }
    
protected:
    time_point<std::chrono::system_clock>  timeStamp;
};

#endif /* Benchmark_h */
