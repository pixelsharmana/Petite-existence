#ifndef UNITS_H
#define UNITS_H

struct unit{
std::string name;
bool sex;//0 for male, 1 for female
double x;
double y;
double speed;
std::vector<const unsigned char*> textures;
unsigned int state;
void draw(void);
unit();
unit(std::string m_name, bool m_sex, double m_x, double m_y, std::vector<const unsigned char*> m_textures);
};

#endif
