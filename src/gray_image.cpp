#include "gray_image.h"

GrayImage::GrayImage() : pixels(nullptr){
}
GrayImage::~GrayImage(){
    if (pixels){
        for (int i=0; i<height; i++){
            delete [] pixels[i];
        }
        delete [] pixels;
        pixels = nullptr;
    }
}

bool GrayImage::LoadImage(string filename){
    loadfilename = filename;
    if (pixels){
        for (int i=0; i<height; ++i){
            delete [] pixels[i];
        }
        delete [] pixels;
        pixels = nullptr;
    }
    pixels = data_loader.Load_Gray(filename, &width, &height);
    return true;
}

void GrayImage::DumpImage(string filename){
    loadfilename = filename;
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
    /*  the following code is usgin system() to delete the .jpg we generate
    std::string command = "rm -f ";
    command += loadfilename;
    int removeImage = system(command.c_str());
    if (removeImage == 0){
        std::cout << "成功刪除圖片" << endl;
    }*/
}
int **GrayImage::get_pixels(){
    return pixels;
}


