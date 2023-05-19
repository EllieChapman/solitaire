#include "state.h"
#include <iostream>


State::State()
{
    empty_spaces.insert(std::make_tuple(4,4));
    marbles = std::set<space> {
        // std::make_tuple(6,4),
        // std::make_tuple(5,4),
        // std::make_tuple(3,4),
        // EBC extend later
        //
        std::make_tuple(3,1),
        std::make_tuple(4,1),
        std::make_tuple(5,1),
        std::make_tuple(3,2),
        std::make_tuple(4,2),
        std::make_tuple(5,2),
        std::make_tuple(1,3),
        std::make_tuple(2,3),
        std::make_tuple(3,3),
        std::make_tuple(4,3),
        std::make_tuple(5,3),
        std::make_tuple(6,3),
        std::make_tuple(7,3),
        std::make_tuple(1,4),
        std::make_tuple(2,4),
        std::make_tuple(3,4),
        std::make_tuple(5,4),
        std::make_tuple(6,4),
        std::make_tuple(7,4),
        std::make_tuple(1,5),
        std::make_tuple(2,5),
        std::make_tuple(3,5),
        std::make_tuple(4,5),
        //
        std::make_tuple(5,5),
        // std::make_tuple(6,5),
        // std::make_tuple(7,5),
        // std::make_tuple(3,6),
        // std::make_tuple(4,6),
        // std::make_tuple(5,6),
        // std::make_tuple(3,7),
        // std::make_tuple(4,7),
        // std::make_tuple(5,7),
    };
}

void State::apply_move(move m)
{
    space hopping = std::get<0>(m);
    space hopped = std::get<1>(m);
    space landing = std::get<2>(m);

    // move hopping and hopped from full to empty
    // std::cout << "Applying move: "; // EBC good for debugging
    // print_move(m); // EBC good for debugging
    // for (long unsigned int i = marbles.size(); i > 0; i--)
    std::list<space> to_erase {};
    for (auto marble : marbles)
    {
        // space marble = marbles[i-1];
        if (marble == hopping || marble == hopped)
        {
            // marbles.erase(marble);
            to_erase.push_back(marble);
            empty_spaces.insert(marble);
        }
    }
    for (auto marble : to_erase)
    {
        marbles.erase(marble);
    }
    // move landing to from empty to full
    // for (long unsigned int i = empty_spaces.size(); i > 0; i--)
    std::list<space> space_to_erase {};
    for (auto space : empty_spaces)
    {
        // space space = empty_spaces[i-1];
        if (space == landing)
        {
            // empty_spaces.erase(space);
            space_to_erase.push_back(space);
            marbles.insert(space);
        }
    }
    for (auto space : space_to_erase)
    {
        empty_spaces.erase(space);
    }
}

std::list<move> State::generate_valid_moves()
{
    // make list of pairs of adjacent marbles
    // make list if valid moves by looking for adjacent spaces, make sure to check both ends of pair
    std::list<move> valid_moves;
    std::vector<std::tuple<space,space>> adjacent_marbles;

    // for (long unsigned int i = 0; i < marbles.size(); i++)
    for (space marble : marbles)
    {
        // space marble = marbles[i];
        // for (long unsigned int j = i+1; j < marbles.size(); j++)
        for (space other_marble : marbles)
        {
            // space other_marble = marbles[j];
            if (are_adjacent(marble, other_marble))
            {
                adjacent_marbles.push_back(std::make_tuple(marble,other_marble));
            }
        }
    }

    for (long unsigned int i = 0; i < adjacent_marbles.size(); i++)
    {
        space m1 = std::get<0>(adjacent_marbles[i]);
        space m2 = std::get<1>(adjacent_marbles[i]);
        space potential1 = find_landing(m1, m2);
        space potential2 = find_landing(m2, m1);
        // for (long unsigned int j = 0; j < empty_spaces.size(); j++)
        for (space landing : empty_spaces)
        {
            // space landing = empty_spaces[j];
            if (potential1 == landing)
            {
                valid_moves.push_back(std::make_tuple(m1, m2, landing));
            }
            else if (potential2 == landing)
            {
                valid_moves.push_back(std::make_tuple(m2, m1, landing));
            }
        }
    }
    return valid_moves;
}

space State::find_landing(space m1, space m2)
{
    int x1 = std::get<0>(m1);
    int y1 = std::get<1>(m1);
    int x2 = std::get<0>(m2);
    int y2 = std::get<1>(m2);
    int x3 = 2*x2 - x1;
    int y3 = 2*y2 - y1;
    return std::make_tuple(x3, y3);
}

bool State::are_adjacent(space marble, space other_marble)
{
    if (std::get<0>(marble) == std::get<0>(other_marble))
    {
        if (std::get<1>(marble) == std::get<1>(other_marble) - 1)
        {
            return true;
        }
        else if (std::get<1>(marble) == std::get<1>(other_marble) + 1)
        {
            return true;
        }
    }
    else if (std::get<1>(marble) == std::get<1>(other_marble))
    {
        if (std::get<0>(marble) == std::get<0>(other_marble) - 1)
        {
            return true;
        }
        else if (std::get<0>(marble) == std::get<0>(other_marble) + 1)
        {
            return true;
        }
    }
    return false;
}

void State::print_state()
{
    std::cout << "Current state of board" << std::endl;
    // long unsigned int no_marbles = marbles.size();
    // for (long unsigned int i = 0; i < no_marbles; i++)
    for (space marble : marbles)
    {
        // space marble = marbles[i];
        std::cout << "Marble: " << std::get<0>(marble) << ", " << std::get<1>(marble) << std::endl;
    }
    // long unsigned int no_spaces = empty_spaces.size();
    // for (long unsigned int i = 0; i < no_spaces; i++)
    for (space space : empty_spaces)
    {
        // space space = empty_spaces[i];
        std::cout << "Space: " << std::get<0>(space) << ", " << std::get<1>(space) << std::endl;
    }
}