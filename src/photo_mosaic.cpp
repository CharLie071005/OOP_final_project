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

int PhotoMosaic::getBestMatchIndex(Image image, vector<int***>& avgs){
    int bestIndex = 0;
    int ***avg = image.get_3D_pixels();
    double minDist = numeric_limits<double>::max();
    for (size_t i = 0; i < avgs.size(); i++) {
        double dist = pow(avg[0] - avgs[i][0], 2) + pow(avg[1] - avgs[i][1], 2) + pow(avg[2] - avgs[i][2], 2);
        if (dist < minDist) {
            minDist = dist;
            bestIndex = i;
        }
    }
    return bestIndex;
}


int ***PhotoMosaic::createImageGrid(const vector<int ***>& images, int subWidth, int subHeight, int width, int height) {
    int ***grid = new int **[height];
    for (int i = 0; i < height; i++) {
        grid[i] = new int *[width];
        for (int j = 0; j < width; j++) {
            grid[i][j] = new int[3];
        }
    }

    for (int y = 0; y < width / subWidth; y++) {
        for (int x = 0; x < height / subHeight; x++) {
            int ***subImage = images[y * width / subWidth + x];
            for (int i = 0; i < subHeight; i++) {
                for (int j = 0; j < subWidth; j++) {
                    grid[y * subHeight + i][x * subWidth + j][0] = subImage[i][j][0];
                    grid[y * subHeight + i][x * subWidth + j][1] = subImage[i][j][1];
                    grid[y * subHeight + i][x * subWidth + j][2] = subImage[i][j][2];
                }
            }
        }
    }
    return grid;
}


vector<int ***> PhotoMosaic::splitImage(int ***pixels, int width, int height, int subWidth, int subHeight) {
    vector<int ***> subImages;
    for (int y = 0; y < height / subHeight; y++) {
        for (int x = 0; x < width / subWidth; x++) {
            int ***subImage = new int **[subHeight];
            for (int i = 0; i < subHeight; i++) {
                subImage[i] = new int *[subWidth];
                for (int j = 0; j < subWidth; j++) {
                    subImage[i][j] = new int[3];
                    subImage[i][j][0] = pixels[y * subHeight + i][x * subWidth + j][0];
                    subImage[i][j][1] = pixels[y * subHeight + i][x * subWidth + j][1];
                    subImage[i][j][2] = pixels[y * subHeight + i][x * subWidth + j][2];
                }
            }
            subImages.push_back(subImage);
        }
    }
    return subImages;
}


void PhotoMosaic::Generate_Mosaic(){

}