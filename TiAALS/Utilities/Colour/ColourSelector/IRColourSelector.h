//
//  IRColourSelector.h
//  IRiMaS
//
//  Created by Keitaro on 02/10/2019.
//

#ifndef IRColourSelector_h
#define IRColourSelector_h
#include "JuceHeader.h"

class IRColourSelector : public Component
{
public:
    IRColourSelector()
    {
        
    }
    
    ~IRColourSelector()
    {
        
    }
     
    void resized() override
    {
        
    }
    
    void paint(Graphics& g) override
    {
        
    }
    
private:
    
    class colourSpaceWindow : public DocumentWindow
    {
    public:
        colourSpaceWindow(Rectangle<int> frameRect) :
            DocumentWindow("", Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId), DocumentWindow::allButtons)
        {
            // do not show a title bar
            setUsingNativeTitleBar(false);
            setTitleBarHeight(0);
            
            // setup system colour
            //IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();
            //SYSTEMCOLOUR.set(IR::IRBlue());
            
            Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
            int x = r.getWidth();
            int y = r.getHeight();
            setBounds(0, 0, frameRect.getWidth(), frameRect.getHeight());
            setCentrePosition(x / 2, y / 2);
            setResizable(false, false);
            
            
            setVisible(true);
            this->space.reset(new colourSpace());
            
            setContentOwned(this->space.get(), true);
            
        }
        
        ~colourSpaceWindow() {}
        
    private:
        
        class colourSpace : public Component
        {
        public:
            colourSpace()
            {
                //addAndMakeVisible(this->sp.get());
            }
            ~colourSpace()
            {
                
            }
        private:

        };
        std::unique_ptr<colourSpace> space;

    };
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRColourSelector)

};

#endif /* IRColourSelector_h */
