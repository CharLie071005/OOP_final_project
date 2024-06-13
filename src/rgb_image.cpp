#include "rgb_image.h"

RGBImage::RGBImage(){
<<<<<<< HEAD
=======

>>>>>>> cb1561ebce1ec320d5394905966d7d6815604289
}

RGBImage::~RGBImage(){
    for (int i=0; i<height; ++i){
        for (int j=0; j<width; ++j){
            delete [] pixels[i][j];
        }
    }
    for (int i=0; i<height; ++i){
        delete [] pixels[i];
    }
    delete [] pixels;
}

bool RGBImage::LoadImage(string filename){
    loadfilename = filename;
    pixels = data_loader.Load_RGB(filename, &width, &height);
    return true;
}

void RGBImage::DumpImage(string filename){
    data_loader.Dump_RGB(width, height, pixels, filename);
}

void RGBImage::Display_X_Server(){
    data_loader.Display_RGB_X_Server(width, height, pixels);
}

void RGBImage::Display_ASCII(){
    data_loader.Display_RGB_ASCII(width, height, pixels);
}

void RGBImage::Display_CMD(){
    data_loader.Display_RGB_CMD(loadfilename);
}
int ***RGBImage::get_pixels(){
    return pixels;
}