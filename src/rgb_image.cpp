#include "rgb_image.h"

RGBImage::RGBImage() : Image(0,0){
    pixels = nullptr;
}

RGBImage::RGBImage(int _h, int _w){
    width = _w;
    height = _h;   
    pixels = new int **[height];
    for (int i=0; i < height; ++i){
        pixels[i] = new int*[width];
        for (int j=0; j < _w; ++j){
            pixels[i][j] = new int [3];
        }
    }
    for (int i =0; i < _h; ++i){
        for (int j =0; j < _w; ++j){
            pixels[i][j][0] = 0;
            pixels[i][j][1] = 0;
            pixels[i][j][2] = 0;
        }
    }
}

RGBImage::~RGBImage(){
    if (pixels) {
        for (int i = 0; i < height; ++i) {
            if (pixels[i]) {
                for (int j = 0; j < width; ++j) {
                    delete[] pixels[i][j];
                }
                delete[] pixels[i];
            }
        }
        delete[] pixels;
    }
}

bool RGBImage::LoadImage(string filename){
    loadfilename = filename;
    //cout << "Load " << filename << "  In rgb_image.cpp" <<endl;

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
    /*  the following code is usgin system() to delete the .jpg we generate
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
