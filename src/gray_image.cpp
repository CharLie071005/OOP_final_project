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
    /*  以下註解區塊目的是刪除產出的圖片檔
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


