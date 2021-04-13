//
//  IRIconBank
//  InteractiveAutomation - App
//
//  Created by Keitaro on 02/05/2019.
//

#ifndef IRIconBank_hpp
#define IRIconBank_hpp

#include "JuceHeader.h"
#include "singletonClass.hpp"
#include "IRPath.h"

class IRIconBank
{
    
public:
    
    struct IRIconImage
    {
        Image white;
        Image black;
        Image gray;
        
        Image small_white;
        Image small_black;
        Image small_gray;
    };
    
    struct IRLogoImage
    {
        Image small; // 177 x 345
        Image medium; // 355 x 690
        Image large; // 710 x 1380
    };
    
    IRIconBank();
    ~IRIconBank();
    
    void loadImages();
    
    IRIconImage getZoomIn() const { return this->icon_zoomIn; }
    IRIconImage getZoomOut() const { return this->icon_zoomOut; }
    IRIconImage getHorizontalMovable() const { return this->icon_horizontalMovable; }
    IRIconImage getVerticalMovable() const { return this->icon_verticalMovable; }
    IRIconImage getCrossMovable() const { return this->icon_crossMovable; }
    IRIconImage getNotMovable() const { return this->icon_notMovable; }
    IRIconImage getComment() const { return this->icon_comment; }
    IRIconImage getBezier() const { return this->icon_bezier; }
    IRIconImage getLinear() const { return this->icon_linear; }

    IRIconImage loadImageAndReturn(String url);
    IRIconImage loadImageWithSmallAndReturn(String url);

    
    IRIconImage icon_addPage;
    IRIconImage icon_addPage2;
    IRIconImage icon_newSlide_noFrame;
    IRIconImage icon_newSlide;
    IRIconImage icon_deleteSlide;
    IRIconImage icon_inspector;
    IRIconImage icon_load;
    IRIconImage icon_loop;
    IRIconImage icon_newProject; // used
    IRIconImage icon_object;
    IRIconImage icon_object_type1;
    IRIconImage icon_preference;
    IRIconImage icon_save;
    IRIconImage icon_export;
    IRIconImage icon_save_noFrame;
    IRIconImage icon_toNavigator;
    IRIconImage icon_toObjectMenu;
    IRIconImage icon_saveProject_noFrame;
    IRIconImage icon_openProject_noFrame;
    IRIconImage icon_saveasProject_noFrame;
    IRIconImage icon_saveProject_arrow;
    IRIconImage icon_saveasProject_arrow;
    IRIconImage icon_openProject_arrow; // used
    IRIconImage icon_close;
    
    IRIconImage icon_text;
    IRIconImage icon_chart;
    IRIconImage icon_image;
    IRIconImage icon_play;
    IRIconImage icon_pause;
    IRIconImage icon_stop;
    IRIconImage icon_wav;
    IRIconImage icon_video;
    
    IRIconImage icon_rightBar;
    IRIconImage icon_leftBar;
    
    // square icon
    IRIconImage icon_active;
    IRIconImage icon_search;
    
    //Event
    IRIconImage icon_AudioEvent;
    IRIconImage icon_ImageEvent;
    IRIconImage icon_ShapeEvent;
    IRIconImage icon_TextEvent;

    
    
    // logo
    IRLogoImage logo_darkMagenta;
    IRLogoImage logo_darkBlue;
    IRLogoImage logo_darkGreen;
    
    IRLogoImage loadLogoImage(String url);
    
private:
    
    IRIconImage loadImage(String url);
    IRIconImage loadWithSmallImage(String url);
    IRIconImage icon_zoomIn;
    IRIconImage icon_zoomOut;
    
    IRIconImage icon_horizontalMovable;
    IRIconImage icon_verticalMovable;
    IRIconImage icon_crossMovable;
    IRIconImage icon_notMovable;
    
    IRIconImage icon_comment;
    IRIconImage icon_bezier;
    IRIconImage icon_linear;
    
    
    
    
    

    
};
#endif /* IRIconBank_hpp */
