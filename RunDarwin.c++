/** @file RunDarwin.c++
 *  @brief includes main
 *   
 * to see the movements of the creatures on the grid (darwin)
 */

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Darwin.h"

// compile
// g++ -pedantic -std=c++11 -Wall Darwin.c++ RunDarwin.c++ -o RunDarwin
// ----
// main
// ----


direction intToDirection(int i) {
    direction dir;
    switch(i) {
        case 0: dir = WEST; break;
        case 1: dir = NORTH; break;
        case 2: dir = EAST; break;
        case 3: dir = SOUTH; break;
    }
    return dir;
}


int main () {
    using namespace std;
    // ----
    // food
    // ----

    Species food('f');
    food.addInstruction(instruction::left,0);
    food.addInstruction(go,0);

    // ------
    // hopper
    // ------

    Species hopper('h');
    hopper.addInstruction(hop,0);
    hopper.addInstruction(go,0);

    // -----
    // rover
    // -----
    Species rover('r');
    rover.addInstruction(if_enemy,9);
    rover.addInstruction(if_empty,7);
    rover.addInstruction(if_random,5);
    rover.addInstruction(instruction::left,0);
    rover.addInstruction(go,0);
    rover.addInstruction(instruction::right,0);
    rover.addInstruction(go,0);
    rover.addInstruction(hop,0);
    rover.addInstruction(go,0);
    rover.addInstruction(infect,0);
    rover.addInstruction(go,0);

    // ----
    // trap
    // ----
    Species trap('t');
    trap.addInstruction(if_enemy,3);
    trap.addInstruction(instruction::left,0);
    trap.addInstruction(go,0);
    trap.addInstruction(infect,0);
    trap.addInstruction(go,0);

    // ----------
    // darwin 8x8
    // ----------
    {
        cout << "*** Darwin 8x8 ***" << endl;
        Darwin x(8,8);
        Creature food1(food,EAST);
        x.addCreature(food1,0,0);
        Creature hopper1(hopper,NORTH);
        x.addCreature(hopper1,3,3);
        Creature hopper2(hopper,EAST);
        x.addCreature(hopper2,3,4);
        Creature hopper3(hopper,SOUTH);
        x.addCreature(hopper3,4,4);
        Creature hopper4(hopper,WEST);
        x.addCreature(hopper4,4,3);
        Creature food2(food,NORTH);
        x.addCreature(food2,7,7);
        /*
        8x8 Darwin
        Food,   facing east,  at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
    */
        cout<<"Turn = 0"<<endl;
        x.print(cout);
        for(int i = 1;i<=5;++i) {
            cout<<"Turn = "<<i<<endl;
            x.move();
            x.print(cout);
        }
    }
    // ----------
    // darwin 7x9
    // ----------

    cout << "*** Darwin 7x9 ***" << endl;
    srand(0);
    {
        Darwin x(7,9);
        Creature trap1(trap,SOUTH);
        x.addCreature(trap1,0,0);
        Creature hopper1(hopper,EAST);
        x.addCreature(hopper1,3,2);
        Creature rover1(rover,NORTH);
        x.addCreature(rover1,5,4);
        Creature trap2(trap,WEST);
        x.addCreature(trap2,6,8);
        cout<<"Turn = 0"<<endl;
        x.print(cout);
        for(int i = 1;i<=5;++i) {
            cout<<"Turn = "<<i<<endl;
            x.move();
            x.print(cout);
        }
    }
    /*
    7x9 Darwin
    Trap,   facing south, at (0, 0)
    Hopper, facing east,  at (3, 2)
    Rover,  facing north, at (5, 4)
    Trap,   facing west,  at (6, 8)
    Simulate 5 moves.
    Print every grid.
    */

    // ------------
    // darwin 72x72
    // without best
    // ------------

    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);
    {
        Darwin x(72,72);
        for(int i = 0;i<10;++i) {
            int location = rand()%5184;
            direction dir = intToDirection(rand()%4);
            Creature creature(food,dir);
            bool placed = false;
            placed = x.addCreature(creature,location/72,location%72);
            while(!placed)  {
                location = rand()%5184;
                placed = x.addCreature(creature,location/72,location%72);
            }
        }
        for(int i = 0;i<10;++i) {
            int location = rand()%5184;
            direction dir = intToDirection(rand()%4);
            Creature creature(hopper,dir);
            bool placed = false;
            placed = x.addCreature(creature,location/72,location%72);
            while(!placed)  {
                location = rand()%5184;
                placed = x.addCreature(creature,location/72,location%72);
            }
        }
        for(int i = 0;i<10;++i) {
            int location = rand()%5184;
            direction dir = intToDirection(rand()%4);
            Creature creature(rover,dir);
            bool placed = false;
            placed = x.addCreature(creature,location/72,location%72);
            while(!placed)  {
                location = rand()%5184;
                placed = x.addCreature(creature,location/72,location%72);
            }
        }
        for(int i = 0;i<10;++i) {
            int location = rand()%5184;
            direction dir = intToDirection(rand()%4);
            Creature creature(trap,dir);
            bool placed = false;
            placed = x.addCreature(creature,location/72,location%72);
            while(!placed)  {
                location = rand()%5184;
                placed = x.addCreature(creature,location/72,location%72);
            }
        }
        cout<<"Turn = 0."<<endl;
        x.print(cout);
        x.move();
        for(int turn = 1; turn < 1000 + 1; ++turn) {
            if(turn < 10 || turn % 100 == 0) {
                cout << "Turn = " << turn <<"."<<endl;
                x.print(cout);
            }
            x.move();
        }
    }
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    // ------------
    // darwin 72x72
    // with best
    // ------------

    cout << "*** Darwin 72x72 with Best ***" << endl;
    Species best('b');
    
    best.addInstruction(if_enemy,10);
    best.addInstruction(if_empty,8);
    best.addInstruction(if_wall,12);
    best.addInstruction(if_random,6);
    best.addInstruction(instruction::left,0);
    best.addInstruction(go,0);
    best.addInstruction(instruction::right,0);
    best.addInstruction(go,0);
    best.addInstruction(hop,0);
    best.addInstruction(go,0);
    best.addInstruction(infect,0);
    best.addInstruction(go,0);
    best.addInstruction(instruction::right,0);
    best.addInstruction(if_enemy,18);
    best.addInstruction(if_empty,20);
    best.addInstruction(if_wall,25);
    best.addInstruction(instruction::right,0);
    best.addInstruction(go,0);
    best.addInstruction(infect,0);
    best.addInstruction(go,13);
    best.addInstruction(hop,0);
    best.addInstruction(go,13);
    best.addInstruction(hop,0);
    best.addInstruction(instruction::right,0);
    best.addInstruction(go,0);
    best.addInstruction(instruction::right,0);
    best.addInstruction(go,22);

    srand(0);
    {
        Darwin x(72,72);
        for(int i = 0;i<10;++i) {
            int location = rand()%5184;
            direction dir = intToDirection(rand()%4);
            Creature creature(food,dir);
            bool placed = false;
            placed = x.addCreature(creature,location/72,location%72);
            while(!placed)  {
                location = rand()%5184;
                placed = x.addCreature(creature,location/72,location%72);
            }
        }
        for(int i = 0;i<10;++i) {
            int location = rand()%5184;
            direction dir = intToDirection(rand()%4);
            Creature creature(hopper,dir);
            bool placed = false;
            placed = x.addCreature(creature,location/72,location%72);
            while(!placed)  {
                location = rand()%5184;
                placed = x.addCreature(creature,location/72,location%72);
            }
        }
        for(int i = 0;i<10;++i) {
            int location = rand()%5184;
            direction dir = intToDirection(rand()%4);
            Creature creature(rover,dir);
            bool placed = false;
            placed = x.addCreature(creature,location/72,location%72);
            while(!placed)  {
                location = rand()%5184;
                placed = x.addCreature(creature,location/72,location%72);
            }
        }
        for(int i = 0;i<10;++i) {
            int location = rand()%5184;
            direction dir = intToDirection(rand()%4);
            Creature creature(trap,dir);
            bool placed = false;
            placed = x.addCreature(creature,location/72,location%72);
            while(!placed)  {
                location = rand()%5184;
                placed = x.addCreature(creature,location/72,location%72);
            }
        }
        for(int i = 0;i<10;++i) {
            int location = rand()%5184;
            direction dir = intToDirection(rand()%4);
            Creature creature(best,dir);
            bool placed = false;
            placed = x.addCreature(creature,location/72,location%72);
            while(!placed)  {
                location = rand()%5184;
                placed = x.addCreature(creature,location/72,location%72);
            }
        }
        cout<<"Turn = 0."<<endl;
        x.print(cout);
        x.move();
        for(int turn = 1; turn < 1000 + 1; ++turn) {
            if(turn < 10 || turn % 100 == 0) {
                cout << "Turn = " << turn <<"."<<endl;
                x.print(cout);
            }
            x.move();
        }
    }
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: 0:west, 1:north, 2:east, 3:south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    return 0;}
