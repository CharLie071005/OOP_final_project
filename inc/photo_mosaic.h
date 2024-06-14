#ifndef _PHOTO_MOSAIC_H_
#define _PHOTO_MOSAIC_H_
#include "image.h"
#include "rgb_image.h"
#include <map>
#include <array>

class PhotoMosaic{
    protected:
        Image image;
        //讀取檔案
        vector<string> small_name;  //儲存小圖名字
        vector<Image> small_image;  //儲存名字對應的Image
        vector<int ***> small_avg;      //儲存對應minst的平均值
        vector<Image> splited_photo; //分割後的大圖
        
        //處理圖片所用到的變數
    public:
        PhotoMosaic();
        ~PhotoMosaic();
        Image *InputImage(string BigPhotoName, string Mnist_Folder);
        //void SplitPhoto();
        int*** CalculateAverage(Image image);
        int getBestMatchIndex(Image image, vector<int***>& avgs);
        void Generate_Mosaic();
        vector<int ***> splitImage(int ***pixels, int width, int height, int subWidth, int subHeight);
        int ***createImageGrid(const vector<int ***>& images, int subWidth, int subHeight, int width, int height);


};

#endif