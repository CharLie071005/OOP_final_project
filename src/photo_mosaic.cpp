#include "photo_mosaic.h"

PhotoMosaic::PhotoMosaic(){}

PhotoMosaic::~PhotoMosaic(){}

array<int, 3> PhotoMosaic::CalculateAverage(RGBImage image){
    int width = image.get_width(), height = image.get_height();
    int avgR =0, avgG =0, avgB =0, count =0;
    int ***_pixels = image.get_3D_pixels();
    for (int y =0; y < height; ++y){
        for (int x =0; x < width; ++x)[
            avgR += _pixels[y][x][0];
            avgG += _pixels[y][x][1];
            avgB += _pixels[y][x][2];
            count++;
        ]
    }
    array<int ,3> arr;
    arr[0] = avgR / count;
    arr[1] = avgG / count;
    arr[2] = avgB / count;
    return arr;
}

Image *PhotoMosaic::InputFile(const string &Bigphoto, const string &MinDir){
    image.LoadImage(Bigphoto);

    if(!image.List_Directory(MinDir, small_name)){
        cout << "Open file failed\n";
        exit(1);
    }
    for (auto name : small_name){
        RGBImage img;
        img.LoadImage(name);
        small_image.push_back(img);
        small_avg.push_back(CalculateAverage(img));
    }
    subheight = small_image[0].get_height(); 
    subwidth = small_image[0].get_width();
}

void PhotoMosaic::SplitImage(){
    int ny = image.get_height() / subheight;
    int nx = image.get_width() / subwidth;
    for (int i =0; i < ny; ++i){
        for (int j =0; j < nx; ++j){
            RGBImage splited(subheight, subwidth);
            int ***split_pixels = splited.get_3D_pixels();
            int ***splo
            for (int i = 0; i < subheight; i++) {
                _pixels[i] = new int*[subwidthw];
                for (int j = 0; j < subwidthw; j++) {
                    filtered_pixels[i][j] = new int[3];
                }
            }

        }
    }
}
void PhotoMosaic::CreateGridImage(){

}

RGBImage PhotoMosaic::GenerateMosaic(){
    return 0;
}