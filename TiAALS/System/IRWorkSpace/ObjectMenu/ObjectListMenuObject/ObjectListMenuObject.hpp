
#ifndef ObjectListMenuObject_hpp
#define ObjectListMenuObject_hpp

#include "JuceHeader.h"
#include "ColourLib.h"
// #include "MenusListBox.h"
#include "MenuObject.hpp"
// #include "IRObjectCreater.hpp"
#include "IRObjectFactory.hpp"

class ObjectListMenuObject : public IRTableListBox
{
    
public:
    
    ObjectListMenuObject(String title, int rowNumber);
    ~ObjectListMenuObject();
    
    Component* refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;
    
    void makeCells();
    
    std::vector<std::string> getIdBank() const;
    
private:
    
    class CellComponent : public Component
    {
    public:
        CellComponent(String titleText, std::string id, int index, IRTableListBox& td) :
        owner(td)
        {
            this->titleText = titleText;
            this->index = index;
            this->id = id;
        }
        
        ~CellComponent()
        {
        }
        
        CellComponent* copy()
        {
            CellComponent* comp = new CellComponent(this->titleText,
                                                    this->id,
                                                    this->index,
                                                    this->owner);
            return comp;
        }
        
        // ==================================================
        
        void paint(Graphics& g) override
        {
            
            //int p_x = getWidth() / 2 - 50;
            int p_y = (getHeight() - 100) / 2;
            
            g.setColour(SYSTEMCOLOUR.contents);
            
            g.fillEllipse(10, p_y, 100, 100);
            
            Font f("Avenir Next",20, Font::plain);
            g.setColour(SYSTEMCOLOUR.text);
            g.setFont(f);
            g.drawText(this->titleText, 0, p_y + 5, getWidth()-20, 100, Justification::right,true);
            
        }
        // ==================================================
        
        void mouseDown(const MouseEvent& e) override
        {
            this->owner.table.selectRowsBasedOnModifierKeys(this->index-1, e.mods, false);
            Component::mouseDown(e);
        }
        
        void mouseDoubleClick(const MouseEvent& e)override
        {
            this->owner.selectedRowDoubleClicked(this->index);
        }
        
        int getIndex() const { return this->index; }
        
        
        // ==================================================
        
    private:
        
        IRTableListBox& owner;
        int index;
        String titleText;
        std::string id;
        
        
        // system appearance
        IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CellComponent);
    };
    
private:
    
    std::vector<CellComponent* > cells;
    std::vector<std::string> idBank;
    
    // IRObjectFactory
    IRObjectFactory& IRFactory = singleton<IRObjectFactory>::get_instance();
    
};

#endif /* ObjectListMenuObject_hpp */




