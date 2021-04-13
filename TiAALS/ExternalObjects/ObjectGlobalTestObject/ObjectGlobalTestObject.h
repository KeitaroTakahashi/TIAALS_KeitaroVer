//
//  ObjectGlobalTestObject.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 07/09/2018.
//

#ifndef ObjectGlobalTestObject_h
#define ObjectGlobalTestObject_h

class ObjectGlobalTestObject : public IRNodeObject
{
public:
    ObjectGlobalTestObject(Component* parent, IRStr* str, IRBoundType boundType = IRBoundType::ABSOLUTE) : IRNodeObject(parent, "ObjectGlobal", str)
    {
        setSize(100, 100);
        
        addAndMakeVisible(&this->addButton);
        this->addButton.setButtonText("addObject");
        this->addButton.setColour(TextButton::buttonColourId, getStr()->SYSTEMCOLOUR.contents);
        this->addButton.onClick = [this] {addButtonClicked();};
        
        if(isEditMode()) this->addButton.setEnabled(false);
        else this->addButton.setEnabled(true);
        
        childComponentManager(&this->addButton);
        this->addButton.setBounds(5,5, 90, 40);

        
        addAndMakeVisible(&this->getButton);
        this->getButton.setButtonText("getButton");
        this->getButton.setColour(TextButton::buttonColourId, getStr()->SYSTEMCOLOUR.contents);
        this->getButton.onClick = [this] {getButtonClicked();};
        
        if(isEditMode()) this->getButton.setEnabled(false);
        else this->getButton.setEnabled(true);
        
        childComponentManager(&this->getButton);
        this->getButton.setBounds(5,45, 90, 40);

    }
    
    ~ObjectGlobalTestObject() {}
    
    // ------------------------------------------------------------
    
    void resized() override
    {
        this->addButton.setBounds(5,5, 90, 40);
        this->getButton.setBounds(5,45, 90, 40);
    }
    void paint(Graphics& g) override
    {
        // empty!
    }
    
    // ------------------------------------------------------------
    // call back function automatically called when the status of this object changed by others.
    // write some tasks here
    void statusChangedCallback(IRNodeComponentStatus status) override
    {
        switch (status)
        {
            case EditModeStatus:
                if(isEditMode()) this->addButton.setEnabled(false);
                else this->addButton.setEnabled(true);
                
                if(isEditMode()) this->getButton.setEnabled(false);
                else this->getButton.setEnabled(true);
                break;
            case SelectableStatus:
                break;
            default:
                break;
        }
    }
    
    void addButtonClicked()
    {
        float* test = new float [10];
        
        std::string stringTest = "This is a test.";
        
        for(int i=0;i<10;i++){
            test[i] = (float)i * 0.01;
        }

        //this->callAddObjectGlobal(static_cast<IRObjectPtr>(&stringTest), this->id);
    }
    
    void getButtonClicked()
    {
        IRObjectPtr val = nullptr;
        
        //get pointer of the data
        //val = this->callGetObjectGlobal(this->id);
        
        // if success
        if(val != nullptr){
            //float* test = static_cast<float* >(val);
            char* test = static_cast<char*>(val);
            for(int i=0;i<10;i++){
                //std::cout << test[i] << std::endl;
            }
            
            puts(test);
            std::cout << *test << std::endl;
        }
    }
    
private:
    TextButton addButton;
    TextButton getButton;
    
    String id = "kayatakahashi";
};

#endif /* ObjectGlobalTestObject_h */
