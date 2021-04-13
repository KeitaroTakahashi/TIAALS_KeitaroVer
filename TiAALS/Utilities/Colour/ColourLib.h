//
//  ColourLib.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 24/08/2018.
//

#ifndef ColourLib_h
#define ColourLib_h

#include "JuceHeader.h"
#include "singletonClass.hpp"

namespace IR
{
    
    
    struct colorPattern
    {
        
        String colourName = "default";
        Colour fundamental = Colour(0,0,0);
        Colour background = Colour(0,0,0);
        Colour contents = Colour(0,0,0);
        Colour titleText = Colour(0,0,0);
        Colour text = Colour(0,0,0);
        Font f;
        
        Font h1 { 32.0 };
        Font h2 { 24.0 };
        Font h3 { 18.72 };
        Font h4 { 16.0 };
        Font h5 { 13.28 };
        Font h6 { 10.72 };
    };
    
    struct IRBrown : public colorPattern
    {
        IRBrown()
        {
            this->colourName = "brown";

            this->background = Colour(255,255,255);
            this->fundamental = Colour(61,31,6);
            this->contents = Colour(138,120,104);
            this->titleText = Colour(0,0,0);
            this->text = Colour(255,255,255);
            this->f = Font("Avenir Next",28, Font::plain);

        }
    };
//light Brown
    struct IRLightBrown : public colorPattern
    {
        IRLightBrown()
        {
            this->colourName = "light brown";

            this->background = Colour(255,255,255);
            this->fundamental = Colour(149,123,96);
            this->contents = Colour(192,175,159);
            this->titleText = Colour(0,0,0);
            this->text = Colour(255,255,255);
        }
    };
   //light blue
    struct IRLightBlue : public colorPattern
    {
        IRLightBlue()
        {
            this->colourName = "light blue";

            this->background = Colour(255,255,255);
            this->fundamental = Colour(100,126,149);
            this->contents = Colour(162,177,191);
            this->titleText = Colour(0,0,0);
            this->text = Colour(255, 255, 255);
            
            
        }
    };

//light pink
 struct IRLightPink : public colorPattern
 {
     IRLightPink()
     {
         this->colourName = "light pink";

         this->background = Colour(255,255,255);
         this->fundamental = Colour(182,99,98);
         this->contents = Colour(207,167,170);
         this->titleText = Colour(0,0,0);
         this->text = Colour(255, 255, 255);
     }
 };

//pink
struct IRPink : public colorPattern
{
    IRPink()
    {
        this->colourName = "Pink";

        this->background = Colour(255,255,255);
        this->fundamental = Colour(152,110,135);
        this->contents = Colour(193,167,183);
        this->titleText = Colour(0,0,0);
        this->text = Colour(255, 255, 255);
        
        
    }
};

//bronze
struct bronzeSet : public colorPattern
{
    bronzeSet()
    {
        this->colourName = "Bronze";

        this->background = Colour(255,255,255);
        this->fundamental = Colour(158, 107, 64);
        this->contents = Colour(166,152,112);
        this->titleText = Colour(0,0,0);
        this->text = Colour(255, 255, 255);
        
        
    }
};
//Black
struct blackSet : public colorPattern
{
    blackSet()
    {
        this->colourName = "black";

        this->background = Colour(255,255,255);
        this->fundamental = Colour(0, 0, 0);
        this->contents = Colour(136,136,136);
        this->titleText = Colour(0,0,0);
        this->text = Colour(255, 255, 255);
        
        
    }
};
    
//darkBrown
    struct darkBrownSet : public colorPattern
    {
        darkBrownSet()
        {
            this->colourName = "dark Brown";

            this->background = Colour(255,255,255);
            this->fundamental = Colour(45,30,14);
            this->contents = Colour(122,98,71);
            this->titleText = Colour(0,0,0);
            this->text = Colour(255,255,255);
        }
    };

//darkGreen
    struct darkGreenSet : public colorPattern
    {
        darkGreenSet()
        {
            this->colourName = "dark Green";
            this->background = Colour(255,255,255);
            this->fundamental = Colour(27,64,42);
            this->contents = Colour(112,140,127);
            this->titleText = Colour(0,0,0);
            this->text = Colour(255,255,255);
        }
    };

//Green
struct greenSet : public colorPattern
{
    greenSet()
    {
        this->colourName = "Green";
        this->background = Colour(255,255,255);
        this->fundamental = Colour(104,150,118);
        this->contents = Colour(159,189,169);
        this->titleText = Colour(0,0,0);
        this->text = Colour(255,255,255);
    }
};
    
// Magenta
    struct darkMagentaSet : public colorPattern
    {
        darkMagentaSet()
        {
            this->colourName = "dark Magenta";
            this->background = Colour(255,255,255);
            this->fundamental = Colour(61,7,35);
            this->contents = Colour(125,77,99);
            this->titleText = Colour(0,0,0);
            this->text = Colour(255,255,255);
        }
    };
    
//darkBlue
    struct darkBlueSet : public colorPattern
    {
        darkBlueSet()
        {
            this->colourName = "dark Blue";
            this->background = Colour(255,255,255);
            this->fundamental = Colour(2,27,53);
            this->contents = Colour(71,88,116);
            this->titleText = Colour(0,0,0);
            this->text = Colour(255,255,255);
        }
    };

//silver
struct silverSet : public colorPattern
{
    silverSet()
    {
        this->colourName = "Silver";
        this->background = Colour(255,255,255);
        this->fundamental = Colour(180,180,180);
        this->contents = Colour(211,211,211);
        this->titleText = Colour(0,0,0);
        this->text = Colour(255,255,255);
    }
};


//darkGray
struct darkGraySet : public colorPattern
{
    darkGraySet()
    {
        this->colourName = "Dark Gray";
        this->background = Colour(255,255,255);
        this->fundamental = Colour(74,74,74);
        this->contents = Colour(51,51,51);
        this->titleText = Colour(0,0,0);
        this->text = Colour(255,255,255);
    }
};

    
    struct whiteSet : public colorPattern
    {
        whiteSet()
        {
            this->background = Colour(255,255,255);
            this->fundamental = Colour(255,255,255);
            this->contents = Colour(220,220,220);
            this->titleText = Colour(30,30,30);
            this->text = Colour(30,30,30);
        }
    };
    
    class IRColours
    {
    public:
        
        String colourName;
        Colour fundamental;
        Colour background;
        Colour contents;
        Colour titleText;
        Colour text;
        
        Font f;
        
        Font h1;
        Font h2;
        Font h3;
        Font h4;
        Font h5;
        Font h6;

        bool isWhiteBased = false;
        
        IRColours()
        {
            this->patterns.clear();
            this->patterns.push_back(darkGreenSet());
            this->patterns.push_back(darkMagentaSet());
            this->patterns.push_back(darkBlueSet());

        }
        
        IRColours(colorPattern pattern, bool isWhiteBased = false)
        {
            this->background = pattern.background;
            this->fundamental = pattern.fundamental;
            this->contents = pattern.contents;
            this->titleText = pattern.titleText;
            this->text = pattern.text;
            //this->colourName = pattern.colourName;
            
            this->h1 = pattern.h1;
            this->h2 = pattern.h2;
            this->h3 = pattern.h3;
            this->h4 = pattern.h4;
            this->h5 = pattern.h5;
            this->h6 = pattern.h6;

            this->isWhiteBased = isWhiteBased;
        }
        
        void set(colorPattern pattern)
        {
            //this->colourName = pattern.colourName;
            this->fundamental = pattern.fundamental;
            this->background = pattern.background;
            this->contents = pattern.contents;
            this->titleText = pattern.titleText;
            this->text = pattern.text;
            
            this->h1 = pattern.h1;
            this->h2 = pattern.h2;
            this->h3 = pattern.h3;
            this->h4 = pattern.h4;
            this->h5 = pattern.h5;
            this->h6 = pattern.h6;
        }
        
        
        std::vector<colorPattern> patterns;
        
    };
    
    class HSV2RGB
    {
    public:
        HSV2RGB(float hue, float saturation, float brightness) :
        _hue(hue),
        _saturation(saturation),
        _brightness(brightness)
        {
            
        }
        
        ~HSV2RGB() {}
        /*
        void convert()
        {
            const float chroma = _brightness * _saturation;
            const float hNormalize = _hue / 60.0;
            const float x = _chroma * ( 1.0 - abs(hNormalize%2.0) - 1.0);
            
            if(hNormalize < 1.0)
            {
                r = x;
                b = x;
            }else if(hNormalize < 2.0){
                r = x;
                b = chroma;
            }else if(hNormalize < 3.0){
                
            }
        }*/
        
    private:
        float _hue;
        float _saturation;
        float _brightness;
        
        float r;
        float g;
        float b;
    };

}

#endif /* ColourLib_h */
