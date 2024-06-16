#ifndef _RGB_IMAGE_H_
#define _RGB_IMAGE_H_

#include "image.h"

class RGBImage : public Image{
private:
    int ***pixels;
public:
    RGBImage();
    RGBImage(int _h, int _w);
    ~RGBImage();
    bool LoadImage(string filename);
    void DumpImage(string filename);
    void Display_X_Server();
    void Display_ASCII();
    void Display_CMD();
    //add function
    int ***get_3D_pixels();
};

#endif