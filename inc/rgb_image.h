#ifndef RGB_IMAGE_H
#define RGB_IMAGE_H

#include "image.h"

class RGBImage : public Image{
private:
    int ***pixels;
public:
    RGBImage();
    ~RGBImage();
    bool LoadImage(string filename) override;
    void DumpImage(string filename) override;
    void Display_X_Server() override;
    void Display_ASCII() override;
    void Display_CMD() override;

};

#endif