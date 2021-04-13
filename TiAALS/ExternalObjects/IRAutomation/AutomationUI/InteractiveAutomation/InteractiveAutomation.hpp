//
//  InteractiveAutomation.hpp
//  InteractiveAutomation - App
//
//  Created by Keitaro on 29/04/2019.
//
#ifndef InteractiveAutomation_hpp
#define InteractiveAutomation_hpp
#include "../JuceLibraryCode/JuceHeader.h"
#include <algorithm>
#include "IRUIFoundation.hpp"
#include "AutomationVertex.hpp"
#include "VertecesSelector.h"
#include "AutomationController.hpp"
#include "IRMouseGrid.h"
#include "IRMeasureGrid.hpp"

using namespace IRAutomation;

class InteractiveAutomation : public IRUIFoundation
{
public:
    
    // ==================================================
    InteractiveAutomation(IRNodeObject* nodeObject, IRStr* str);
    ~InteractiveAutomation();
    // ==================================================
    
    void paint(Graphics& g) override;
    void resized() override;
    
    void initAutomation();
    // ==================================================
    
    void mouseDown(const MouseEvent& e) override;
    void mouseDoubleClick(const MouseEvent& e) override;
    
    void mouseUp(const MouseEvent& e) override;
    void mouseMove(const MouseEvent& e) override;
    void mouseDrag(const MouseEvent& e) override;
    
    // ==================================================
    void selectAllVerteces();
    void deselectAllVerteces();
    void deleteSelectedVerteces();
    void deleteAllVerteces();
    void repaintAllverteces();
    // ==================================================
    
    bool isHitAnyVerteces(Rectangle<float> area) const;
    
    void showVerteces()
    {
        std::cout << " ========== \n";
        int index = 0;
        for(auto v : this->verteces)
        {
            std::cout << "verteces[" << index <<"] : " << v->getX() << ", " << v->getY() << std::endl;
            index++;
        }
        std::cout << " ========== \n";
        
    }
    
    // ==================================================
    
    void setMovable(bool movable, bool verticalMovable, bool horizontalMovable);
    
    void reCalcPos();
    
    // --------------------------------------------------
    Array<IRAutomationVertexComponent* > getVerteces() { return this->verteces; }
    
    // --------------------------------------------------
    // ==================================================
    
    void zoomInClicked();
    void zoomOutClicked();
    void movableClicked(IRAutomation::movableStatus status);
    void commentClicked();
    void bezierClicked(IRAutomation::lineStatus status);

    std::function<void()>zoomInClickedCallback;
    std::function<void()>zoomOutClickedCallback;
    std::function<void(IRAutomation::movableStatus status)>movableClickedCallback;
    // ==================================================

    void setVisibleArea(Rectangle<int> area);
    // ==================================================
    
    bool isCommentShow() const { return this->isCommentShowFlag; }
    void setCommentShow(bool flag) { this->isCommentShowFlag = flag; repaint(); }
    
    void paintComment(Graphics& g);
    
    bool isBezierShow() const { return this->isBezierShowFlag; }
    void setBezierShow(bool flag) { this->isBezierShowFlag = flag; repaint(); }
    void paintBezierLines(Graphics& g);
    // ==================================================

    // test
    void demoData(int num);
    
    void setDescriptor(IRDescriptorStr* data);
    
    void setPlayingLine(Rectangle<int> line) { this->playingLine = line; repaint(); }

    // ==================================================
    
    void doReCalcPos() { this->isCalcPosFlag = true; }
    void reCalcPosDone() { this->isCalcPosFlag = false; }
private:
    
    class ascendingSorter
    {
    public:
        static int compareElements (const IRAutomationVertexComponent* first, const IRAutomationVertexComponent* second)
        {
            if (first->getX() < second->getX())
                return -1;
            if (first->getX() > second->getX())
                return 1;
            return 0;
        }
    };
    
    std::shared_ptr<AutomationController> controller;
    int previousOffsetX = 0;
    Rectangle<int> visibleArea;
    
    float automation_width_ratio = 1.0;
    float automation_height_ratio = 1.0;
    
    void makeVertexBuffer();
    
    std::vector<IRAutomationVertexPos* > vertexBuffer;
    Array<IRAutomationVertexComponent* > verteces;
    Array<IRAutomationVertexComponent* > selectedVerteces;
    
    float MaxVertexValue = -999999;
    float MinVertexValue = 999999;
    
    Rectangle<int> previousBounds;
    
    std::shared_ptr<VertecesSelector> selector;
    
    void createVertex(juce::Point<float> pos, bool isSelected, bool shouldSort = true);
    
    void drawVerteces(Graphics& g);
    
    void drawLinesBetweenVerteces(Graphics& g);
    
    // ==================================================

    bool isCommentShowFlag = false;
    bool isBezierShowFlag = false;
    // ==================================================

    Rectangle<int>playingLine;

    
    // ==================================================
    
    juce::Point<int> currentMousePos {0, 0};
    
    // ==================================================
    
    IRMouseGrid mouseGrid;
    
    // ==================================================
    
    //bool keyPressed(const KeyPress &key,
      //              Component* originatingComponent) override;
    void IRKeyPressed(int keyCode,String keyText) override;
    // ==================================================
    
    bool isCalcPosFlag = true;

    // ==================================================
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InteractiveAutomation)
    
    
};
#endif /* InteractiveAutomation_hpp */
