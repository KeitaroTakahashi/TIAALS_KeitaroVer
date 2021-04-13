
#ifndef ListTypeScrollableMenu_h
#define ListTypeScrollableMenu_h

#include "JuceHeader.h"





enum IRTableListBoxStatus
{
    selectedRowChanged,
    selectedColumnChanged,
    selectedRowDoubleClicked,
    scrolled
};





class IRTableListBox : public Component,
public TableListBoxModel,
public ChangeBroadcaster
{
    
public:
    
    IRTableListBox(String title, int rowNumber);
    ~IRTableListBox();
    
    void makeTableContents();
    
    void resized() override;
    
    void selectedRowsChanged(int lastRowSelected) override;
    
    void selectedRowDoubleClicked(int lastRowSelected);

    // TableList
    int getNumRows() override;
    void setNumRows(int n);
    
    void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    int getColumnAutoSizeWidth(int columnId) override;
    void sortOrderChanged(int newSortColumnId, bool isForwards) override;
    
    virtual Component* refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;
    
    int getSelection(const int rowNumber) const;
    
    void setSelection(const int rowNumber, const int newSelection);

    int getSelectedIndex() const;
    IRTableListBoxStatus getStatus() const;
    
    
    TableListBox table {{}, this};
    
    
private:
    
    IRTableListBoxStatus status;
    
    int selectedIndex;
    
    String title;
    XmlElement* dataList = nullptr;
    
    int numRows = 0;
    
};




#endif /* ListTypeScrollableMenu_h */




