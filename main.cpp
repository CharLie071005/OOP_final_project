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
        img2->DumpImage("imgtest1.jpg");
        if(ENABLE_X_SERVER) {
            img2->Display_X_Server();
        }
        img2->Display_CMD();
    }
    delete img2;
}

void TestPhotoMosaic() {
    PhotoMosaic photo_mosaic;
    photo_mosaic.InputImage("Image-Folder/gril_2x.png", "Image-Folder/cifar10");

    RGBImage* img3 = new RGBImage();
    img3->LoadImage("Image-Folder/mnist/img_100.jpg");

    img3->DumpImage("img3.jpg");
    if(ENABLE_X_SERVER) {
        img3->Display_X_Server();
    }
    img3->Display_CMD();

    RGBImage Mosaiced_photo = photo_mosaic.Generate_Mosaic();
    Mosaiced_photo.DumpImage("Mosaiced_Photo.jpg");

    if(ENABLE_X_SERVER) {
        Mosaiced_photo.Display_X_Server();
    }
    Mosaiced_photo.Display_CMD();
    delete img3;
}