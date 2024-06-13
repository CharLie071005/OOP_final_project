#ifndef _GRAY_IMAGE_H_
#define _GRAY_IMAGE_H_

#include "image.h"

class GrayImage : public Image{
private:
    int **pixels;
public:
    GrayImage();
    ~GrayImage();
    bool LoadImage(string filename);
    void DumpImage(string filename);
    void Display_X_Server();
    void Display_ASCII();
    void Display_CMD();
    int **get_pixels(); //���F��filter�ϥ�pixels
    void showPixels();
};

#endif