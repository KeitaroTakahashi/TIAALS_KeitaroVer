//
//  singletonClass.cpp
//  C++Singleton
//
//  Created by Keitaro Takahashi on 2018/07/05.
//  Copyright © 2018 Keitaro Takahashi. All rights reserved.
//

#include "singletonClass.hpp"


const int kMaxFinalizersSize = 256;
static int gNumFinalizersSize = 0;
static SingletonFinalizer::FinalizerFunc gFinalizers[kMaxFinalizersSize];

void SingletonFinalizer::addFinalizer(FinalizerFunc func) {
    assert(gNumFinalizersSize < kMaxFinalizersSize);
    gFinalizers[gNumFinalizersSize++] = func;
}

void SingletonFinalizer::finalize()
{
    for(int i = gNumFinalizersSize -1; i >= 0; --i) {
        (*gFinalizers[i])();
    }
    gNumFinalizersSize = 0;
}
