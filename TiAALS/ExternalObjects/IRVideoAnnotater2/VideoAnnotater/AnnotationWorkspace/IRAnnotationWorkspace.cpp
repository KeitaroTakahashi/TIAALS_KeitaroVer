//
//  IRAnnotationWorkspace.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 13/04/2021.
//

#include "IRAnnotationWorkspace.hpp"
IRAnnotationWorkspace::IRAnnotationWorkspace(String title,
                        Rectangle<int> draggableMargin,
                        IRStr* str,
                        int index) :
IRWorkspaceComponent(title, draggableMargin, str, index)
{
    
}

IRAnnotationWorkspace::~IRAnnotationWorkspace()
{
    
}

// --------------------------------------------------

void IRAnnotationWorkspace::loadThisFromSaveData(json11::Json saveData)
{
    auto appearance = saveData["Appearance"];
    auto ap = appearance["aspectRatio"].array_items();
    Rectangle<float> aspectRatio = Rectangle<float>(0,0,ap[0].number_value(), ap[1].number_value());
    setUserDefinedRatio(aspectRatio);
    
    setZoomRatio(1.0);
    
    json11::Json Objects = saveData["Objects"];
    json11::Json::array objectArray = Objects.array_items();


    for (int i = 0; i < objectArray.size(); i++) // for each item of the array...
    {
        for (auto it = objectArray[i].object_items().cbegin(); it != objectArray[i].object_items().cend(); ++it)
        {
            
            std::cout << " ===== " << it->first << " ===== " << std::endl;
            
            // ===== create object =====
            std::string objectTypeId = it->second["objectType"].string_value();
            
            //IRNodeObject* obj = static_cast<IRNodeObject*>(getStr()->createNewObject(objectTypeId, this, getStr()));
            IRNodeObject* obj = createObjectFromId(objectTypeId, this);
            
            std::cout << objectTypeId << " created : " << obj << std::endl;

            
            json11::Json arrangeCtl = it->second["ArrangeController"];
            obj->setZoomRatio(1.0);
            obj->loadArrangeControllerSaveData(arrangeCtl);

            createObject(obj);

            // load save dada
            obj->loadThisFromSaveData(it->second["ObjectDefined"]);
            
            // ===== END =====
        }
    }
    setZoomRatio(1.0);

    
}


IRNodeObject* IRAnnotationWorkspace::createObjectFromId(String id, IRWorkspaceComponent* parent)
{
    if ( id == "IRTextEditor")
    {
        return createTextObjectFromId(parent);
    }else if( id == "IRShape")
    {
        return createShapeObjectFromId(parent);
    }else if( id == "IRImageViewer")
    {
        return createImageObjectFromId(parent);
    }else return nullptr;
    
}
IRNodeObject* IRAnnotationWorkspace::createTextObjectFromId(IRWorkspaceComponent* parent)
{
    return IRObjectCreater<IRVNTextEditorObject>().create(parent, parent->getStr());
}
IRNodeObject* IRAnnotationWorkspace::createShapeObjectFromId(IRWorkspaceComponent* parent)
{
    return IRObjectCreater<IRVNShapeObject>().create(parent, parent->getStr());
}
IRNodeObject* IRAnnotationWorkspace::createImageObjectFromId(IRWorkspaceComponent* parent)
{
    return IRObjectCreater<IRVNImageViewerObject>().create(parent, parent->getStr());
}
