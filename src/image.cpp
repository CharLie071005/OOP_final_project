#include "image.h"

<<<<<<< HEAD
Image::Image(
){}
=======
Image::Image(){
    height =0;
    width =0;
}

Image::Image(int _h, int _w) {
    height = _h;
    width = _w;
}
>>>>>>> Factor2_Ou

Image::~Image(){}

bool Image::LoadImage(string filename){
<<<<<<< HEAD
    cout << "Load Image's Load Image\n";
=======
    //cout << "LoadImage" << filename  << "  at Image.cpp" <<endl;
>>>>>>> Factor2_Ou
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