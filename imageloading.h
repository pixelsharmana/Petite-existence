#ifndef IMAGELOADING_H
#define IMAGELOADING_H
#include <vector>
struct image{
std::vector<unsigned char> data;
unsigned int width;
unsigned int height;
};

//image finalImageLoading(std::string);
void pasteImage(image inputImage);
void movePasteImage(image inputImage,double,double);
void movePartialPasteImage(image inputImage,int,int,unsigned int,unsigned int);
void pasteText(const unsigned char*);
void movePasteText(const unsigned char*,double,double);
void writeText(std::string,std::map<char,const unsigned char *>,int,int);

#endif
