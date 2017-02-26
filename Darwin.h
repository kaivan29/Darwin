/** @file Darwin.h
 *  @brief Creates a grid of creatures
 *   
 * 
 */


#ifndef Darwin_h
#define Darwin_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstddef>   // ptrdiff_t, size_t
#include <new>       // bad_alloc, new
#include <stdexcept> // invalid_argument
#include <vector>
#include "gtest/gtest_prod.h"

#include "Creature.h"

using namespace std;
// ---------
// Darwin
// ---------

class Darwin {
    private:
        // ----
        // data
        // ----
        vector<vector<int>> grid;
        vector<Creature> creatures;
        vector<pair<int,int>> creaturePos;
        int columnSize;
        int rowSize;


    public:
        FRIEND_TEST(TestDarwin, addCreature1);
        FRIEND_TEST(TestDarwin, moveCreature1);
        FRIEND_TEST(TestDarwin, moveCreature2);
        FRIEND_TEST(TestDarwin, move1);
        FRIEND_TEST(TestDarwin, move2);
        // ------------
        // constructors
        // ------------

        /**
        // default constructor, automatic 10X10 implementation
         */
        Darwin ();
        //construct with grid of size x by y
        Darwin (int x, int y);
        //place Creature c at location x, y facing direction d
        bool addCreature(Creature& c, int x, int y);
        void moveCreature(Creature& c, pair<int,int> p);
        void move();
        int wallCode(pair<int,int> p);
        void print(ostream& w);

};

#endif
