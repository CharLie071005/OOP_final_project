#include "rgb_image.h"

RGBImage::RGBImage() : pixels(nullptr) {
    width = 0;
    height = 0;
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
    loadfilename = filename;
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
    /*  以下註解區塊目的是刪除產出的圖片檔
    std::string command = "rm -f ";
    command += loadfilename;
    int removeImage = system(command.c_str());
    if (removeImage == 0){
        std::cout << "成功刪除圖片" << endl;
    }*/
}
int ***RGBImage::get_3D_pixels(){
    return pixels;
}

RGBImage& RGBImage::operator=(Image image) {
    if (this != &image) {  //如果不是=自己  ->執行assignment
        height = image.get_height();
        width = image.get_width();
        int ***tmp_pixels = image.get_3D_pixels();

        // 刪除現有的記憶體
        if (pixels != nullptr) {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    delete[] pixels[i][j];
                }
                delete[] pixels[i];
            }
            delete[] pixels;
        }

        // 重新分配記憶體
        pixels = new int**[height];
        for (int i = 0; i < height; ++i) {
            pixels[i] = new int*[width];
            for (int j = 0; j < width; ++j) {
                pixels[i][j] = new int[3];
            }
        }

        //複製pixels值
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                for (int k = 0; k < 3; k++) {
                    pixels[i][j][k] = tmp_pixels[i][j][k];
                }
            }
        }
    }
    return *this;
}