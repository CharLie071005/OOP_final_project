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

void TestGrayImage();
void TestRGBImage();
void TestPhotoMosaic();

int main(int argc, char *argv[]) {
    // TestGrayImage();
    //TestRGBImage();
    TestPhotoMosaic();
    return 0;
}
// int main() {
//     int height = 100;
//     int width = 100;

//     try {
//         RGBImage *Mosaic = new RGBImage(height, width);
//         std::cout << "RGBImage object created successfully." << std::endl;
//         // Test LoadImage and DumpImage
//         Mosaic->LoadImage("input_file.txt");
//         Mosaic->DumpImage("output_file.txt");
//         // Do something with Mosaic
//         delete Mosaic;
//         std::cout << "RGBImage object deleted successfully." << std::endl;
//     } catch (const std::exception &e) {
//         std::cerr << "Exception: " << e.what() << std::endl;
//     }

//     return 0;
// }

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
    if (loadCase(RGB_Linear, img1)) {
        img1->DumpImage("imgtest1.jpg");
        if(ENABLE_X_SERVER) {
            img1->Display_X_Server();
        }
        img1->Display_ASCII();
        img1->Display_CMD();
    }
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

    if(loadCase(RGB_Linear, img2)) {
        img2->DumpImage("imgtest2.jpg");
        if(ENABLE_X_SERVER) {
            img2->Display_X_Server();
        }
        img2->Display_CMD();
    }
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
    // int ***pixels = Mosaic->get_3D_pixels();
    
    Mosaic->DumpImage("mosaic.jpg");
    cout << "Display Mosaiced loadimg" << endl;  
    //Mosaic->Display_ASCII();
    Mosaic->Display_CMD();
    delete Mosaic;
    Mosaic = nullptr;
}