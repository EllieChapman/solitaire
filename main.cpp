#include <iostream>
#include "state.h"
#include "utils.h"
#include <set>

std::list<move> moves_done;

// When create state from applying move, check if already been here
// If not, when have done all moves for the state add to list of seen states and update num_seen_states
std::set <std::set<std::tuple<int,int>>> seen_states;
int num_seen_states = 0;

void add_rotations_and_reflections(std::set<space> marbles)
{
    // 3 times, rotate 90 degrees aroutn 4,4, then add to seen states
    // EBC make this better when class holds as a state anyway

    // Initial reflection
    std::set<space> initial_reflected_marbles {};
    for (auto marble : marbles)
    {
        initial_reflected_marbles.insert(reflect_point(marble));
    }
    seen_states.insert(initial_reflected_marbles);

    // 1st rotation and reflection
    std::set<space> rotated_marbles {};
    for (auto marble : marbles)
    {
        rotated_marbles.insert(rotate_point(marble));
    }
    seen_states.insert(rotated_marbles);

    std::set<space> reflected_marbles {};
    for (auto marble : rotated_marbles)
    {
        reflected_marbles.insert(reflect_point(marble));
    }
    seen_states.insert(reflected_marbles);

    // 2nd rotation and reflecction
    std::set<space> rotated_marbles2 {};
    for (auto marble : rotated_marbles)
    {
        rotated_marbles2.insert(rotate_point(marble));
    }
    seen_states.insert(rotated_marbles2);

    std::set<space> reflected_marbles2 {};
    for (auto marble : rotated_marbles2)
    {
        reflected_marbles2.insert(reflect_point(marble));
    }
    seen_states.insert(reflected_marbles2);

    // 3nd rotation and reflecction
    std::set<space> rotated_marbles3 {};
    for (auto marble : rotated_marbles2)
    {
        rotated_marbles3.insert(rotate_point(marble));
    }
    seen_states.insert(rotated_marbles3);

    std::set<space> reflected_marbles3 {};
    for (auto marble : rotated_marbles3)
    {
        reflected_marbles3.insert(reflect_point(marble));
    }
    seen_states.insert(reflected_marbles3);

}

int do_move(State s, move m)
{
    s.apply_move(m);
    // check if state has been seen before
    seen_states.insert(s.marbles);
    int size = seen_states.size();
    if (num_seen_states == size)
    {
        return 1;
    }
    else
    {
        // add_rotations_and_reflections(s.marbles);
        num_seen_states = size; // EBC no guarentee to be 8
        
    }
    // if not, recurse
    moves_done.push_back(m);
    std::list<move> moves = s.generate_valid_moves();
    while (moves.size() > 0)
    {
        int rc = do_move(s, moves.front());
        if (rc == 0)
        {
            return 0;
        }
        else
        {
            moves.pop_front();
        }
    }
    if (s.marbles.size() == 1)
    {
        // EBC also store off winning thing here?
        std::cout << "Found a solution!\n";
        std::cout << "Solution moves:\n";
        for (auto move : moves_done)
        {
            print_move(move);
        }
        return 0; // EBC also pop when find multiple
    }
    else
    {
        // std::cout << "No solution found, backtracking\n"; // EBC good for debugging
        moves_done.pop_back();
        return 1;
    }
}

void play_game()
{
    State initial_state;
    initial_state.print_state();
    std::list<move> moves = initial_state.generate_valid_moves();
    while (moves.size() > 0)
    {
        int rc = do_move(initial_state, moves.front());
        if (rc == 0)
        {
            std::cout << "Completed successfully!\n";
            break;
        }
        else
        {
            moves.pop_front();
        }
    }
    if (moves.size() == 0)
    {
        std::cout << "Completed with no solution found\n";
    }
}


int main ()
{
    std::cout << "Starting game!\n";
    play_game();
    return 0;
}


// Wnat something which represents state (do i just store marbles, or also spaces? for speed?)
// want something which represents a move (ie a set of three consequtive spaces, one which is currently empty)

// find_moves function, takes a state, returns a list of moves

// global list of moves done

// each level can call find_moves, then do_move passing in state and first move in list. Add move to list of moves done
    // If get back a 0, found a solution! Return 0
    // If get back a 1 all was tried.
        // If there are moves left, replace end move in global list and do_move
        // If there are no moves left, remove end move in global list and return 1
// if find_moves returns 0 moves, check if we have won
    // If we have won, return 0 (also store off current state of global list of moves done, important for finding multiple solutions later)
    // If we have not won, return 1
