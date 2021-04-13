//
//  ObjectListMenuObject.cpp
//  NodeComponentObject_Study - App
//
//  Created by Frédéric Dufeu on 27/02/2019.
//

#include "ObjectListMenuObject.hpp"




ObjectListMenuObject::ObjectListMenuObject(String title, int rowNumber) : IRTableListBox(title, rowNumber)
{
    makeCells();
    setNumRows((int)this->cells.size());
}


ObjectListMenuObject::~ObjectListMenuObject()
{
    for (auto item : this->cells)
    {
        delete item;
    }
}


Component* ObjectListMenuObject::refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    if (columnId == 1)
    {
        if(existingComponentToUpdate != nullptr)
        {
            delete existingComponentToUpdate;
        }
        auto* cell = this->cells[rowNumber]->copy();
        return cell;
    }
    
    jassert(existingComponentToUpdate == nullptr);
    return nullptr;
}


void ObjectListMenuObject::makeCells()
{
    
    this->cells.clear();
    
    std::map<std::string, IRObjectFactory::t_object> list = IRFactory.getRegisteredObjectList();
    
    int index = 1;
    this->idBank.push_back(""); // dummy
    for (auto &obj : list)
    {
        CellComponent* cell = new CellComponent(obj.second.name,
                                                obj.second.id,
                                                index,
                                                *this);
        this->cells.push_back(cell);
        this->idBank.push_back(obj.second.id);
        
        index++;
    }
}


std::vector<std::string> ObjectListMenuObject::getIdBank() const
{
    return this->idBank;
}




