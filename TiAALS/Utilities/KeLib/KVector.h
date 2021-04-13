//
//  KVector.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 09/06/2019.
//

#ifndef KVector_h
#define KVector_h

#include "JuceHeader.h"

// ONLY Numerics are accepted.
template <typename T>
class KVector
{
public:
    KVector() :
    val1(0),
    val2(0),
    val3(0),
    val4(0)
    {
        
    }
    KVector(T val1, T val2, T val3, T val4)
    {
        this->val1 = val1;
        this->val2 = val2;
        this->val3 = val3;
        this->val4 = val4;
    }
    
    KVector(T val1, T val2, T val3)
    {
        this->val1 = val1;
        this->val2 = val2;
        this->val3 = val3;
        this->val4 = 0;
    }
    
    KVector(T val1, T val2)
    {
        this->val1 = val1;
        this->val2 = val2;
        this->val3 = 0;
        this->val4 = 0;
    }
    
    ~KVector()
    {
        
    }
    // ==================================================

    void operator= (KVector<T> vec)
    {
        this->val1 = vec.getVal1();
        this->val2 = vec.getVal2();
        this->val3 = vec.getVal3();
        this->val4 = vec.getVal4();
    }
    
    void operator= (Colour colour)
    {
        this->val1 = colour.getFloatRed();
        this->val2 = colour.getFloatGreen();
        this->val3 = colour.getFloatBlue();
        this->val4 = colour.getAlpha();
    }
    
    KVector<T> operator+ (KVector<T> vec)
    {
        KVector<T> result;
        
        result.setVal1(this->val1 + vec.getVal1());
        result.setVal2(this->val2 + vec.getVal2());
        result.setVal3(this->val3 + vec.getVal3());
        result.setVal4(this->val4 + vec.getVal4());

        return result;
    }
    
    KVector<T> operator- (KVector<T> vec)
    {
        KVector<T> result;
        
        result.setVal1(this->val1 - vec.getVal1());
        result.setVal2(this->val2 - vec.getVal2());
        result.setVal3(this->val3 - vec.getVal3());
        result.setVal4(this->val4 - vec.getVal4());
        
        return result;
    }
    
    KVector<T> operator* (KVector<T> vec)
    {
        KVector<T> result;
        
        result.setVal1(this->val1 * vec.getVal1());
        result.setVal2(this->val2 * vec.getVal2());
        result.setVal3(this->val3 * vec.getVal3());
        result.setVal4(this->val4 * vec.getVal4());
        return result;
    }
    
    KVector<T> operator/ (KVector<T> vec)
    {
        KVector<T> result;
        
        result.setVal1(this->val1 / vec.getVal1());
        result.setVal2(this->val2 / vec.getVal2());
        result.setVal3(this->val3 / vec.getVal3());
        result.setVal4(this->val4 / vec.getVal4());
        return result;
    }
    
    KVector<T> operator* (float scale)
    {
        KVector<T> result;
        
        result.setVal1(val1 * scale);
        result.setVal2(val2 * scale);
        result.setVal3(val3 * scale);
        result.setVal4(val4 * scale);
        
        return result;
    }
    // ==================================================

    
    T getVal1() const { return this->val1; }
    T getVal2() const { return this->val2; }
    T getVal3() const { return this->val3; }
    T getVal4() const { return this->val4; }
    
    void setVal1(T newVal) { this->val1 = newVal; }
    void setVal2(T newVal) { this->val2 = newVal; }
    void setVal3(T newVal) { this->val3 = newVal; }
    void setVal4(T newVal) { this->val4 = newVal; }

    // ==================================================

    void show()
    {
        std::cout << val1 << ", " << val2 << ", " << val3 << ", " << val4 << std::endl;
    }
private:
    
    T val1, val2, val3, val4;
    // ==================================================

};

#endif /* KVector_h */
