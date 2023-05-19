#ifndef _STATE_H_
#define _STATE_H_

#include <vector>
#include <tuple>
#include <list>
#include "utils.h"
#include <set>


class State
{
    public:
        State();

        std::set<space> marbles;
        std::set<space> empty_spaces;

        // Updates full and empty spaces, throws exception if not valid
        void apply_move(move m);

        std::list<move> generate_valid_moves();

        void print_state();

        bool are_adjacent(space s1, space s2);

        space find_landing(space hopping, space hopped);
};

#endif