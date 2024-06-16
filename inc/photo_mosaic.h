#ifndef _PHOTO_MOSAIC_H_
#define _PHOTO_MOSAIC_H_
#include "rgb_image.h"
#include <array>
#include <vector>
#include <string>
#define SUB_PIC_SIZE 32
#define Max_Small_Number 10000

<<<<<<< HEAD
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
=======
using namespace std;

class PhotoMosaic {
    private:
        vector<string> sub_name; // Store small image's filename       
        RGBImage tarimage;
        RGBImage small_img[Max_Small_Number];
        static Data_Loader data_loader;
        int *avgR_tar_grid;
        int *avgG_tar_grid;
        int *avgB_tar_grid;
        int *avgR_small;
        int *avgG_small;
        int *avgB_small;
        int simage_number; //storage the number of small_image
        vector<int> Best_fit_index;
        
        //function
        void readSubImage();
        void Calculate_SmallAverage();
        void Calculate_TarAverage();
        void getBestMatchIndex();  
    public:
        // Initialization
        PhotoMosaic();
        ~PhotoMosaic();
        RGBImage *InputPath(const string& Bigphoto, const string &cifatDir);    
        
        //Processing Image
        RGBImage *Generate_Mosaic();
>>>>>>> Factor2_Ou
};

#endif
