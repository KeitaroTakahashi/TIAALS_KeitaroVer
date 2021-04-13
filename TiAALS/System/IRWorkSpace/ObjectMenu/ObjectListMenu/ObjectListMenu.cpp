
#include "ObjectListMenu.hpp"




ObjectListMenu::ObjectListMenu(Component* parent, Rectangle<int>frameRect) : MenuObject(parent)
{
    this->frameRect = frameRect;
    setSize(frameRect.getWidth(), frameRect.getHeight());
    this->menu = new ObjectListMenuObject("Object List", 13);
    setListBoxComponent(this->menu);
}


ObjectListMenu::~ObjectListMenu()
{
    delete menu;
}


void ObjectListMenu::paint(Graphics& g)
{
    MenuObject::paint(g);
    //g.fillAll(SYSTEMCOLOUR.contents);
    
    auto area = getLocalBounds().reduced (2);
    
    g.setColour(SYSTEMCOLOUR.contents.brighter());
    g.fillRoundedRectangle (area.toFloat(), 5.0f);
    
}


void ObjectListMenu::resized()
{
    MenuObject::resized();
}


void ObjectListMenu::selectedItemChanged(int itemIndex)
{
    std::cout << itemIndex << std::endl;
    this->selectedIndex = itemIndex;
    this->selectedID = this->menu->getIdBank()[itemIndex];
    callItemSelectionAction();
}


void ObjectListMenu::selectedItemDoubleClicked(int itemIndex)
{
    std::cout << "double clicked = " <<itemIndex << std::endl;
    this->selectedIndex = itemIndex;
    this->selectedID = this->menu->getIdBank()[itemIndex];
    callItemHasSelectedAction();
}


void ObjectListMenu::menuScrolled()
{
    //repaint();
}


int ObjectListMenu::getSelectedIndex() const
{
    return this->selectedIndex;
}


std::string ObjectListMenu::getSelectedId() const
{
    return this->selectedID;
}


void ObjectListMenu::addListener(Listener* newListener)
{
    this->listeners.add(newListener);
}


void ObjectListMenu::removeListener(Listener* listener)
{
    this->listeners.remove(listener);
}


void ObjectListMenu::callItemSelectionAction()
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if (checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.itemSelectionAction(this); });
    //check again
    if (checker.shouldBailOut()) return;
}


void ObjectListMenu::callItemHasSelectedAction()
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.itemHasSelectedAction(this); });
    //check again
    if(checker.shouldBailOut()) return;
}




