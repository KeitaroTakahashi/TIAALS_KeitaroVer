//
//  IRFileManager.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 05/02/2019.
//

#ifndef IRFileManager_hpp
#define IRFileManager_hpp

#include <map>

#include "JuceHeader.h"
#include "singletonClass.hpp"
#include "DataAllocationManager.h"
#include "DataType.h"
#include "IRImage.hpp"
#include "IRAudio.hpp"
#include "KLib.h"

class FILEMAP
{
private:
    std::vector<File> fileList;
    std::vector<IRObjectPtr> pList;
    
public:
    
    std::vector<File> getFileList() const { return this->fileList; }
    std::vector<IRObjectPtr> getPList() const { return this->pList; }
    
    void clear()
    {
        this->fileList.clear();
        this->pList.clear();
    }
    
    bool add(File f, IRObjectPtr p)
    {
        this->fileList.push_back(f);
        this->pList.push_back(p);
        
        // if any confliction occurs
        if(this->fileList.size() != this->pList.size()) return false;
        
        return true;
    }
    
    bool remove(File f)
    {
        int index = findIndexOf(f);
        this->fileList.erase(this->fileList.begin() + index);
        this->pList.erase(this->pList.begin() + index);
        return true;
        
        // if any confliction occurs
        if(this->fileList.size() != this->pList.size()) return false;
    }
    
    bool remove(IRObjectPtr p)
    {
        int index = findIndexOf(p);
        
        this->fileList.erase(this->fileList.begin() + index);
        this->pList.erase(this->pList.begin() + index);
        
        std::cout << "fileList size = " << this->fileList.size() << std::endl;
        
        // if any confliction occurs
        if(this->fileList.size() != this->pList.size())
            return false;
        else return true;
    }
    
    bool isFile(File f)
    {
        for(auto _f : this->fileList)
        {
            // if the same File found in the list
            if(_f == f)
                return true;
        }
        return false;
    }
    
    
    File findFile(File f)
    {
        for(auto _f : this->fileList)
        {
            // if the same File found in the list
            if(_f == f)
                return _f;
        }
        //if nothing found
        return File();
    }
    
    IRObjectPtr findPtr(IRObjectPtr p)
    {
        int index = findIndexOf(p);
        if (index > -1) return this->pList[index];
        else return nullptr;
    }
    
    IRObjectPtr findPtrByFile(File f)
    {
        int index = findIndexOf(f);
        if (index > -1) return this->pList[index];
        else return nullptr;
    }
    
    File findFileByPtr(IRObjectPtr p)
    {
        int index = findIndexOf(p);
        if(index > -1) return this->fileList[index];
        else return File();
    }
    
    int findIndexOf(File f)
    {
        int i = 0;
        int index = -1;
        for(auto _f : this->fileList)
        {
            if(_f == f)
            {
                index = i;
                break;
            }
            i++;
        }
        
        return index;
    }
    
    int findIndexOf(IRObjectPtr p)
    {
        int i = 0;
        int index = -1;
        for(auto _p : this->pList)
        {
            if(_p == p)
            {
                index = i;
                break;
            }
            i++;
        }
        return index;
    }
    
};

/*
 
    IRFileManager should be constructed as singleton.
    This class manages all files imported on the software and avoid import the same file more than twice unless the files are modified by the program.
 
 juce::Image
 audioDataClass
 juce::VideoComponent
 TextDataClass : .txt, .csv


 */

class IRFileManager
{
public:

    IRFileManager()
    {
        clear();
    }
    
    ~IRFileManager()
    {
        
    }

    //==================================================
    // get a file pointer from IRFileManager
    // if file has not yet been loaded, then this method loads the file first and returns its pointer
    // you can set a callback function to notify the completion of importing files
    IRObjectPtr getFilePtr(IRFileType type, File file, IRObjectPtr owner);
    
    // with callback function,
    // note that we are using pointer of IRObjectPtr means double pointer in order to modify the pointer itself inside of this function and keep the results in the outside
    void getFilePtrWithCallBack(IRFileType type, File file, IRObjectPtr owner, std::string keyword, std::function<void()>callback = nullptr);

    
    IRObjectPtr discardFilePtr(IRFileType type, IRObjectPtr obj, IRObjectPtr owner, File file);
    
    //==================================================
    
    FILEMAP* getObjctList() { return &this->list; }
    
    IRObjectPtr getFileObject(std::string keyword) { return this->temporalBuffer[keyword]; }
    // get a pointer which has the corresponding keyword and then remove it from temporalBuffer.
    // note that the pointer is not deallocated!
    IRObjectPtr getFileObjectAndRemoveFromBuffer(std::string keyword)
    {
        IRObjectPtr obj = this->temporalBuffer[keyword];
        std::map<std::string,IRObjectPtr>::iterator it;
        it= this->temporalBuffer.find(keyword);
        this->temporalBuffer.erase (it);
        
        return obj;
        
    }


private:
    
    //==================================================
    // allocate data by a given FileType
    IRObjectPtr createFileData(IRFileType type, File file, IRObjectPtr owner, std::function<void()>callback = nullptr);
    void createFileDataCallback();
    IRObjectPtr createImageFileData(File file, IRObjectPtr owner);
    IRObjectPtr createAudioFileData(File file, IRObjectPtr owner, std::function<void()>callback, bool threadSafe = false);
    
    // check if the new file is already imported or not
    bool isFileAlreadyRegistered(File newFile);
    bool isObjectAlreadyRegistered(IRObjectPtr p);
    // -------------------------------------------------
    // return nullptr if object does not exist
    IRObjectPtr retrievePtrByFile(File file);
    File retrieveFileByPtr(IRObjectPtr p);
    // -------------------------------------------------
    void registerNewFile(File file, IRObjectPtr obj);
    // -------------------------------------------------
    void managerOwner(IRFileType type, IRObjectPtr obj, IRObjectPtr owner, bool addOrRemove);
    
    void IRImageReferencerManager(IRObjectPtr obj, IRObjectPtr owner, bool addOrRemove);
    void IRAudioReferencerManager(IRObjectPtr obj, IRObjectPtr owner ,bool addOrRemove);
    
    //==================================================
    void clear() { this->list.clear(); }
    
    
    //==================================================

    FILEMAP list;
    
    // dummy pointer for fileImport process with callback
    IRObjectPtr dummy;
    
    // temporalBuffer is used to store the retrieved pointer and store into distinguish memory region.
    // A keyword is given so that any objects requesting the pointer should have the correct pointer.
    std::map<std::string, IRObjectPtr > temporalBuffer;
};


#endif /* IRFileManager_hpp */
