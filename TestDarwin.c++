/** @file TestDarwin.c++
 *  @brief Unit Tests 
 *   
*/

#include <string>
#include <iostream>
#include <cassert>

#include "Darwin.h"

#include "gtest/gtest.h"

using namespace std;
using std::ostringstream;

/*g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 
-Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lgtest_main -lpthread*/

Species food('f');
Species hopper('h');
Species trap('t');
Species rover('r');


//------------TestSpecies-------------------

//
// print species
//
TEST(TestSpecies, printSpecies1) {
	Species s('h');
	ostringstream sout;
	s.printSpecies(sout);
	ASSERT_EQ(sout.str(),"h");
}

TEST(TestSpecies, printSpecies2) {
	Species s('s');
	ostringstream sout;
	s.printSpecies(sout);
	ASSERT_EQ(sout.str(),"s");
}

//
// addInstruction
//
TEST(TestSpecies, addInstruction1) {
	food.addInstruction(instruction::left,0);
	food.addInstruction(go,0);
	ASSERT_EQ(food.program[0], make_pair(instruction::left,0));
	ASSERT_EQ(food.program[1], make_pair(go,0));
}

TEST(TestSpecies, addInstruction2) {
	hopper.addInstruction(hop,0);
	hopper.addInstruction(go,0);
	ASSERT_EQ(hopper.program[0], make_pair(hop,0));
	ASSERT_EQ(hopper.program[1], make_pair(go,0));
}

TEST(TestSpecies, addInstruction3) {
	trap.addInstruction(if_enemy,3);
    trap.addInstruction(instruction::left,0);
    trap.addInstruction(go,0);
    trap.addInstruction(infect,0);
    trap.addInstruction(go,0);
	ASSERT_EQ(trap.program[0], make_pair(if_enemy,3));
	ASSERT_EQ(trap.program[4], make_pair(go,0));
}

TEST(TestSpecies, addInstruction4) {
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
	ASSERT_EQ(rover.program[0], make_pair(if_enemy,9));
	ASSERT_EQ(rover.program[5], make_pair(instruction::right,0));
	ASSERT_EQ(rover.program[10], make_pair(go,0));
}

//
// callInstruction
//
TEST(TestSpecies, callInstruction1) {
	int pc = 0;
	instruction command = food.callInstruction(&pc,true,false,false);
	ASSERT_EQ(command,instruction::left);
	ASSERT_EQ(pc,1);
}

TEST(TestSpecies, callInstruction2) {
	int pc = 0;
	instruction command = hopper.callInstruction(&pc,true,false,false);
	ASSERT_EQ(command,hop);
	ASSERT_EQ(pc,1);
}
TEST(TestSpecies, callInstruction3) {
	int pc = 0;
	instruction command = trap.callInstruction(&pc,true,false,false);
	ASSERT_EQ(command,instruction::left);
	ASSERT_EQ(pc,2);
}
TEST(TestSpecies, callInstruction4) {
	int pc = 0;
	instruction command = trap.callInstruction(&pc,false,false,true);
	ASSERT_EQ(command,infect);
	ASSERT_EQ(pc,4);
}

TEST(TestSpecies, callInstruction5) {
	int pc = 0;
	instruction command = rover.callInstruction(&pc,true,false,false);
	ASSERT_EQ(command,hop);
	ASSERT_EQ(pc,8);
}

TEST(TestSpecies, callInstruction6) {
	int pc = 0;
	srand(0);
	instruction command = rover.callInstruction(&pc,false,false,false);
	ASSERT_EQ(command,instruction::right);
	ASSERT_EQ(pc,6);
}

TEST(TestSpecies, callInstruction7) {
	int pc = 0;
	srand(2);
	instruction command = rover.callInstruction(&pc,false,false,false);
	ASSERT_EQ(command,instruction::left);
	ASSERT_EQ(pc,4);
}


TEST(TestSpecies, callInstruction8) {
	int pc = 0;
	instruction command = rover.callInstruction(&pc,false,false,true);
	ASSERT_EQ(command,infect);
	ASSERT_EQ(pc,10);
}

//matches
TEST(TestSpecies, matches) {
	assert(food.matches(food));
}

//------------TestCreature-------------------

//
// turnLeft
//
TEST(TestCreature, turnLeft1) {
	Creature creature(food,NORTH);
	creature.turnLeft();
	ASSERT_EQ(creature.dir,WEST);
}

TEST(TestCreature, turnLeft2) {
	Creature creature(food,EAST);
	creature.turnLeft();
	ASSERT_EQ(creature.dir,NORTH);
}

TEST(TestCreature, turnLeft3) {
	Creature creature(food,SOUTH);
	creature.turnLeft();
	ASSERT_EQ(creature.dir,EAST);
}

TEST(TestCreature, turnLeft4) {
	Creature creature(food,WEST);
	creature.turnLeft();
	ASSERT_EQ(creature.dir,SOUTH);
}

TEST(TestCreature, turnLeft5) {
	Creature creature(rover,NORTH);
	creature.turnLeft();
	ASSERT_EQ(creature.dir,WEST);
}

TEST(TestCreature, turnLeft6) {
	Creature creature(rover,EAST);
	creature.turnLeft();
	ASSERT_EQ(creature.dir,NORTH);
}

TEST(TestCreature, turnLeft7) {
	Creature creature(rover,SOUTH);
	creature.turnLeft();
	ASSERT_EQ(creature.dir,EAST);
}

TEST(TestCreature, turnLeft8) {
	Creature creature(rover,WEST);
	creature.turnLeft();
	ASSERT_EQ(creature.dir,SOUTH);
}

//
// turnRight
//
TEST(TestCreature, turnRight1) {
	Creature creature(food,NORTH);
	creature.turnRight();
	ASSERT_EQ(creature.dir,EAST);
}

TEST(TestCreature, turnRight2) {
	Creature creature(food,EAST);
	creature.turnRight();
	ASSERT_EQ(creature.dir,SOUTH);
}

TEST(TestCreature, turnRight3) {
	Creature creature(food,SOUTH);
	creature.turnRight();
	ASSERT_EQ(creature.dir,WEST);
}

TEST(TestCreature, turnRight4) {
	Creature creature(food,WEST);
	creature.turnRight();
	ASSERT_EQ(creature.dir,NORTH);
}

TEST(TestCreature, turnRight5) {
	Creature creature(rover,NORTH);
	creature.turnRight();
	ASSERT_EQ(creature.dir,EAST);
}

TEST(TestCreature, turnRight6) {
	Creature creature(rover,EAST);
	creature.turnRight();
	ASSERT_EQ(creature.dir,SOUTH);
}

TEST(TestCreature, turnRight7) {
	Creature creature(rover,SOUTH);
	creature.turnRight();
	ASSERT_EQ(creature.dir,WEST);
}

TEST(TestCreature, turnRight8) {
	Creature creature(rover,WEST);
	creature.turnRight();
	ASSERT_EQ(creature.dir,NORTH);
}
//
// infect
//
TEST(TestCreature, infect1) {
	Creature food1(food,NORTH);
	Creature rover1(rover,SOUTH);
	rover1.infectCreature(food1);
	assert(food1.species.matches(rover));
	ASSERT_EQ(food1.pc,0);
}

TEST(TestCreature, infect2) {
	Creature hopper1(hopper,NORTH);
	Creature rover1(rover,SOUTH);
	hopper1.pc = 1;
	rover1.infectCreature(hopper1);
	assert(hopper1.species.matches(rover));
	ASSERT_EQ(hopper1.pc,0);
}


//
// move
//
TEST(TestCreature, move1) {
	vector<pair<Creature*,direction>> creatures;
	Creature hopper1(hopper,NORTH);
	pair<instruction,direction> command = hopper1.move(creatures,0);
	ASSERT_EQ(command,make_pair(hop,NORTH));
}

TEST(TestCreature, move2) {
	vector<pair<Creature*,direction>> creatures;
	Creature trap1(trap,NORTH);
	Creature hopper1(hopper,SOUTH);
	creatures.push_back(make_pair(&hopper1,EAST));
	pair<instruction,direction> command = trap1.move(creatures,0);
	ASSERT_EQ(command,make_pair(instruction::left,WEST));
}

TEST(TestCreature, move3) {
	vector<pair<Creature*,direction>> creatures;
	Creature trap1(trap,NORTH);
	Creature hopper1(hopper,SOUTH);
	creatures.push_back(make_pair(&hopper1,NORTH));
	pair<instruction,direction> command = trap1.move(creatures,0);
	ASSERT_EQ(command,make_pair(infect,NORTH));
}

TEST(TestCreature, move4) {
	vector<pair<Creature*,direction>> creatures;
	Creature trap1(trap,NORTH);
	Creature trap2(trap,SOUTH);
	creatures.push_back(make_pair(&trap2,NORTH));
	pair<instruction,direction> command = trap1.move(creatures,0);
	ASSERT_EQ(command,make_pair(instruction::left,WEST));
}

TEST(TestCreature, move5) {
	vector<pair<Creature*,direction>> creatures;
	Creature rover1(rover,NORTH);
	Creature rover2(rover,NORTH);
	creatures.push_back(make_pair(&rover2,NORTH));
	srand(0);
	pair<instruction,direction> command = rover1.move(creatures,0);
	ASSERT_EQ(command,make_pair(instruction::right,EAST));
}

TEST(TestCreature, move6) {
	vector<pair<Creature*,direction>> creatures;
	Creature rover1(rover,NORTH);
	pair<instruction,direction> command = rover1.move(creatures,7);
	ASSERT_EQ(command,make_pair(hop,NORTH));
}


//
// printCreature
//
TEST(TestCreature, printCreature) {
	Creature food1(food,NORTH);
	ostringstream sout;
	food1.printCreature(sout);
	ASSERT_EQ(sout.str(),"f");
}


//------------TestDarwin-------------------

//
// addCreature
//
TEST(TestDarwin, addCreature1) {
	Darwin x(10,10);
	Creature food1(food,NORTH);
	x.addCreature(food1,0,0);
	ASSERT_EQ(x.grid[0][0],0);
	ASSERT_EQ(x.creaturePos[0],make_pair(0,0));
}

//
// moveCreature
//
TEST(TestDarwin, moveCreature1) {
	Darwin x(10,10);
	Creature hopper1(hopper,NORTH);
	x.addCreature(hopper1,5,5);
	x.moveCreature(hopper1,make_pair(5,5));
	ASSERT_EQ(x.grid[4][5],0);
}

TEST(TestDarwin, moveCreature2) {
	Darwin x(10,10);
	Creature hopper1(hopper,NORTH);
	x.addCreature(hopper1,0,5);
	x.moveCreature(hopper1,make_pair(0,5));
}

//
// move
//
TEST(TestDarwin, move1) {
	Darwin x(10,10);
	Creature hopper1(hopper,SOUTH);
	x.addCreature(hopper1,5,5);
	Creature hopper2(hopper,EAST);
	x.addCreature(hopper2,6,5);
	x.move();
	ASSERT_EQ(x.grid[5][5],0);
	ASSERT_EQ(x.grid[6][6],1);
}

TEST(TestDarwin, move2) {
	Darwin x(10,10);
	Creature hopper1(hopper,SOUTH);
	x.addCreature(hopper1,5,5);
	x.move();
	ASSERT_EQ(x.grid[6][5],0);
}

//
// wallCode
//
TEST(TestDarwin, wallCode1) {
	Darwin x(10,10);
	int i = x.wallCode(make_pair(5,5));
	ASSERT_EQ(i,0);
}

TEST(TestDarwin, wallCode2) {
	Darwin x(10,10);
	int i = x.wallCode(make_pair(9,9));
	ASSERT_EQ(i,5);
}

TEST(TestDarwin, wallCode3) {
	Darwin x(10,10);
	int i = x.wallCode(make_pair(5,0));
	ASSERT_EQ(i,8);
}

//
// print
//
TEST(TestDarwin, print1) {
	Darwin x(1,1);
	ostringstream sout;
	x.print(sout);
	ASSERT_EQ(sout.str(),"  0\n0 .\n\n");
}

TEST(TestDarwin, print2) {
	Darwin x(1,1);
	Creature food1(food,NORTH);
	x.addCreature(food1,0,0);
	ostringstream sout;
	x.print(sout);
	ASSERT_EQ(sout.str(),"  0\n0 f\n\n");
}

