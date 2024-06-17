#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "photo_mosaic.h"
#include "bit_field_filter.h"

#define ENABLE_X_SERVER false

void grayImage(string filePath);
void rgbImage(string filePath);
void photoMosaic(string filePath);

int main() {
    string filePath;
    int imageType;
    cout << "Please cin your image path(ex:Image-Folder/girl_2x.png): " << endl;
    cin >> filePath;
    cout << "Please cin your image type:\n" << "1: gray image\n" << "2: rgb image\n" << "3: mosaic image\n";
    cin >> imageType;
    switch(imageType){
        case 1:
            grayImage(filePath);
            break;
        case 2:
            rgbImage(filePath);
            break;
        case 3:
            photoMosaic(filePath);
            break;
        default:
            cout << "Wrong input!!!";
            exit(1);
    }
    return 0;
}

void grayImage(string filePath) {
    Image *img1 = new GrayImage();
    img1->LoadImage(filePath);
    img1->DumpImage("GrayImage.jpg");
    if(ENABLE_X_SERVER) {
        img1->Display_X_Server();
    }
    img1->Display_ASCII();
    img1->Display_CMD();
    int8_t option;
    cout << "please choose your filter:\n" << "GRAY_BOX       0b01000001\nGRAY_Med       0b01000010\nGRAY_Sobel     0b01000100\nGRAY_Linear    0b01001000\nGRAY_Stretch   0b01010000\nGRAY_Histogram 0b01100000\n";
    cin >> option;
    if (loadCase(option, img1)) {
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

void rgbImage(string filePath) {
    Image *img2 = new RGBImage();
    img2->LoadImage(filePath);
    img2->DumpImage("RGBImage.jpg");
    if(ENABLE_X_SERVER) {
        img2->Display_X_Server();
    }
    img2->Display_CMD();
    int8_t option;
    cout << "please choose your filter:\n" << "RGB_BOX       0b10000001\nRGB_Med       0b10000010\nRGB_Sobel     0b10000100\nRGB_Linear    0b10001000\nRGB_Stretch   0b10010000\nRGB_Histogram 0b10100000\n";
    cin >> option;
    if(loadCase(option, img2)) {
        img2->DumpImage("imgtest2.jpg");
        if(ENABLE_X_SERVER) {
            img2->Display_X_Server();
        }
        img2->Display_CMD();
    }
    img2->Delete();
    delete img2;
    img2 = nullptr;
}

void photoMosaic(string filePath) {
    PhotoMosaic mosaic;
    RGBImage *loadimg = mosaic.InputPath(filePath, "Image-Folder/cifar10"); 
    loadimg->DumpImage("MosaicImage.jpg");
    cout << "Display CMD" <<endl;
    loadimg->Display_CMD();
    
    RGBImage *Mosaic = mosaic.Generate_Mosaic();   
    Mosaic->DumpImage("mosaic.jpg");
    cout << "Display Mosaiced loadimg" << endl;  
    Mosaic->Display_CMD();
    string answer;
    cout << "Do you want to imply filters?\n";
    cin >> answer;
    if (answer != "y" && answer != "Y" && answer != "yes" && answer != "YES" && answer != "Yes") {
        exit(1);
    }
    rgbImage(filePath);
    Mosaic->Delete();
    loadimg->Delete();
    delete Mosaic;
    Mosaic = nullptr;
}