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

        std::set<int> marbles;
        // std::set<int> empty_spaces;

        // Updates full and empty spaces, throws exception if not valid
        void apply_move(move m);

        std::list<move> generate_valid_moves();

        void print_state();

        std::list<move> all_moves;
};


#endif