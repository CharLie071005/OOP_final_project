#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "photo_mosaic.h"
#include "bit_field_filter.h"

<<<<<<< HEAD
#define option1 0b00000100
#define option2 0b01000000


int main(int argc, char *argv[]){
    Image *img1 = new GrayImage();
    img1->LoadImage("Image-Folder/mnist/img_100.jpg");
    img1->DumpImage("img1.jpg");
    //img1->Display_X_Server();
    //img1->Display_ASCII();
    //img1->Display_CMD();
    Image *img2 = new RGBImage();
    img2->LoadImage("Image-Folder/lena.jpg");
    img2->DumpImage("img2.jpg");
    // img2->Display_X_Server();
    //img2->Display_ASCII();
    img2->Display_CMD();

=======
#define option 0b00100000


int main(int argc, char *argv[]){
    // Image *img1 = new GrayImage();
    // img1->LoadImage("Image-Folder/mnist/img_100.jpg");
    // img1->DumpImage("img1.jpg");
    // img1->Display_X_Server();
    // img1->Display_ASCII();
    // img1->Display_CMD();

    // loadCase(option, img1);
    // img1->DumpImage("imgtest1.jpg");
    // img1->Display_X_Server();
    // img1->Display_ASCII();
    // img1->Display_CMD();

    Image *img2 = new RGBImage();
    img2->LoadImage("Image-Folder/lena.jpg");
    img2->DumpImage("img2.jpg");
    img2->Display_X_Server();
    // img2->Display_ASCII();
    img2->Display_CMD();

    loadCase(option, img2);
    img2->DumpImage("imgtest1.jpg");
    img2->Display_X_Server();
    // img2->Display_ASCII();
    img2->Display_CMD();
>>>>>>> b0c8f8d17babb752b19383fc91a2e6538f821f4a

    ////some bit field filter design driven code here
    //loadCase(option1, img1);
    //img1->DumpImage("imgtest1.jpg");
    //img1->Display_X_Server();
    //img1->Display_CMD();
    //img1->Display_ASCII();
  
    loadCase(option1, img2);
    img2->DumpImage("imgtest1.jpg");
    //img2->Display_X_Server();
    //img2->Display_ASCII();
    img2->Display_CMD();

    //// some bit field filter design driven code here
    
    // some photo mosaic driven code here

    // more ...
    return 0;
}
