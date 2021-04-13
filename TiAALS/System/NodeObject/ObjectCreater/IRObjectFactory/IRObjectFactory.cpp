
#include "IRObjectFactory.hpp"




IRObjectFactory::IRObjectFactory()
{
    
}

/*
IRObjectFactory::~IRObjectFactory()
{
    
}
 */


IRNodeObject* IRObjectFactory::createObject(std::string id, Component* parent, IRStr* str)
{
    return this->list[id].obj->create(parent, str);
}


void IRObjectFactory::showRegisteredObjectList()
{
    std::cout << "showRegisteredObjectList" << std::endl;
    for (auto item : this->list)
    {
        std::cout << item.first << std::endl;
    }
}




