//
//  IRFileInspecter.cpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 11/03/2019.
//

#include "IRFileInspecter.hpp"

IRFileInspecter::IRFileInspecter():
panel("panel test")
{
    setSize(480, 640);
        
    addAndMakeVisible(panel);
}

IRFileInspecter::~IRFileInspecter()
{
    
}


void IRFileInspecter::resized()
{    
    this->panel.setBounds(10, 120, 300, 300);

}

void IRFileInspecter::paint(Graphics& g)
{
    g.fillAll(SYSTEMCOLOUR.contents.brighter());
}


void IRFileInspecter::makePropertyPanel()
{
    this->panel.clear();
    FILEMAP* list = getFileManager()->getObjctList();
    std::vector<File> fileList = list->getFileList();
    std::vector<IRObjectPtr> pList = list->getPList();
    
    std::cout << "makePropertyPanel : " << fileList.size() << "\n";
    
    for(int i = 0; i < fileList.size(); i++)
    {
        Array<PropertyComponent* > components;
        DataAllocationManager<IRImage>* obj = static_cast<DataAllocationManager<IRImage>*>(pList[i]);
        
        for(int j = 0; j < obj->getOwnerCount(); j++)
        {
            IRNodeObject* node = static_cast<IRNodeObject* >(obj->getOwnerList()[j]);
            //std::cout << "node = " << node << std::endl;
            components.add(new IRPropertyComponent(node->name, juce::Point<int>(40,0), node->getBounds()));
            //std::cout << "makePropertyPanel : " << i << " of " << fileList.size() << " : " << node->name << "\n";
        }
        this->panel.addSection(fileList[i].getFileName(), components);
    }
}

void IRFileInspecter::updatePropertyPanel()
{
    makePropertyPanel();
}
