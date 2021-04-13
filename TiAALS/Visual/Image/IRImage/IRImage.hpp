//
//  IRImage.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 01/03/2019.
//

#ifndef IRImage_hpp
#define IRImage_hpp

#include "JuceHeader.h"

/*
 This class is based on juce::Image and ImageFileFormat in order to add loadImage function in it.
 
 */

class IRImage
{
    // --------------------------------------------------
public:
    IRImage(File file);
    IRImage();
    ~IRImage();
    
    // --------------------------------------------------
    void loadImage(File file);
    // --------------------------------------------------
    Image getImageData() const;
    // --------------------------------------------------

    // ==================================================
    // getter
    int getHeight();
    int getWidth();
    
    File getFile() const { return this->file; }

private:
    Image img;
    
    File file;

};


#endif /* IRImage_hpp */
