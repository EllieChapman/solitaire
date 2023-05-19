#include "utils.h"

void print_move(move m)
{
    space hopping = std::get<0>(m);
    space hopped = std::get<1>(m);
    space landing = std::get<2>(m);
    std::cout << std::get<0>(hopping) << "," << std::get<1>(hopping) << " hops " << std::get<0>(hopped) << "," << std::get<1>(hopped) << " to " << std::get<0>(landing) << "," << std::get<1>(landing) << std::endl;
}

space rotate_point(space s)
{
    return std::make_tuple(8-std::get<1>(s), std::get<0>(s));
}