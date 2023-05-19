#include <iostream>
#include "state.h"
#include "utils.h"


std::list<move> moves_done;

int do_move(State s, move m)
{
    s.apply_move(m);
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
