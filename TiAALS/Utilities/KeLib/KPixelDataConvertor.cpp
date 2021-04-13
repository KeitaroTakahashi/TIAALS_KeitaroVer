//
//  KPixelDataConvertor.cpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 13/02/2019.
//

#include "KPixelDataConvertor.h"

// new ImagePixelData format by Keitaro
/*
 You must be careful to use this pixel data because this pixel data format only has a pointer of the input data.
 When the input data is deallocated or switched to another, any crash or further errors may be caused.
 
 */

/*
class NonCopyingPixelData : public ImagePixelData
{
public:
    NonCopyingPixelData(Image::PixelFormat formatToUse, int w, int h, bool clearImage):
    ImagePixelData(formatToUse, w, h),
    pixelStride (formatToUse == Image::RGB ? 3 : ((formatToUse == Image::ARGB) ? 4 : 1)),
    lineStride ((pixelStride * jmax (1, w) + 3) & ~3)
    
    {
        // data is not copied!
        //imageData.allocate ((size_t) lineStride * (size_t) jmax (1, h), clearImage);
        //this->imageData = calloc(sizeof(lineStride * (size_t) jmax (1, h)), sizeof(uint8));
        
        //std::cout << "stride " << pixelStride << ", " << lineStride << std::endl;
    }
    
    void setData(uint8* data)
    {
        // convert uint8* to HeapBlock<uint8>
        this->imageData = data;
    }
    
    LowLevelGraphicsContext* createLowLevelContext() override
    {
        sendDataChangeMessage();
        return new LowLevelGraphicsSoftwareRenderer (Image (*this));
    }
    
    void initialiseBitmapData (Image::BitmapData& bitmap, int x, int y, Image::BitmapData::ReadWriteMode mode) override
    {
        bitmap.data = this->imageData; //imageData + (size_t) x * (size_t) pixelStride + (size_t) y * (size_t) lineStride;
         bitmap.pixelFormat = pixelFormat;
         bitmap.lineStride = lineStride;
         bitmap.pixelStride = pixelStride;
                 
         if (mode != Image::BitmapData::readOnly)
         sendDataChangeMessage();
    }
    
    ImagePixelData::Ptr clone() override
    {
        auto s = new NonCopyingPixelData (pixelFormat, width, height, false);
        memcpy (s->imageData, imageData, (size_t) lineStride * (size_t) height);
        return *s;
        return nullptr;
    }
    
    ImageType* createType() const override {
        return new NonCopyingImageType();
    };
    
private:
    //HeapBlock<uint8> imageData;
    uint8* imageData;
    const int pixelStride, lineStride;
    
};

// NonCopyingImageType method contents here!!
ImagePixelData::Ptr NonCopyingImageType::create (Image::PixelFormat format, int width, int height, bool clearImage) const
{
    NonCopyingPixelData* n = new NonCopyingPixelData(format, width, height, clearImage);
    n->setData(this->data);
    return *n;
}
*/
