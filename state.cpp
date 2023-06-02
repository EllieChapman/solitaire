#include "state.h"
#include <iostream>


void State::apply_move(move m)
{
    int hopping = std::get<0>(m);
    int hopped = std::get<1>(m);
    int landing = std::get<2>(m);

    marbles.erase(hopping);
    marbles.erase(hopped);
    marbles.insert(landing);

    // // move hopping and hopped from full to empty
    // // std::cout << "Applying move: "; // EBC good for debugging
    // // print_move(m); // EBC good for debugging
    // std::list<int> to_erase {};
    // for (auto marble : marbles)
    // {
    //     if (marble == hopping || marble == hopped)
    //     {
    //         to_erase.push_back(marble);
    //         empty_spaces.insert(marble);
    //     }
    // }
    // for (auto marble : to_erase)
    // {
    //     marbles.erase(marble);
    // }
    // // move landing to from empty to full
    // std::list<int> space_to_erase {};
    // for (auto space : empty_spaces)
    // {
    //     if (space == landing)
    //     {
    //         space_to_erase.push_back(space);
    //         marbles.insert(space);
    //     }
    // }
    // for (auto space : space_to_erase)
    // {
    //     empty_spaces.erase(space);
    // }
}

std::list<move> State::generate_valid_moves()
{
    std::list<move> valid_moves;

    for (auto possible : all_moves)
    {
        int hopping = std::get<0>(possible);
        int hopped = std::get<1>(possible);
        int landing = std::get<2>(possible);
        if (marbles.find(hopped) != marbles.end())
        {
            if (marbles.find(hopping) != marbles.end())
            {
                if (marbles.find(landing) == marbles.end())
                {
                    // std::cout << "found move" << std::endl;
                    valid_moves.push_back(possible);
                }
            }
            else
            {
                if (marbles.find(landing) != marbles.end())
                {
                    // reverse valid
                    // std::cout << "found move" << std::endl;
                    valid_moves.push_back(std::make_tuple(landing, hopped, hopping));
                }
            }
        }
    }
    return valid_moves;
}


void State::print_state()
{
    std::cout << "Current state of board" << std::endl;
    for (int marble : marbles)
    {
        std::cout << "Marble: " << marble << std::endl;
    }
    // for (int space : empty_spaces)
    // {
    //     std::cout << "Space: " << space << std::endl;
    // }
}


State::State()
{
    // empty_spaces.insert(16);
    marbles = std::set<int> {
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
    };

    all_moves = std::list<move> {
    std::make_tuple(0, 1, 2),
    // std::make_tuple(2, 1, 0),
    std::make_tuple(3, 4, 5),
    // std::make_tuple(5, 4, 3),
    std::make_tuple(6, 7, 8),
    // std::make_tuple(8, 7, 6),
    std::make_tuple(7, 8, 9),
    // std::make_tuple(9, 8, 7),
    std::make_tuple(8, 9, 10),
    // std::make_tuple(10, 9, 8),
    std::make_tuple(9, 10, 11),
    // std::make_tuple(11, 10, 9),
    std::make_tuple(10, 11, 12),
    // std::make_tuple(12, 11, 10),
    std::make_tuple(13, 14, 15),
    // std::make_tuple(15, 14, 13),
    std::make_tuple(14, 15, 16),
    // std::make_tuple(16, 15, 14),
    std::make_tuple(15, 16, 17),
    // std::make_tuple(17, 16, 15),
    std::make_tuple(16, 17, 18),
    // std::make_tuple(18, 17, 16),
    std::make_tuple(17, 18, 19),
    // std::make_tuple(19, 18, 17),
    std::make_tuple(20, 21, 22),
    // std::make_tuple(22, 21, 20),
    std::make_tuple(21, 22, 23),
    // std::make_tuple(23, 22, 21),
    std::make_tuple(22, 23, 24),
    // std::make_tuple(24, 23, 22),
    std::make_tuple(23, 24, 25),
    // std::make_tuple(25, 24, 23),
    std::make_tuple(24, 25, 26),
    // std::make_tuple(26, 25, 24),
    std::make_tuple(27, 28, 29),
    // std::make_tuple(29, 28, 27),
    std::make_tuple(30, 31, 32),
    // std::make_tuple(32, 31, 30),
    //
    std::make_tuple(6, 13, 20),
    // std::make_tuple(20, 13, 6),
    std::make_tuple(7, 14, 21),
    // std::make_tuple(21, 14, 7),
    std::make_tuple(0, 3, 8),
    // std::make_tuple(8, 3, 0),
    std::make_tuple(3, 8, 15),
    // std::make_tuple(15, 8, 3),
    std::make_tuple(8, 15, 22),
    // std::make_tuple(22, 15, 8),
    std::make_tuple(15, 22, 27),
    // std::make_tuple(27, 22, 15),
    std::make_tuple(22, 27, 30),
    // std::make_tuple(30, 27, 22),
    std::make_tuple(1, 4, 9),
    // std::make_tuple(9, 4, 1),
    std::make_tuple(4, 9, 16),
    // std::make_tuple(16, 9, 4),
    std::make_tuple(9, 16, 23),
    // std::make_tuple(23, 16, 9),
    std::make_tuple(16, 23, 28),
    // std::make_tuple(28, 23, 16),
    std::make_tuple(23, 28, 31),
    // std::make_tuple(31, 28, 23),
    std::make_tuple(2, 5, 10),
    // std::make_tuple(10, 5, 2),
    std::make_tuple(5, 10, 17),
    // std::make_tuple(17, 10, 5),
    std::make_tuple(10, 17, 24),
    // std::make_tuple(24, 17, 10),
    std::make_tuple(17, 24, 29),
    // std::make_tuple(29, 24, 17),
    std::make_tuple(24, 29, 32),
    // std::make_tuple(32, 29, 24),
    std::make_tuple(11, 18, 25),
    // std::make_tuple(25, 18, 11),
    std::make_tuple(12, 19, 26),
    // std::make_tuple(26, 19, 12),
};
}