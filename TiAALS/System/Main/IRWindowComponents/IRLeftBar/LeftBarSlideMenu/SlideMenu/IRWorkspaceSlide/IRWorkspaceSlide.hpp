//
//  IRWorkspaceSlide.hpp
//  IRiMaS
//
//  Created by Keitaro on 17/09/2019.
//

#ifndef IRWorkspaceSlide_hpp
#define IRWorkspaceSlide_hpp

#include "JuceHeader.h"
#include "IRStrComponent.hpp"
#include "IRWorkspace2.hpp"
#include "IRiMaSHeader.h"


class IRWorkspaceSlide : public Component,
public IRStrComponent
{
public:
    IRWorkspaceSlide(IRStr* str, int index, IRWorkspace* space);
    ~IRWorkspaceSlide();
    // ==================================================

    void paint(Graphics& g) override;
    
    void mouseDown(const MouseEvent& e) override;
    void mouseUp(const MouseEvent& e) override;

    std::function<void(IRWorkspaceSlide*)> onClick = nullptr;
    std::function<void(IRWorkspaceSlide*)> slideSwitchedCallback = nullptr;

    // ==================================================
    void deleteThisWorkspace();
    // ==================================================
    void setIndex(int newIndex);
    int getIndex() const { return this->index; }
    // ==================================================

    bool updateThumbnail();
    // ==================================================

    void setSelectedFlag(bool flag) { this->isSelectedFlag = flag; repaint(); }
    bool isSelected() const { return this->isSelectedFlag; }
    // ==================================================
    
    IRWorkspace* getWorkspace() { return this->space; }
    
    // ==================================================
    static bool compBy  (IRWorkspaceSlide* a, IRWorkspaceSlide* b)
    {
        return (a->index < b->index);
    }

    String getThumbnailURL() const { return this->thumbnailURL; }
private:
    
    IRWorkspace* space;
    int index;
    bool isSelectedFlag = false;
    Image thumbnail;
    // ==================================================
    String thumbnailURL;
    // ==================================================
    Image drawTextIntoImage();
    // ==================================================

    Image loadImage()
    {
        this->thumbnailURL = String(URL_WORKSPACE_SLIDE_PICTURE) + "workspace_" + String(index-1) + ".png";
        std::cout << this->thumbnailURL << std::endl;
        return ImageFileFormat::loadFrom(File(this->thumbnailURL));
    }
    
    // ==================================================

};
#endif /* IRWorkspaceSlide_hpp */
