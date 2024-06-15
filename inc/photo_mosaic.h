#ifndef _PHOTO_MOSAIC_H_
#define _PHOTO_MOSAIC_H_
#include "image.h"
#include "rgb_image.h"
#include <map>
#include <array>

class PhotoMosaic{
    protected:
        Image image;
        // store the Load image
        vector<string> small_name;  //store small image's filename
        vector<RGBImage> small_image;  //store the corresponding image in the same sequence
        vector<int ***> small_avg;      //store the average value correspond to image
        
        //the variables used to process photo
        vector<int ***> splited_photo; //the splited target photo
        
    public:
        //initialization
        PhotoMosaic();
        ~PhotoMosaic();
        Image *InputImage(string BigPhotoName, string Mnist_Folder);
        //Image Processing
        void CalculateAverage(int ***_pixels);
        int getBestMatchIndex(int ***tar, vector<int***>& avgs);
        vector<int ***> splitImage(int ***pixels, int width, int height, int subWidth, int subHeight);
        int ***createImageGrid(const vector<int ***>& images, int subWidth, int subHeight, int width, int height);
        RGBImage Generate_Mosaic();
        
        /*Memories need to delete: 
        1.Img1 that InputImage() declared
        2.grid that createImageGrid() declared
        Done 3. subImages that splitImage() declared -> using destructor
        */
};

#endif