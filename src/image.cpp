#include "image.h"

Image::Image(){}

Image::~Image(){}

bool Image::LoadImage(string filename){
    return true;
}

void Image::DumpImage(string filename){
    //data_loader.Dump_Gray(width, height, pixels, filename);
}

void Image::Display_X_Server(){
    //data_loader.Display_Gray_X_Server(width, height, pixels);
}

void Image::Display_ASCII(){
    //data_loader.Display_Gray_ASCII(width, height, pixels);
}

void Image::Display_CMD(){
    data_loader.Display_Gray_CMD(loadfilename);
}

int Image::get_width(){
    return width;
    //test
}

int Image::get_height(){
    return height;
}
int **Image::get_pixels(){
    return 0;
}
int ***Image::get_3D_pixels(){
    return 0;
}

void Image::List_Name_Directory(string Path, vector<string> &filenames){
    bool SetUpName = data_loader.List_Directory(Path, filenames);
    if (SetUpName != 0 ){
        std::cout << "List Directory failed " << endl;
    }
}