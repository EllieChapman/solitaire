#ifndef _UTILS_H_
#define _UTILS_H_

#include <tuple>
#include <iostream>

typedef std::tuple<int,int> space;
typedef std::tuple<space,space,space> move;

void print_move(move m);

space rotate_point(space s);

#endif