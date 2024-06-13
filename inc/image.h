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
      string loadfilename; //�]�w�ܼƥH�O��Ū�����ɮצW�١A�D�n�O��Display_CMD�ϥΡA�������b���i
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
      virtual int **get_pixels(); //���F��filter�ϥ�pixels�C�ݦb���i����
};

#endif