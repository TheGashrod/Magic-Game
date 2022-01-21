#ifndef __MTG_COLOR_INCLUDED__
#define __MTG_COLOR_INCLUDED__

#include <iostream>
#include <list>


enum Color { Blue, White, Red, Black, Green};

std::ostream& operator<<(std::ostream& os, const Color c);
std::ostream& operator<<(std::ostream& os, std::list<Color> colors);




#endif
