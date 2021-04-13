//
//  IRObjectFactory2.hpp
//  IRiMaS
//
//  Created by Keitaro on 20/09/2019.
//

#ifndef IRObjectFactory2_hpp
#define IRObjectFactory2_hpp

#include "IRObjectCreater.hpp"
#include "ExternalObjectHeader.h"


class IRObjectFactory2
{
public:
    struct t_object
    {
        std::string id;
        std::string name;
        objectCategory category;
        Image img;
        
        // IRObjectCreaterBase* obj;
        std::shared_ptr<IRObjectCreaterBase> obj;
        
        t_object() {}
        ~t_object(){}
        
        // t_object(std::string id, std::string name, Image img, IRObjectCreaterBase* obj)
        t_object(std::string id, std::string name, objectCategory category, Image img, std::shared_ptr<IRObjectCreaterBase> obj)
        {
            this->id = id;
            this->name = name;
            this->category = category;
            this->img = img;
            this->obj = obj;
        }
    };
    
    
    IRObjectFactory2();
    ~IRObjectFactory2( )
    {
        
    };
    
    template<class T>
    void registerObject(std::string id, std::string name, objectCategory objectType, Image img);
    
    IRNodeObject* createObject(std::string id, Component* parent, IRStr* str);
    
    void showRegisteredObjectList();
    
    std::map<std::string, t_object> getRegisteredObjectList() const // FD leaving this here because of scope resolution design to check with t_object
    {
        return this->list;
    }
    
    std::vector<t_object*> getRegisteredObjectOfCategory(objectCategory category)
    {
        return this->registeredObjectInfo[category];
    }
private:
    
    std::map<std::string, t_object> list;
    
    std::map<objectCategory, std::vector<t_object*>> registeredObjectInfo;
    
};


// template function should be written outside of the class - FD could not put this in .cpp - to investigate further once global file separation done
template<class T>
void IRObjectFactory2::registerObject(std::string id, std::string name, objectCategory objectType, Image img)
{
    
    // now trying with shared pointer
    std::shared_ptr<IRObjectCreater<T>> obj = std::make_shared<IRObjectCreater<T>>();
    // IRObjectCreater<T>* obj = new IRObjectCreater<T>();
    // std::cout << "hallo" << std::endl;
    this->list[id] = IRObjectFactory2::t_object(id, name, objectType, img, obj);
    
    this->registeredObjectInfo[objectType].push_back(&this->list[id]);
    
    
}

#endif /* IRObjectFactory2_hpp */
