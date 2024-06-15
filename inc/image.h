#ifndef _IMAGE_H_
#define _IMAGE_H_
#include "data_loader.h"
#include <string>
using namespace std;

class Image{
  protected:
      int width;
      int height;
      static Data_Loader data_loader;
      string loadfilename; //storage the filename that LoadImane imput
                           //mainly used by CMD_Display
  public:
      Image();
      virtual ~Image();
      virtual bool LoadImage(string filename);
      virtual void DumpImage(string filename);
      virtual void Display_X_Server();
      virtual void Display_ASCII();
      virtual void Display_CMD();
      int get_width();
      int get_height();
      // function
      virtual int **get_pixels();   //return 2-dimensiolan pixels array
      virtual int ***get_3D_pixels();  //return 3-dimensiolan pixels array
      void List_Name_Directory(string Path, vector<string> &filenames);
};

#endif