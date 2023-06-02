#include "utils.h"

void print_move(move m)
{
    int hopping = std::get<0>(m);
    int hopped = std::get<1>(m);
    int landing = std::get<2>(m);
    std::cout << hopping << " hops " << hopped << " to " << landing << std::endl;
}