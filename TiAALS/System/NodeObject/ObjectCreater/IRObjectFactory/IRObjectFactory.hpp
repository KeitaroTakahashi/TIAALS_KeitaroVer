
#ifndef IRObjectFactory_hpp
#define IRObjectFactory_hpp


#include "IRObjectCreater.hpp"




class IRObjectFactory
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
    
    
    IRObjectFactory();
    ~IRObjectFactory() // won't be called as is singleton?
    {
        // std::cout << "destructor of IRObjectFactory called" << std::endl; // I NEED FOR THIS TO HAPPEN...
    };
    
    template<class T>
    void registerObject(std::string id, std::string name, objectCategory objectType, Image img)
    {
        
        // now trying with shared pointer
        std::shared_ptr<IRObjectCreater<T>> obj = std::make_shared<IRObjectCreater<T>>();
        this->list[id] = IRObjectFactory::t_object(id, name, objectType, img, obj);
        
        this->registeredObjectInfo[objectType].push_back(&this->list[id]);
        std::cout<< id << " registered : size is " << this->list.size() << std::endl;
    }
    
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


#endif /* IRObjectFactory_hpp */
