#ifndef _PHOTO_MOSAIC_H_
#define _PHOTO_MOSAIC_H_
#include "image.h"
#include "rgb_image.h"
#include <map>
#include <array>
#include <vector>
#include <string>

using namespace std;

class PhotoMosaic: public RGBImage {
    private:
        Image* TImage;
        Image subImage;
        vector<string> sub_name; // Store small image's filename
        vector<Image> sub_image; // Store the corresponding image in the same sequence
        vector<array<int, 3>> sub_avg; // Store the average value correspond to image

    public:
        // Initialization
        PhotoMosaic();
        ~PhotoMosaic();
        PhotoMosaic(Image* image);
        Image *get_TImage();
        void readSubImage(const string& subPath, vector<string>& sub_Folder);
        array<int, 3> CalculateAverage(int*** pixels, int width, int height);
        int getBestMatchIndex(const array<int, 3>& tarAvg);
        vector<int***> splitImage(int*** pixels, int subWidth, int subHeight, int width, int height);
        int*** createImageGrid(const vector<int***>& sub_images_pixel, int subWidth, int subHeight, int width, int height);
        void Generate_Mosaic(const string& path);
};

#endif
