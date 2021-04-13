//
//  ComponentExportToImage.h
//  TIAALS_LIGHT
//
//  Created by Keitaro on 16/03/2021.
//

#ifndef ComponentExportToImage_h
#define ComponentExportToImage_h
#include <JuceHeader.h>
class componentExportToImage
{
public:
    
    bool exportByDialog(Component* comp)
    {
        
        std::cout << "exportByDialog\n";
        // create new save data file with an extension of ".irimas by default
        FileChooser chooser("Save project...",
                            {},
                            "*.png");

        if (chooser.browseForFileToSave(true))
        {
            auto file = chooser.getResult();
            auto path = file.getFullPathName();
            auto filename = file.getFileName();
            
            if(file.exists())
            {
                file.deleteFile();
            }
            
            return exportTo(path, comp);
            
        }
        return false;
    }
  
    bool exportTo(String imageFileNameWithExtension, Component* comp)
    {

        File thumbFile = File(imageFileNameWithExtension);
        Image snapShot = comp->createComponentSnapshot (comp->getLocalBounds());

        // copied from jules' posting above:
        if (ImageFileFormat* format = ImageFileFormat::findImageFormatForFileExtension (thumbFile))
        {
            FileOutputStream stream (thumbFile);
            
            if (stream.openedOk())
            {
                format->writeImageToStream (snapShot, stream);
                return true;
            }
        }
        return false;
    }
    
    // scale it with newWidth
    bool exportTo(String imageFileNameWithExtension, Component* comp, int newWidth)
    {
        File thumbFile = File(imageFileNameWithExtension);
        Image snapShot = comp->createComponentSnapshot (comp->getLocalBounds());
        Image thumbnail = snapShot.rescaled (newWidth, newWidth * comp->getHeight() / comp->getWidth());

        // copied from jules' posting above:
        if (ImageFileFormat* format = ImageFileFormat::findImageFormatForFileExtension (thumbFile))
        {
         
            FileOutputStream stream (thumbFile);
            if (stream.openedOk())
            {
                format->writeImageToStream (thumbnail, stream);
                return true;
            }
        }
        return false;
    }
    
};
#endif /* ComponentExportToImage_h */
