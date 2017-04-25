#include <gl/gl.h>
#include <map>
#include <string>
#include <vector>

///How to use this?
//Well, I dunno lol

struct image{
std::vector<unsigned char> data;
unsigned int width;
unsigned int height;
};


void pasteImage(image inputImage){
glDrawPixels(inputImage.width,inputImage.height,GL_RGBA,GL_UNSIGNED_BYTE, &inputImage.data[0]);
}

void movePasteImage(image inputImage, double x, double y){
//f(x/(nombre/2))-1
///Thanks Ayoub
x=x/(175/2);
y=y/(181/2);
glRasterPos2d(x,y);
glDrawPixels(inputImage.width,inputImage.height,GL_RGBA,GL_UNSIGNED_BYTE, &inputImage.data[0]);
glRasterPos2d(-1,-1);
}

void pasteText(const unsigned char *letter){
glDrawPixels(3,5,GL_RGBA,GL_UNSIGNED_BYTE, letter);
}

void movePasteText(const unsigned char *letter, double x, double y){
x=x/(175/2);
y=y/(181/2);
glRasterPos2d(x,y);
glDrawPixels(3,5,GL_RGBA,GL_UNSIGNED_BYTE, letter);
glRasterPos2d(-1,-1);
}

void movePartialPasteImage(image inputImage, int moveX, int moveY, unsigned int cutX, unsigned int cutY){
//f(x/(nombre/2))-1
///Thanks Ayoub
glRasterPos2d(moveX/((160+15)/2)-1,moveY/((144+37)/2)-1);
glDrawPixels(cutX,cutY,GL_RGBA,GL_UNSIGNED_BYTE, &inputImage.data[0]);
glRasterPos2d(-1,-1);
}

void writeText(std::string textIn, std::map<char,const unsigned char *> font, int moveX, int moveY){
int offset=0;
for (auto it : textIn){
    movePasteText(font[it],moveX+offset,moveY);
    offset+=5;
}
}
