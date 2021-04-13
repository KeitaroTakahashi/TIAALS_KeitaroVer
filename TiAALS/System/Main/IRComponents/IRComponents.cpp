//
//  IRComponents.cpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 14/04/2019.
//

#include "IRComponents.hpp"

void IRComponents::createFileManager()
{
    this->fileManager = new IRFileManager();
}

void IRComponents::deleteFileManager()
{
    delete this->fileManager;
}

void IRComponents::setIRFileManager(IRFileManager* manager)
{
    this->fileManager = manager;
    if(this->fileManagerUpdated != nullptr) this->fileManagerUpdated(this->fileManager);

}
