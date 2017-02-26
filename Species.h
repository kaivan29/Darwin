/** @file Species.h
 *  @brief Creates different species of the creature
 *   
 * Each species has a certain set of instruction that it follows
 */

#include <vector>
#include <cstring>
#include <string>
#include <cstdlib>

using namespace std;

enum instruction {
	hop,
	left,
	right,
	infect,
	if_empty,
	if_wall,
	if_random,
	if_enemy,
	go
};

class Species {
	private:
		vector<pair<instruction,int>> program;
		char type;
	public:
		FRIEND_TEST(TestSpecies, addInstruction1);
		FRIEND_TEST(TestSpecies, addInstruction2);
		FRIEND_TEST(TestSpecies, addInstruction3);
		FRIEND_TEST(TestSpecies, addInstruction4);
		
		//default constructor is empty
		Species(char c = 'a') {
			type = c;
		}
		
		/*
		* @param instruct instruction to be added
		* @param i int that points to the next line number
		* add instruction to the species' program
		*/
		void addInstruction(instruction instruct, int i) {
			program.push_back(make_pair(instruct,i));
		}
		
		/*
		* @param pc current program counter of the species
		* @param isEmpty whether the next square is empty
		* @param isWall whether the creature is facing a wall
		* @param isEnemy whether the creature is facing an enemy
		* <br> call the instruction
		*/
		instruction callInstruction(int* pc, bool isEmpty, bool isWall, bool isEnemy) {
			while(1 > 0) {
				switch(program[*pc].first) {
					case hop: ++*pc; return hop;
					case instruction::left: ++*pc; return instruction::left;
					case instruction::right: ++*pc; return instruction::right;
					case infect: ++*pc; return infect;
					case if_empty: 
						if(isEmpty) *pc = program[*pc].second;
						else ++*pc; break;
					case if_wall: 
						if(isWall) *pc = program[*pc].second;
						else ++*pc; break;
					case if_enemy: 
						if(isEnemy) *pc = program[*pc].second;
						else ++*pc; break;
					case if_random:
						if(rand() % 2 == 1) *pc = program[*pc].second;
						else ++*pc; break;
					case go: *pc = program[*pc].second; break;
				}
			}
			return hop;
		}
		
		/*
		* @param w the ostream
		* <br>ostream prints the char of the species
		*/
		void printSpecies(ostream& w) {
			w<<type;
		}
		
		/*
		* @param species species to be compared to
		* <br>whether the species in the argument is the same
		*/
		bool matches(Species species) {
			return type == species.type;
		}

};
