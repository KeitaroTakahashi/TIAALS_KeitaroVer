
#include "IRListBoxObject.hpp"




IRTableListBox::IRTableListBox(String title, int rowNumber)
{
    this->title = title;
    this->numRows = rowNumber;
    
    this->table.setColour(ListBox::outlineColourId, Colours::transparentWhite);
    this->table.setColour(ListBox::backgroundColourId, Colours::transparentWhite);
    this->table.setColour(ListBox::textColourId, Colours::black);
    
    this->table.setOutlineThickness(0);
    this->table.setHeaderHeight(0);
    this->table.setRowHeight(110);
    
    this->table.getViewport()->setScrollBarsShown(true,false);
    
    addAndMakeVisible(this->table);
}


IRTableListBox::~IRTableListBox()
{
    
}


void IRTableListBox::makeTableContents()
{
    
    int width = getWidth() - 20;
    this->table.getHeader().addColumn(this->title,
                                      1,
                                      width,
                                      width,
                                      width,
                                      TableHeaderComponent::defaultFlags);
}


void IRTableListBox::resized()
{
    this->table.setBounds(0,0,getWidth(), getHeight());
}


void IRTableListBox::selectedRowsChanged(int lastRowSelected)
{
    this->status = IRTableListBoxStatus::selectedRowChanged;
    this->selectedIndex = lastRowSelected;
    sendChangeMessage();
}


void IRTableListBox::selectedRowDoubleClicked(int lastRowSelected)
{
    this->status = IRTableListBoxStatus::selectedRowDoubleClicked;
    this->selectedIndex = lastRowSelected;
    sendChangeMessage();
}


int IRTableListBox::getNumRows()
{
    return this->numRows;
}


void IRTableListBox::setNumRows(int n)
{
    this->numRows = n;
    this->table.updateContent();
}


void IRTableListBox::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected) g.fillAll(Colour::fromFloatRGBA(1,1,1,0.25));
}


void IRTableListBox::paintCell (Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    
}


int IRTableListBox::getColumnAutoSizeWidth(int columnId)
{
    int widest = 32;
    return widest;
}


void IRTableListBox::sortOrderChanged(int newSortColumnId, bool isForwards)
{
    
}


Component* IRTableListBox::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    jassert(existingComponentToUpdate == nullptr);
    return nullptr;
}


int IRTableListBox::getSelection(const int rowNumber) const
{
    return this->dataList->getChildElement(rowNumber)->getIntAttribute("Select");
}


void IRTableListBox::setSelection(const int rowNumber, const int newSelection)
{
    this->dataList->getChildElement(rowNumber)->setAttribute("Select", newSelection);
}


int IRTableListBox::getSelectedIndex() const
{
    return this->selectedIndex;
}


IRTableListBoxStatus IRTableListBox::getStatus() const
{
    return this->status;
}





