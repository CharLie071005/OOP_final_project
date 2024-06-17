#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "photo_mosaic.h"
#include "bit_field_filter.h"

#define option1 0b01001100
#define option2 0b10001000
#define ENABLE_X_SERVER false

void TestGrayImage();
void TestRGBImage();
void TestPhotoMosaic();

int main(int argc, char *argv[]) {
    TestGrayImage();
    TestRGBImage();
    TestPhotoMosaic();
    return 0;
}

void TestGrayImage() {
    Image *img1 = new GrayImage();
    img1->LoadImage("Image-Folder/mnist/img_100.jpg");
    img1->DumpImage("img1.jpg");
    if(ENABLE_X_SERVER) {
        img1->Display_X_Server();
    }
    img1->Display_ASCII();
    img1->Display_CMD();

    //Test bit field
    if (loadCase(option1, img1)) {
        img1->DumpImage("imgtest1.jpg");
        if(ENABLE_X_SERVER) {
            img1->Display_X_Server();
        }
        img1->Display_ASCII();
        img1->Display_CMD();
    }
    img1->Delete();
    delete img1;
    img1 = nullptr;
}

void TestRGBImage() {
    Image *img2 = new RGBImage();
    img2->LoadImage("Image-Folder/lena.jpg");
    img2->DumpImage("img2.jpg");
    if(ENABLE_X_SERVER) {
        img2->Display_X_Server();
    }
    img2->Display_CMD();

    if(loadCase(option2, img2)) {
        img2->DumpImage("imgtest2.jpg");
        if(ENABLE_X_SERVER) {
            img2->Display_X_Server();
        }
        img2->Display_CMD();
    }
    // img2->Delete();
    delete img2;
    img2 = nullptr;
}

void TestPhotoMosaic() {
    PhotoMosaic mosaic;
    RGBImage *loadimg = mosaic.InputPath("Image-Folder/girl_2x.png", "Image-Folder/cifar10"); 
    loadimg->DumpImage("LoadImage.jpg");
    cout << "Display CMD" <<endl;
    loadimg->Display_CMD();
    
    RGBImage *Mosaic = mosaic.Generate_Mosaic();   
    Mosaic->DumpImage("mosaic.jpg");
    cout << "Display Mosaiced loadimg" << endl;  
    Mosaic->Display_CMD();
    Mosaic->Delete();
    loadimg->Delete();
    delete Mosaic;
    Mosaic = nullptr;
}