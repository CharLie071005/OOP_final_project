#ifndef _PHOTO_MOSAIC_H_
#define _PHOTO_MOSAIC_H_
#include "image.h"
#include "rgb_image.h"
#include <map>
#include <array>

class PhotoMosaic{
    protected:
        Image image;
        vector<string> small_name;  //儲存小圖名字
        vector<Image> small_image;  //儲存名字對應的Image
        vector<array<int,3>> small_avg;      //儲存對應minst的平均值
        vector<Image> splited_photo; //分割後的大圖
        //map<string, Image> Map_mnist;
    public:
        PhotoMosaic();
        ~PhotoMosaic();
        Image *InputImage(string BigPhotoName, string Mnist_Folder);
        //void SplitPhoto();
        std::array<int, 3> CalculateAverage(Image *image);
        int getBestMatchIndex(Image avg, vector<Image>& avgs);
        int ***createImageGrid(const vector<int ***>& images, int subWidth, int subHeight, int width, int height);
        vector<int ***> splitImage(int ***pixels, int width, int height, int subWidth, int subHeight);

};

#endif