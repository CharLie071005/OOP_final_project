#include "photo_mosaic.h"
<<<<<<< HEAD

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

=======
#include "rgb_image.h"
#include <limits>
#include <cmath>
#include <iostream>

// Constructor
PhotoMosaic::PhotoMosaic() {
    simage_number = 0;
}

// Destructor
PhotoMosaic::~PhotoMosaic() {
    delete [] avgR_tar_grid;
    avgR_tar_grid = nullptr;
    delete [] avgG_tar_grid;
    avgG_tar_grid = nullptr;
    delete [] avgB_tar_grid;
    avgB_tar_grid = nullptr;
    delete [] avgR_small;
    avgR_small = nullptr;
    delete [] avgG_small;
    avgG_small = nullptr;
    delete [] avgB_small;
    avgB_small = nullptr;
}

RGBImage *PhotoMosaic::InputPath(const string& Bigphoto, const string &cifarDir){
    tarimage.LoadImage(Bigphoto);
    data_loader.List_Directory(cifarDir, sub_name);
    this->readSubImage();
    int tile_width = tarimage.get_width() / SUB_PIC_SIZE;
    int tile_height = tarimage.get_height() / SUB_PIC_SIZE;
    avgR_tar_grid = new int [tile_height * tile_width];
    avgG_tar_grid = new int [tile_height * tile_width];
    avgB_tar_grid = new int [tile_height * tile_width];
    return &tarimage;
}

void PhotoMosaic::readSubImage(){
    for(auto name : sub_name){
        RGBImage img;
        small_img[simage_number].LoadImage(name);
        simage_number++;
    }
    avgR_small = new int [simage_number];
    avgG_small = new int [simage_number];
    avgB_small = new int [simage_number];

}


// Calculate the average color of an image
void PhotoMosaic::Calculate_SmallAverage() {
    for (int index =0; index < simage_number; ++index){
        for (int y = 0; y < SUB_PIC_SIZE; ++y) {
            for (int x = 0; x < SUB_PIC_SIZE; ++x) {
                avgR_small[index] += small_img[index].get_3D_pixels()[y][x][0];
                avgG_small[index] += small_img[index].get_3D_pixels()[y][x][1];
                avgB_small[index] += small_img[index].get_3D_pixels()[y][x][2];
            }
        }
        avgR_small[index] /= SUB_PIC_SIZE * SUB_PIC_SIZE;
        avgG_small[index] /= SUB_PIC_SIZE * SUB_PIC_SIZE;
        avgB_small[index] /= SUB_PIC_SIZE * SUB_PIC_SIZE;
    }
}

void PhotoMosaic::Calculate_TarAverage() {
    int index = 0;
    int height = tarimage.get_height(), width = tarimage.get_width();
    for (int n_y =0; n_y <= height - SUB_PIC_SIZE; n_y += SUB_PIC_SIZE){
        for (int n_x =0; n_x <= width - SUB_PIC_SIZE; n_x += SUB_PIC_SIZE){
            int sumR =0, sumG = 0, sumB =0;
            //run the tarpixels int the range of (n_x, n_y) to (n_x + 32, n_y + 32)
            for (int y = n_y; y < SUB_PIC_SIZE + n_y; ++y) {
                for (int x = n_x; x < SUB_PIC_SIZE + n_x; ++x) {
                    sumR += tarimage.get_3D_pixels()[y][x][0];
                    sumG += tarimage.get_3D_pixels()[y][x][1];
                    sumB += tarimage.get_3D_pixels()[y][x][2];
                }
            }
            sumR /= SUB_PIC_SIZE * SUB_PIC_SIZE;
            sumG /= SUB_PIC_SIZE * SUB_PIC_SIZE;
            sumB /= SUB_PIC_SIZE * SUB_PIC_SIZE;

            avgR_tar_grid[index] = sumR;
            avgG_tar_grid[index] = sumG;
            avgB_tar_grid[index] = sumB;
            index++;
        }
    }
}

// Find the best match index based on the average color
void PhotoMosaic::getBestMatchIndex() {
    int tile_width = tarimage.get_width() / SUB_PIC_SIZE;
    int tile_height = tarimage.get_height() / SUB_PIC_SIZE;
    for (int y =0; y < tile_height * tile_width; ++y){
        int bestIndex = 0;
        double minDist = std::numeric_limits<double>::max();
        for (int j =0; j < simage_number; ++j){
            double r_diff = avgR_tar_grid[y] - avgR_small[j];
            double g_diff = avgG_tar_grid[y] - avgG_small[j];
            double b_diff = avgB_tar_grid[y] - avgB_small[j];
            double diff = sqrt(r_diff * r_diff + g_diff * g_diff + b_diff * b_diff);
        
            if (diff < minDist){
                minDist = diff;
                bestIndex = j;
            }
>>>>>>> Factor2_Ou
        }
        Best_fit_index.push_back(bestIndex);
    }
<<<<<<< HEAD
=======

>>>>>>> Factor2_Ou
}
void PhotoMosaic::CreateGridImage(){

}

<<<<<<< HEAD
RGBImage PhotoMosaic::GenerateMosaic(){
    return 0;
}
=======
// Generate the mosaic image
RGBImage *PhotoMosaic::Generate_Mosaic() {
    int height = tarimage.get_height(), width = tarimage.get_width();
    RGBImage *Mosaic = new RGBImage(height , width);  //remember to delete this in main.cpp
    Calculate_TarAverage();
    Calculate_SmallAverage();
    int ***_pixels = Mosaic->get_3D_pixels();
    int index =0;
    for (int n_y =0; n_y <= height - SUB_PIC_SIZE; n_y += SUB_PIC_SIZE){
        for (int n_x =0; n_x <= width - SUB_PIC_SIZE; n_x += SUB_PIC_SIZE){
            int *** best_pixels = small_img[ Best_fit_index[index] ].get_3D_pixels();
            for (int y = 0; y < SUB_PIC_SIZE + n_y; ++y) {
                for (int x = 0; x < SUB_PIC_SIZE + n_x; ++x) {
                    _pixels[n_y + y][n_x + x][0] = best_pixels[y][x][0];
                    _pixels[n_y + y][n_x + x][1] = best_pixels[y][x][1];
                    _pixels[n_y + y][n_x + x][2] = best_pixels[y][x][2];
                }
            }
            index++;
        }
    }
    return Mosaic;
}

>>>>>>> Factor2_Ou
