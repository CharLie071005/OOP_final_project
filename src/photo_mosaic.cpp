#include "photo_mosaic.h"
#include "rgb_image.h"
PhotoMosaic::PhotoMosaic(){};

PhotoMosaic::~PhotoMosaic(){};

int ***PhotoMosaic::CalculateAverage(Image image) {
    int sumR = 0, sumG = 0, sumB = 0, count = 0;
    int _h = image.get_height(), _w = image.get_width();
    int ***_pixels = image.get_3D_pixels(); 

    for (int y = 0; y < _h; ++y) {
        for (int x = 0; x < _w; ++x) {
            sumR += _pixels[y][x][0];
            sumG += _pixels[y][x][1];
            sumB += _pixels[y][x][2];
            ++count;
        }
    }
    int avgR = sumR / count;
    int avgG = sumG / count;
    int avgB = sumB / count;
    for (int i=0; i < _h; ++i){
        for (int j=0; j < _w; ++j){
            _pixels[i][j][0] = avgR;
            _pixels[i][j][1] = avgG;
            _pixels[i][j][2] = avgB;
        }
    }
    return _pixels;
}



Image *PhotoMosaic::InputImage(string BigPhotoName, string Mnist_Folder){
    //Load the Target Photo, store as Pointer
    Image *img1 = new RGBImage();  
    img1->LoadImage("Image-Folder/mnist/img_100.jpg");
    
    //Construct the vector that store the name of mnists
    image.List_Name_Directory(Mnist_Folder, small_name);
    //Load every mnists and calculate the average value of every channel
    for (auto name : small_name ){
        Image mni;
        mni.LoadImage(name);
        small_avg.push_back(CalculateAverage(mni));
        small_image.push_back(mni);
    }
    return img1;

}



void PhotoMosaic::Matching(){

}


void PhotoMosaic::Generate_Mosaic(){

}
