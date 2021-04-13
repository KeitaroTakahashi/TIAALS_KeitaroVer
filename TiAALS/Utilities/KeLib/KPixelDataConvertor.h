//
//  KPixelDataConvertor.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 07/02/2019.
//

#ifndef KPixelDataConvertor_h
#define KPixelDataConvertor_h
#include "JuceHeader.h"
/*
#include <opencv.hpp>
#include <opencv2/opencv.hpp>
#include <highgui.hpp>

#include "IRFoundation.h"



// new pixel format by Keitaro
class NonCopyingImageType : public ImageType
{
public:
    NonCopyingImageType(){}
    ~NonCopyingImageType(){}
    // --------------------------------------------------
    // the contents of this method should be written in the cpp file as it instantiates NonCopyingPixelData
    ImagePixelData::Ptr create (Image::PixelFormat format, int width, int height, bool clearImage) const override;
    
    void setData(uint8* data)
    {
        this->data = data;
    }
    
    // --------------------------------------------------
    int getTypeID() const override
    {
        return 101;
    }
    
private:
    uint8* data;
};

class KPixelDataConvertor
{
    
public:
    
    KPixelDataConvertor()
    {
        
    }
    
    ~KPixelDataConvertor() {}
    // --------------------------------------------------

    Image* Mat2Image(cv::Mat *m)
    {
        switch (m->channels())
        {
            case 3: // RGB
                return Mat2Image_RGB(m);
                break;
            case 4: // ARGB
                return nullptr;
                break;
            case 1: // GreyScale
                return nullptr;
                break;
            default:
                return nullptr;
                break;
        }
        
        
        //m->data;
    }
    // --------------------------------------------------

    Image* Mat2Image_RGB(cv::Mat *m)
    {
        int w = m->cols;
        int h = m->rows;
        int chan = m->channels();
        
       // const size_t numBytes = w * h * chan;
        //std::cout << "mat size = " << w << ", " << h << " : bytes = " << numBytes << std::endl;

        // create non copying image type
        NonCopyingImageType* type = new NonCopyingImageType();
        // set row data
        type->setData(m->data);
        
        //Ptr important!
        ImagePixelData::Ptr pixelData = type->create(Image::PixelFormat::RGB, w, h, true);
        
        ReferenceCountedObjectPtr<ImagePixelData> pd = static_cast<ReferenceCountedObjectPtr<ImagePixelData>> (pixelData);
        Image* img = new Image(pixelData);
        
        return img;
        
    }
    // --------------------------------------------------

    void Mat2Image_ARGB(Image* img, cv::Mat *m)
    {
        
    }
    // --------------------------------------------------

    void Image2Mat(cv::Mat *m, Image *img)
    {
        
    }
    
    // --------------------------------------------------


    
    
    
};
 */

#endif /* KPixelDataConvertor_h */
