#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "photo_mosaic.h"
#include "bit_field_filter.h"

#define option1 0b00001100
#define option2 0b10100000
#define ENABLE_X_SERVER false

void TestGrayImage();
void TestRGBImage();
void TestPhotoMosaic();

int main(int argc, char *argv[]) {
    // TestGrayImage();
    // TestRGBImage();
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

    // Test bit field
    if (loadCase(option1, img1)) {
        img1->DumpImage("imgtest1.jpg");
        if(ENABLE_X_SERVER) {
            img1->Display_X_Server();
        }
        img1->Display_ASCII();
        img1->Display_CMD();
    }
    delete img1;
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
    delete img2;
}

void TestPhotoMosaic() {
    Image* img3T = new RGBImage();
    PhotoMosaic* img3 = new PhotoMosaic(img3T);
    img3->get_TImage()->LoadImage("Image-Folder/girl_2x.png");
    cout << "Load Image success\n";
    img3->get_TImage()->DumpImage("img3.jpg");
    cout << "Dump Image success\n";
    img3->Generate_Mosaic("Image-Folder/mnist");
    img3->get_TImage()->DumpImage("Mosaiced_Photo.jpg");

    if(ENABLE_X_SERVER) {
        img3->get_TImage()->Display_X_Server();
    }
    img3->get_TImage()->Display_CMD();
    delete img3;
}