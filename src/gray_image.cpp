#include "gray_image.h"

GrayImage::GrayImage(){
}

GrayImage::~GrayImage(){
    for (int i=0; i<height; ++i){
        delete [] pixels[i];
    }
    delete [] pixels;
}

bool GrayImage::LoadImage(string filename){
    loadfilename = filename;
    pixels = data_loader.Load_Gray(filename, &width, &height);
    return true;
}

void GrayImage::DumpImage(string filename){
    data_loader.Dump_Gray(width, height, pixels, filename);
}

void GrayImage::Display_X_Server(){
    data_loader.Display_Gray_X_Server(width, height, pixels);
}

void GrayImage::Display_ASCII(){
    data_loader.Display_Gray_ASCII(width, height, pixels);
}

void GrayImage::Display_CMD(){
    data_loader.Display_Gray_CMD(loadfilename);
}
int **GrayImage::get_pixels(){
    return pixels;
}