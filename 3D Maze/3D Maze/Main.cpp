/*
Rodney Recursion
Program finds a path through a 3D Maze
*/

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

#include <fstream>
#include <iostream>
#include <sstream>
#include "Maze.h"

using namespace std;

int main(int argc, char * argv[])
{
	VS_MEM_CHECK
	
	ifstream in(argv[1]);
	ofstream out(argv[2]);

	int numHeight, numWidth, numLayer, num;
	string line;

	getline(in, line);
	istringstream iss(line);
	iss >> numHeight >> numWidth >> numLayer;
	Maze myMaze(numHeight, numWidth, numLayer);
	getline(in, line);

	// Fill maze
	for (int i = 0; i < numLayer; i++) {
		for (int j = 0; j < numHeight; j++) {
			getline(in, line);
			istringstream iss(line);
			for (int k = 0; k < numWidth; k++) {
				iss >> num;
				myMaze.setValue(j, k, i, num);
			}
		}
		getline(in, line); //skip blank line
	}

	// Solve and output maze
	out << "Solve Maze: " << endl << myMaze.toString() << endl;
	if (myMaze.find_maze_path()) { // I guess we only need to output the bonus maze... <('.'<) kirby
		//out << "Solution: " << endl << myMaze.toString() << endl;
		out << "Solution: " << endl << myMaze.bonusToString() << endl;
	}
	else out << "No Solution Exists!" << endl;
	
	system("pause");
	return 0;
}