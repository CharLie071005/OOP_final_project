#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "photo_mosaic.h"
#include "bit_field_filter.h"
#define option1  0b00000010
#define option2  0b00010000

int main(int argc, char *argv[]){
    Image *img1 = new GrayImage();
    img1->LoadImage("Image-Folder/girl_2x.png");
    img1->DumpImage("img1.jpg");
    //img1->Display_X_Server();
    //img1->Display_ASCII();
    img1->Display_CMD();
    

    //Image *img2 = new RGBImage();
    // img2->LoadImage("Image-Folder/lena.jpg");
    // img2->DumpImage("img2.jpg");
    //img2->Display_X_Server();
    //img2->Display_ASCII();
    //img2->Display_CMD();

    // some bit field filter design driven code here
    loadCase(option1, img1);
    img1->DumpImage("img1.jpg");
    //img1->Display_X_Server();
    //img2->Display_ASCII();
    img1->Display_CMD();
    img1->showPixels();
    // some bit field filter design driven code here
    
    // some photo mosaic driven code here

    // more ...
    return 0;
}
