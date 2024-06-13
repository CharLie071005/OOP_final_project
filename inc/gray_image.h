#ifndef GRAY_IMAGE_H
#define GRAY_IMAGE_H

#include "image.h"

class GrayImage : public Image{
private:
    int **pixels;
public:
    GrayImage();
    ~GrayImage();
    bool LoadImage(string filename) override;
    void DumpImage(string filename) override;
    void Display_X_Server() override;
    void Display_ASCII() override;
    void Display_CMD() override;
};

#endif