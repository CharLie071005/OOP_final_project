#ifndef _PHOTO_MOSAIC_H_
#define _PHOTO_MOSAIC_H_
#include "rgb_image.h"
#include <array>

class PhotoMosaic{
    private:
        Image image;

        vector<string> small_name;
        vector<RGBImage> small_image;
        vector<RGBmage> Bestvector;
    public:
        PhotoMosaic();
        ~PhotoMosaic();
        Image *InputFile(const string &Bigphoto, const string &MinDir);
        void CalculateAverage();
        void SplitImage();
        void CreateGridImage();
        RGBImage GenerateMosaic();
};

#endif