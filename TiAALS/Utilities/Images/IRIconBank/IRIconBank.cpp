//
//  IRIconBank.cpp
//  InteractiveAutomation - App
//
//  Created by Keitaro on 02/05/2019.
//

#include "IRIconBank.hpp"

IRIconBank::IRIconBank()
{
    loadImages();
}

IRIconBank::~IRIconBank()
{
    
}

IRIconBank::IRIconImage IRIconBank::loadImageAndReturn(String url)
{
    
    
#if JUCE_MAC
    return loadImage("/Contents/Resources" + url);
#elif JUCE_IOS
    return loadImage(url);
#endif
    return IRIconImage();
}

IRIconBank::IRIconImage IRIconBank::loadImageWithSmallAndReturn(String url)
{
    
    
#if JUCE_MAC
    return loadWithSmallImage("/Contents/Resources" + url);
#elif JUCE_IOS
    return loadWithSmallImage(url);
#endif
    return IRIconImage();
}


void IRIconBank::loadImages()
{
    String url = "/materials/Images/icon/menu/icon_zoomIn";
    this->icon_zoomIn = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_zoomOut";
    this->icon_zoomOut = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_horizontalArrow";
    this->icon_horizontalMovable = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_verticalArrow";
    this->icon_verticalMovable = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_crossArrow";
    this->icon_crossMovable = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_minus";
    this->icon_notMovable = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_comment";
    this->icon_comment = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_bezier";
    this->icon_bezier = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_linear";
    this->icon_linear = loadImageAndReturn(url);
    
    // icons
    url = "/materials/Images/icon/menu/icon_addPage";
    this->icon_addPage = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_addPage2";
    this->icon_addPage2 = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_inspector";
    this->icon_inspector = loadImageWithSmallAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_load";
    this->icon_load = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_loop";
    this->icon_loop = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_NewProject";
    this->icon_newProject = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_object";
    this->icon_object = loadImageWithSmallAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_video";
    this->icon_video = loadImageAndReturn(url);
    
    
    
    
    url = "/materials/Images/icon/menu/icon_object_type1";
    this->icon_object_type1 = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_preference";
    this->icon_preference = loadImageWithSmallAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_save";
    this->icon_save = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_export";
    this->icon_export = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_toNavigator";
    this->icon_toNavigator = loadImageWithSmallAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_toObjectMenu";
    this->icon_toObjectMenu = loadImageWithSmallAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_text";
    this->icon_text = loadImageWithSmallAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_data";
    this->icon_chart = loadImageWithSmallAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_img";
    this->icon_image = loadImageWithSmallAndReturn(url);
    

    
    url = "/materials/Images/icon/menu/icon_play";
    this->icon_play = loadImageWithSmallAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_pause";
    this->icon_pause = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_stop";
    this->icon_stop = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_wav";
    this->icon_wav = loadImageWithSmallAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_rightBar";
    this->icon_rightBar = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_leftBar";
    this->icon_leftBar = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_newSlide_noFrame";
    this->icon_newSlide_noFrame = loadImageAndReturn(url);
        
    url = "/materials/Images/icon/menu/icon_openProject_noFrame";
    this->icon_openProject_noFrame = loadImageAndReturn(url);

    
    url = "/materials/Images/icon/menu/icon_saveProject_noFrame";
    this->icon_saveProject_noFrame = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_saveasProject_noFrame";
    this->icon_saveasProject_noFrame = loadImageAndReturn(url);
    
    
    url = "/materials/Images/icon/menu/icon_saveProject_arrow";
    this->icon_saveProject_arrow = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_saveasProject_arrow";
    this->icon_saveasProject_arrow = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_openProject_arrow";
    this->icon_openProject_arrow = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_close";
    this->icon_close = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_newSlide";
    this->icon_newSlide = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_deleteSlide";
    this->icon_deleteSlide = loadImageAndReturn(url);

    url = "/materials/Images/icon/menu/icon_audioEvent";
    this->icon_AudioEvent = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_ImageEvent";
    this->icon_ImageEvent = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_ShapeEvent";
    this->icon_ShapeEvent = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_TextEvent";
    this->icon_TextEvent = loadImageAndReturn(url);
    
    
    // square Icon
    url = "/materials/Images/icon/menu/icon_active";
    this->icon_active = loadImageAndReturn(url);
    
    url = "/materials/Images/icon/menu/icon_search";
    this->icon_search = loadImageAndReturn(url);
    
    
    // logo
    this->logo_darkBlue = loadLogoImage("logo_15.png");
    this->logo_darkGreen = loadLogoImage("logo_14.png");
    this->logo_darkMagenta = loadLogoImage("logo_10.png");

 
}
IRIconBank::IRIconImage IRIconBank::loadWithSmallImage(String url)
{
    IRIconImage img;
    
    String url_white = url + "_white.png";
    String url_black = url + ".png";
    String url_gray  = url + "_gray.png";
    
    String url_small_white = url + "_small_white.png";
    String url_small_black = url + "_small.png";
    String url_small_gray  = url + "_small_gray.png";
    
    // white image
    File file = File(IRPath().getAppContentsDirectoryPath() + url_white);
    if(!file.exists()) std::cout << "Error : IRIconBank : file does not exist!! " << file.getFullPathName() << std::endl;
    
    img.white = ImageFileFormat::loadFrom(file);
    
    // black image

    file = File(IRPath().getAppContentsDirectoryPath() + url_black);
    if(!file.exists()) std::cout << "Error : IRIconBank : file does not exist!! " << file.getFullPathName() << std::endl;

    img.black = ImageFileFormat::loadFrom(file);
    
    // gray image

    file = File(IRPath().getAppContentsDirectoryPath() + url_gray);
    if(!file.exists()) std::cout << "Error : IRIconBank : file does not exist!! " << file.getFullPathName() << std::endl;

    img.gray = ImageFileFormat::loadFrom(file);
    
    // small white image
    file = File(IRPath().getAppContentsDirectoryPath() + url_small_white);
    if(!file.exists()) std::cout << "Error : IRIconBank : file does not exist!! " << file.getFullPathName() << std::endl;
    img.small_white = ImageFileFormat::loadFrom(file);
    
    // small black image
    file = File(IRPath().getAppContentsDirectoryPath() + url_small_black);
    if(!file.exists()) std::cout << "Error : IRIconBank : file does not exist!! " << file.getFullPathName() << std::endl;
    img.small_black = ImageFileFormat::loadFrom(file);
    
    // small gray image
    file = File(IRPath().getAppContentsDirectoryPath() + url_small_gray);
    if(!file.exists()) std::cout << "Error : IRIconBank : file does not exist!! " << file.getFullPathName() << std::endl;
    img.small_gray = ImageFileFormat::loadFrom(file);
    
    return img;
}


IRIconBank::IRIconImage IRIconBank::loadImage(String url)
{
    IRIconImage img;
    
    String url_white = url + "_white.png";
    String url_black = url + ".png";
    String url_gray  = url + "_gray.png";
    
    
    
    // white image
    File file = File(IRPath().getAppContentsDirectoryPath() + url_white);
    if(!file.exists()) std::cout << "Error : IRIconBank : file does not exist!! " << file.getFullPathName() << std::endl;
    
    img.white = ImageFileFormat::loadFrom(file);
    
    // black image

    file = File(IRPath().getAppContentsDirectoryPath() + url_black);
    if(!file.exists()) std::cout << "Error : IRIconBank : file does not exist!! " << file.getFullPathName() << std::endl;

    img.black = ImageFileFormat::loadFrom(file);
    
    // gray image

    file = File(IRPath().getAppContentsDirectoryPath() + url_gray);
    if(!file.exists()) std::cout << "Error : IRIconBank : file does not exist!! " << file.getFullPathName() << std::endl;

    img.gray = ImageFileFormat::loadFrom(file);
    

    
    return img;
}

IRIconBank::IRLogoImage IRIconBank::loadLogoImage(String fileName)
{
    IRLogoImage logo;
    
    String base;

    #if JUCE_MAC
        base = "/Contents/Resources/materials/Images/Logo/";
    #elif JUCE_IOS
        base = "/materials/Images/Logo/";
    #endif
    
    // small image
    File file = File(IRPath().getAppContentsDirectoryPath() + base + "small/" + fileName);
    if(!file.exists()) std::cout << "Error : IRIconBank : file does not exist!! " << file.getFullPathName() << std::endl;
    logo.small = ImageFileFormat::loadFrom(file);
    
    // small image
    file = File(IRPath().getAppContentsDirectoryPath() + base + "medium/" + fileName);
    if(!file.exists()) std::cout << "Error : IRIconBank : file does not exist!! " << file.getFullPathName() << std::endl;
    logo.medium = ImageFileFormat::loadFrom(file);
    
    // small image
    file = File(IRPath().getAppContentsDirectoryPath() + base + "large/" + fileName);
    if(!file.exists()) std::cout << "Error : IRIconBank : file does not exist!! " << file.getFullPathName() << std::endl;
    logo.large = ImageFileFormat::loadFrom(file);
    
    return logo;
}
