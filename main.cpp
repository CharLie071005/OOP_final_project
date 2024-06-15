#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "photo_mosaic.h"
#include "bit_field_filter.h"

#define GRAY_BOX    0b00000001
#define GRAY_Med    0b00000010
#define GRAY_Sobel  0b00000100
#define GRAY_Linear 0b00001000
#define RGB_BOX     0b00010000
#define RGB_Med     0b00100000
#define RGB_Sobel   0b01000000
#define RGB_Linear  0b10000000
#define ENABLE_X_SERVER false



int main(int argc, char *argv[]){
    /*
    Image *img1 = new GrayImage();
    img1->LoadImage("Image-Folder/mnist/img_100.jpg");
    img1->DumpImage("img1.jpg");
    if(ENABLE_X_SERVER){
        img1->Display_X_Server();
    }
    img1->Display_ASCII();
    img1->Display_CMD();

    //test bit filed
    if (loadCase(GRAY_Sobel | GRAY_Linear , img1)){
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
    */

    //// some bit field filter design driven code here
    
    //try ignore
    // some photo mosaic driven code here

    PhotoMosaic photo_mosaic;
    Image *img3 = photo_mosaic.InputImage("Image-Folder/gril_2x.png", "Image-Folder/cifar10");
    img3->DumpImage("img3.jpg");
    if(ENABLE_X_SERVER){
        img3->Display_X_Server();
    }
    //img3->Display_ASCII();
    img3->Display_CMD();


    RGBImage Mosaiced_photo = photo_mosaic.Generate_Mosaic();
    Mosaiced_photo.DumpImage("Mosaiced_Photo.jpg");

    if(ENABLE_X_SERVER){
        Mosaiced_photo.Display_X_Server();
    }
    //Mosaiced_photo.Display_ASCII();
    Mosaiced_photo.Display_CMD();

    /*
    delete img1;
    img1 = nullptr;
    delete img2;
    img2 = nullptr;
    */
    return 0;
}
