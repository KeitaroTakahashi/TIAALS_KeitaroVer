//
//  singletonClass.hpp
//  C++Singleton
//
//  Created by Keitaro Takahashi on 2018/07/05.
//  Copyright © 2018 Keitaro Takahashi. All rights reserved.
//

#ifndef singletonClass_hpp
#define singletonClass_hpp

#include <stdio.h>
#include <iostream>

class SingletonFinalizer
{
public:
    typedef void (*FinalizerFunc)();
    static void addFinalizer(FinalizerFunc func);
    static void finalize();
};

template <typename T>
class singleton final
{
public:
    static T& get_instance()
    {
        std::call_once(initFlag, create);
        assert(instance);
        return *instance;
    }
    
    // FD ADD-ON
    static void explicitlyDestroy()
    {
        destroy();
    }

    
private:
    static void create() {
        instance = new T;
        SingletonFinalizer::addFinalizer(&singleton<T>::destroy);
    }
    
    static void destroy()
    {
        delete instance;
        instance = nullptr;
    }
    
    static std::once_flag initFlag;
    static T* instance;
};

template <typename T> std::once_flag singleton<T>::initFlag;
template <typename T> T* singleton<T>::instance = nullptr;

#endif /* singletonClass_hpp */
