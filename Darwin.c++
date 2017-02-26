/** @file Darwin.c++
 *  @brief Creates a grid of creatures
 *   
 * It handles the movement of the creatures. Handles  the wallcodel,
 */

// --------
// includes
// --------

#include <vector>
#include <list>
#include <iostream> 

#include "Darwin.h"

using namespace std;

/*
 * <br> Creates default grid of 10X10
 */
Darwin::Darwin():grid(10, vector<int>(10,-1)) {
	rowSize = grid.size();
	columnSize = grid.at(0).size();
        }

/*
* @param x the number of rows
* @param y the number of columns
* <br> Creates a grid of x by y
*/
Darwin::Darwin(int x, int y):grid(x, vector<int>(y,-1)) {
	rowSize = grid.size();
	columnSize = grid.at(0).size();
        }

/*
* @param c the creature to be added to the grid
* @param x the row number the creature is being added to
* @param y the column number the creature is being added to
* @return whether the add was successful
* <br> adds a creature to the grid
*/
bool Darwin::addCreature(Creature& c, int x, int y) {
	if(grid[x][y] != -1)
		return false;
	creatures.push_back(c);
	grid[x][y] = creatures.size() - 1;
	creaturePos.push_back(make_pair(x,y));
	return true;
}

/*
* @param p a coordinate pair location in the grid
* <br> returns the wall, if any that the coordianate is next to
*/
int Darwin::wallCode(const pair<int,int> p) {
	int x = p.first;
	int y = p.second;
	if(x == 0) {
		if(y == 0)
			return 1;
		if(y == columnSize-1)
			return 3;
		return 2;
	}
	if(x == rowSize-1) {
		if(y == 0)
			return 7;
		if(y == columnSize-1)
			return 5;
		return 6;
	}
	if(y == 0)
		return 8;
	if(y == columnSize - 1)
		return 4;
	return 0;
}

/*
* @param c the creature to be moved
* @param p the creatures coordinate pair location
* <br> move a creature in the grid
*/
void Darwin::moveCreature(Creature& c, pair<int,int> p) {
	int row = p.first;
	int column = p.second;
	vector<pair<Creature*,direction>> surroundingCreatures;
	if(row != 0) {
		int creatureNumber = grid[row-1][column];
		if(creatureNumber != -1)
			surroundingCreatures.push_back(make_pair(&creatures[creatureNumber],NORTH));
	}
	if(row != rowSize-1) {
		int creatureNumber = grid[row+1][column];
		if(creatureNumber != -1)
			surroundingCreatures.push_back(make_pair(&creatures[creatureNumber],SOUTH));
	}
	if(column != 0) {
		int creatureNumber = grid[row][column-1];
		if(creatureNumber != -1)
			surroundingCreatures.push_back(make_pair(&creatures[creatureNumber],WEST));
	}
	if(column != columnSize-1) {
		int creatureNumber = grid[row][column+1];
		if(creatureNumber != -1)
			surroundingCreatures.push_back(make_pair(&creatures[creatureNumber],EAST));
	}
	pair<instruction,direction> command = c.move(surroundingCreatures,wallCode(p));
	if(command.first == hop) {
		bool moved = false;
		int newRow = row;
		int newColumn = column;
		switch(command.second) {
			case NORTH: if(row > 0) {--newRow; moved = true; } break;
			case EAST: if(column < columnSize-1) {++newColumn; moved = true; } break;
			case SOUTH: if(row < rowSize-1) {++newRow; moved = true; } break;
			case WEST: if(column > 0) {--newColumn; moved = true;} break;
		}
		if(moved && grid[newRow][newColumn] == -1) {
			int creatureNumber = grid[row][column];
			grid[newRow][newColumn] = creatureNumber;
			grid[row][column] = -1;
			creaturePos[creatureNumber] = make_pair(newRow,newColumn);
		}
	}
}

/*
* <br> move all creatures in the grid
*/
void Darwin::move() {
	list<int> creatureList;
	for(int y = 0;y<rowSize;++y)
		for(int x = 0;x<columnSize;++x) {
			int creatureNumber = grid[y][x];
			if(creatureNumber >= 0)
				creatureList.push_back(grid[y][x]);
		}
	list<int>::iterator index = creatureList.begin();
	while(index != creatureList.end()) {
		moveCreature(creatures.at(*index), creaturePos.at(*index));
		++index;
	}
}	

/*
* print everything in the grid
*/
void Darwin::print(ostream& w) {
	{
	w<<"  ";
	for(int x = 0;x<columnSize;++x)
		w<<x%10;
	w<<endl;
	}
	for(int y = 0;y<rowSize;++y) {
		w<<y%10<<" ";
		for(int x = 0;x<columnSize;++x) {
			int creatureNumber = grid[y][x];
			if(creatureNumber == -1)
				w<<".";
			else
				creatures[creatureNumber].printCreature(w);
		}
		w<<endl;
	}
	w<<endl;
}
