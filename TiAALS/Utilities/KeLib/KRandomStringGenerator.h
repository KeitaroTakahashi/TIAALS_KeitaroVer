//
//  KRandomStringGenerator.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 23/11/2018.
//

#ifndef KRandomStringGenerator_h
#define KRandomStringGenerator_h

class KeRandomStringGenerator
{
    


public:
    
    
    KeRandomStringGenerator()
    {
        
    }

    std::string createStrings(unsigned int cLen)
    {
        std::string buf;
        int i;
        for(i=0;i<cLen;i++)
        {
            buf += getRandomString();
        }
        std::cout << buf << std::endl;
        return buf;
    }
    
private:
    
    std::string alphanum = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    char getRandomString()
    {
        unsigned long cLen = alphanum.length();
        return alphanum[rand() % cLen];
    }
    
    
    
};


#endif /* KRandomStringGenerator_h */
