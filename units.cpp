#include <vector>
#include <string>
#include <random>
#include <gl/gl.h>

struct unit{
std::string name;
bool sex;//0 for male, 1 for female
double x;
double y;
double speed;
std::vector<const unsigned char*> textures;
unsigned int state;//State shows what texture to display
//0 Down, 1 Down Left, 2 Down Right, 3 Left Rest, 4 Left Active, 5 Up, 6 Up Left, 7 Up Right, 8 Right Rest, 9 Right Active
//After that, it's special textures
void draw(void);
unit();
unit(std::string m_name, bool m_sex, double m_x, double m_y, std::vector<const unsigned char*> m_textures);
};

unit::unit(void){}

unit::unit(std::string m_name, bool m_sex, double m_x, double m_y, std::vector<const unsigned char*> m_textures){
name=m_name;
sex=m_sex;
x=m_x;
y=m_y;
speed=0;
textures=m_textures;
state=0;
}

void unit::draw(void){
glRasterPos2d(0,0);
glDrawPixels(14,14,GL_RGBA,GL_UNSIGNED_BYTE, this->textures[this->state]);
}
