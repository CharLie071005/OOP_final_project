#ifndef IMAGE_H
#define IMAGE_H
#include "data_loader.h"
#include <string>
using namespace std;

class Image{
  protected:
      int width;
      int height;
      static Data_Loader data_loader;
      string loadfilename; //設定變數以記錄讀取的檔案名稱，主要是給Display_CMD使用
  public:
      Image();
      ~Image();
      virtual bool LoadImage(string filename);
      virtual void DumpImage(string filename);
      virtual void Display_X_Server();
      virtual void Display_ASCII();
      virtual void Display_CMD();
      int get_width();
      int get_height();
};

#endif