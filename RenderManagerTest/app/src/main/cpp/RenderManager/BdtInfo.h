#include "../Jni/Device.hpp"

#ifndef BDT_INFO_HPP
#define BDT_INFO_HPP

#define GL_BGRA 0x80E1 //24비트

typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned int UINT;
typedef long LONG;

class BDTImage {
public:
    int width, height;
    GLint component;
    GLenum format;
    unsigned char* bits;
    int bitsize;
    int bisizeimage;
    int bitcount;
    BDTImage(std::string fileName);
    ~BDTImage();
    friend BDTImage* BDTLoad(std::string fileName);
};
BDTImage* BDTLoad(std::string fileName);


#endif //BDT_INFO_HPP
