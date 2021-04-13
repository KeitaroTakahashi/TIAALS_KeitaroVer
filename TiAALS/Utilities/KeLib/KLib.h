//
//  KeLib.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 23/11/2018.
//

#ifndef KeLib_h
#define KeLib_h


#include "KRandomStringGenerator.h"
#include "KDictionary.h"
#include "KVector.h"
#include "IRPath.h"

class KLib
{
public:
    
    //separator
    std::vector<std::string> StringSplit(const std::string &str, char sep)
    {
        std::vector<std::string> v;
        std::stringstream ss(str);
        std::string buffer;
        while( std::getline(ss, buffer, sep) ) {
            v.push_back(buffer);
        }
        return v;
    }
    
    std::string GetNextNumber( std::string baseString, int &lastNum, int zeroNum )
    {
        std::stringstream ss;
        ss << baseString;
        ss << std::setfill('0') << std::setw(zeroNum) << lastNum++;

        return ss.str();
    }
    
    void showConnectionErrorMessage (const String& messageText)
    {
        AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "Connection error",
                                          messageText,
                                          "OK");
    }
    
    void showErrorMessage (const String& messageText)
    {
        AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "TiAALS ERROR",
                                          messageText,
                                          "OK");
    }
    
    void debugMessage(const String& messageText, bool flag)
    {
        if(flag)
        {
            std::cout << messageText << std::endl;
        }
    }
    
    void showInvalidSystemStatsMessage(const String& messageText)
    {
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     "OS update required!",
                                     messageText,
                                     "OK");
        
        juce::JUCEApplicationBase::quit();
    }
    
    void showMessage(const String& messageText)
    {
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     "TiAALS",
                                     messageText,
                                     "OK");
    }
    
    bool showOKCancelMessage(const String& messageText)
    {
        return AlertWindow::showOkCancelBox(AlertWindow::WarningIcon,
                                            "TiAALS",
                                            messageText,
                                            "OK",
                                            "Cancel");
    }
    
    template<typename T>
    void showRectangle(Rectangle<T> rect){
        std::cout << "x = " << rect.getX() << " : y = " << rect.getY() << " : w = " << rect.getWidth() << " : h = " << rect.getHeight() << std::endl;
    }
    
    
   
};


#endif /* KeLib_h */
