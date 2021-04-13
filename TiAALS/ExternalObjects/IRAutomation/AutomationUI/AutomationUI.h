//
//  AutomationUI.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 23/10/2018.
//

#ifndef AutomationUI_h
#define AutomationUI_h

class AutomationUI : public Component
{
public:
    AutomationUI(Rectangle<int> frameRect)
    {
        this->frameRect = frameRect;
        
        sampleFunction(frameRect);
        

    }
    
    ~AutomationUI()
    {
        
    }
    
    //==============================================================
    //  ------------------------------------------------------------
    void resized() override
    {
        sampleFunction(Rectangle<int>(0,0,getWidth(),getHeight()));
        
    }
    //  ------------------------------------------------------------
    void paint(Graphics& g)override
    {
        
        for(int i=0;i<this->lineVertex.size()-1; i++)
        {
            Path path;
            ColourGradient gf2(this->lineVertex[i].colour,
                              this->lineVertex[i].p,
                              this->lineVertex[i+1].colour,
                              this->lineVertex[i+1].p,
                              true);
            g.setGradientFill(gf2);
            
            path.startNewSubPath (this->lineVertex[i].p);
            
            if(isDrawDot == true)
                g.fillEllipse(this->lineVertex[i].p.getX()-radius/2,
                              this->lineVertex[i].p.getY()-radius/2,
                              radius,
                              radius);

            
            float cx = this->lineVertex[i].p.getX() + (this->lineVertex[i+1].p.getX() - this->lineVertex[i].p.getX())/2.0;
            juce::Point<float> c1 = juce::Point<float>(cx, this->lineVertex[i].p.getY());
            juce::Point<float> c2 = juce::Point<float>(cx, this->lineVertex[i+1].p.getY());
            path.cubicTo (c1,c2,this->lineVertex[i+1].p);
            
            //dot
            if(isDrawDot == true)
                g.fillEllipse(this->lineVertex[i+1].p.getX()-radius/2,
                              this->lineVertex[i+1].p.getY()-radius/2,
                              radius,
                              radius);
            
            g.strokePath(path, PathStrokeType(6.0));
        }
        
        //path.closeSubPath();
    }
    //==============================================================

private:
    
    void sampleFunction(Rectangle<int> frameRect)
    {
        float x = frameRect.getWidth();
        float y = frameRect.getHeight();
        this->lineVertex.clear();

        
        
        this->lineVertex.push_back(a_vertex(juce::Point<float>(0,y/2), SYSTEMCOLOUR.contents));
        this->lineVertex.push_back(a_vertex(juce::Point<float>(x/8,y*2/7), SYSTEMCOLOUR.contents.brighter()));
        this->lineVertex.push_back(a_vertex(juce::Point<float>(x/3,y*3/5), SYSTEMCOLOUR.fundamental));
        this->lineVertex.push_back(a_vertex(juce::Point<float>(x/2,y*1/8), SYSTEMCOLOUR.contents.brighter().brighter()));
        this->lineVertex.push_back(a_vertex(juce::Point<float>(x*2/3,y*3/5), SYSTEMCOLOUR.contents));
        this->lineVertex.push_back(a_vertex(juce::Point<float>(x*6/8,y*3/7), SYSTEMCOLOUR.contents.brighter()));
        this->lineVertex.push_back(a_vertex(juce::Point<float>(x*7/8,y*6/7), SYSTEMCOLOUR.fundamental.darker().darker()));
        this->lineVertex.push_back(a_vertex(juce::Point<float>(x,y/2), SYSTEMCOLOUR.contents));

    }
    
    struct a_vertex{
        juce::Point<float> p;
        Colour colour;

        a_vertex(juce::Point<float>p, Colour colour = Colours::grey)
        {
            this->p = p;
            this->colour = colour;
        }
        

    };
    
    Rectangle<int> frameRect;
    
    float radius = 10;
    
    std::vector<a_vertex> lineVertex;
    
    Colour initialColour = Colours::blue;
    Colour selectedColour = Colours::red;
    
    
    // bool
    bool isDrawDot = false;
    
    
    // system appearance
    IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();
    
};


#endif /* AutomationUI_h */
