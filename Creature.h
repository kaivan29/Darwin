/** @file Creature.h
 *  @brief Tracks the movement of creatures
 *   
 * It handles the movement of the creatures. move left, right and infect the enemies
 */


#include "Species.h"
#include <ostream>

using namespace std;
enum direction {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

class Creature {
	private:
		int pc;
		Species species;
		direction dir;
	public:
		FRIEND_TEST(TestCreature, turnLeft1);
		FRIEND_TEST(TestCreature, turnLeft2);
		FRIEND_TEST(TestCreature, turnLeft3);
		FRIEND_TEST(TestCreature, turnLeft4);
		FRIEND_TEST(TestCreature, turnLeft5);
		FRIEND_TEST(TestCreature, turnLeft6);
		FRIEND_TEST(TestCreature, turnLeft7);
		FRIEND_TEST(TestCreature, turnLeft8);
		FRIEND_TEST(TestCreature, turnRight1);
		FRIEND_TEST(TestCreature, turnRight2);
		FRIEND_TEST(TestCreature, turnRight3);
		FRIEND_TEST(TestCreature, turnRight4);
		FRIEND_TEST(TestCreature, turnRight5);
		FRIEND_TEST(TestCreature, turnRight6);
		FRIEND_TEST(TestCreature, turnRight7);
		FRIEND_TEST(TestCreature, turnRight8);
		FRIEND_TEST(TestCreature, infect1);
		FRIEND_TEST(TestCreature, infect2);
		
		Creature(Species& s, direction d) {
			species = s;
			dir = d;
			pc = 0;
		}
		
		/*
		* turn the creature to the left
		*/
		void turnLeft() {
			switch(dir) {
				case NORTH: dir = WEST; break;
				case EAST: dir = NORTH; break;
				case SOUTH: dir = EAST; break;
				case WEST: dir = SOUTH; break;
			}
		}
		
		/*
		* turn the creature to the right
		*/
		void turnRight() {
			switch(dir) {
				case NORTH: dir = EAST; break;
				case EAST: dir = SOUTH; break;
				case SOUTH: dir = WEST; break;
				case WEST: dir = NORTH; break;
			}
		}
		
		/*
		* @param c creature to be infected
		* <br>changes the creature to be the same species
		*/
		void infectCreature(Creature& c) {
			c.species = species;
			c.pc = 0;
		}
		
		/*
		* @param creatures vector of each creature to the north, south, east and west and their relational direction
		* @param wallCode wallCode for the creatures' spot in the grid
		* @return the instruction called and the new direction the creature is facing
		* <br> move the creature
		*/
		pair<instruction,direction> move(vector<pair<Creature*,direction>>& creatures, int wallCode) {
			bool isEmpty = true;
			bool isEnemy = false;
			bool isWall = false;
			Creature* toInfect = nullptr;
			for(int i = 0;i<(int)creatures.size();i++) {
				if(creatures[i].second == dir) {
					Creature c = *creatures[i].first;
					if(!c.species.matches(species)) {
						isEnemy = true;
						toInfect = creatures[i].first;
					}
					isEmpty = false;
				}
			}
			switch(dir) {
				case NORTH: if(wallCode < 4 && wallCode > 0) {
					isWall = true; isEmpty = false; } break;
				case EAST: if(wallCode < 6 && wallCode > 2) {
					isWall = true; isEmpty = false; } break;
				case SOUTH: if(wallCode < 8 && wallCode > 4) {
					isWall = true; isEmpty = false; } break;
				case WEST: if(wallCode > 6 || wallCode == 1) {
					isWall = true; isEmpty = false; } break;
			}
			instruction command = species.callInstruction(&pc,isEmpty,isWall,isEnemy);
			switch(command) {
				case hop: return make_pair(hop,dir);
				case instruction::left: turnLeft(); break;
				case instruction::right: turnRight(); break;
				case infect: if(isEnemy) infectCreature(*toInfect); break;
				default: break;
			}
			return make_pair(command,dir);
		}
		
		/*
		* @param ostream
		* <br> print the species for the creature into the ostream
		*/
		void printCreature(ostream& w) {
			species.printSpecies(w);
		}

};