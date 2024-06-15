#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "photo_mosaic.h"
#include "bit_field_filter.h"

#define option1 0b00001100
#define option2 0b10100000
#define ENABLE_X_SERVER false



int main(int argc, char *argv[]){
    Image *img1 = new GrayImage();
    img1->LoadImage("Image-Folder/mnist/img_100.jpg");
    img1->DumpImage("img1.jpg");
    if(ENABLE_X_SERVER){
        img1->Display_X_Server();
    }
    img1->Display_ASCII();
    img1->Display_CMD();

    //test bit filed
    if (loadCase(option1, img1)){
        img1->DumpImage("imgtest1.jpg");
        if(ENABLE_X_SERVER){
            img1->Display_X_Server();
        }
        img1->Display_ASCII();
        img1->Display_CMD();
    }

    Image *img2 = new RGBImage();
    img2->LoadImage("Image-Folder/lena.jpg");
    img2->DumpImage("img2.jpg");
    if(ENABLE_X_SERVER){
        img2->Display_X_Server();
    }
    //img2->Display_ASCII();
    img2->Display_CMD();

    if(loadCase(option2, img2)){
        img2->DumpImage("imgtest1.jpg");
        if(ENABLE_X_SERVER){
            img2->Display_X_Server();
        }
        //img2->Display_ASCII();
        img2->Display_CMD();
    }

    //// some bit field filter design driven code here
    
    // some photo mosaic driven code here

    // more ...

    delete img1;
    img1 = nullptr;
    delete img2;
    img2 = nullptr;
    return 0;
}
