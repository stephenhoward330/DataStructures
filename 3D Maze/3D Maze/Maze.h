#ifndef MAZE_H
#define MAZE_H

#include "MazeInterface.h"
#include <sstream>
#include <string>
using namespace std;

class Maze : public MazeInterface {
private:
	enum squares {OPEN, BLOCKED, PATH, EXIT, TEMPORARY, LEFT, RIGHT, UP, DOWN, IN, OUT};
	int height;
	int width;
	int layer;
	int*** myMaze;
public:
	Maze(int h, int w, int l) {
		height = h;
		width = w;
		layer = l;
		myMaze = new int**[height];
		for (int i = 0; i < height; ++i) {
			myMaze[i] = new int*[width];
			for (int j = 0; j < width; ++j) {
				myMaze[i][j] = new int[layer];
			}
		}
	}
	~Maze() {
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				delete[] myMaze[i][j];
			}
			delete[] myMaze[i];
		}
		delete[] myMaze;
	}

	/** Set maze value
		@parm height
		@parm width
		@parm layer
		@parm value
	*/
	virtual void setValue(int height, int width, int layer, int value) {
		myMaze[height][width][layer] = value;
	}

	/** Wrapper for maze path function */
	virtual bool find_maze_path() {
		return find_maze_path(0, 0, 0); // (0,0,0) is the start point
	}

	/** Solve maze
	@return true if solvable, else false
	*/
	bool find_maze_path(int h, int w, int l) {
		// check boundary (base case #1)
		if ((h < 0) || (h >= height) || (w < 0) || 
			(w >= width) || (l < 0) || (l >= layer)) return false;

		if (myMaze[h][w][l] != OPEN) return false; // blocked (base case #2)

		if ((h == height - 1) && (w == width - 1) && (l == layer - 1)) {
			myMaze[h][w][l] = EXIT; // Success! (base case #3)
			return true;
		}

		myMaze[h][w][l] = PATH; // Recursive case
		if (find_maze_path(h, w - 1, l)) { //left
			myMaze[h][w][l] = LEFT;
			return true;
		}
		if (find_maze_path(h, w + 1, l)) { //right
			myMaze[h][w][l] = RIGHT;
			return true;
		}
		if (find_maze_path(h - 1, w, l)) { //up
			myMaze[h][w][l] = UP;
			return true;
		}
		if (find_maze_path(h + 1, w, l)) { //down
			myMaze[h][w][l] = DOWN;
			return true;
		}
		if (find_maze_path(h, w, l - 1)) { //out
			myMaze[h][w][l] = OUT;
			return true;
		}
		if (find_maze_path(h, w, l + 1)) { //in
			myMaze[h][w][l] = IN;
			return true;
		}
		myMaze[h][w][l] = TEMPORARY;
		return false;
	}

	/** Output maze (same order as input maze)
		@return string of xx layers
	*/
	virtual string toString() const {
		ostringstream oss;
		for (int i = 0; i < layer; i++) {
			oss << "Layer " << i+1 << endl;
			for (int j = 0; j < height; j++) {
				for (int k = 0; k < width; k++) {
					if (myMaze[j][k][i] == 0 || myMaze[j][k][i] == 4) { //Open or temporary
						oss << " _";
					}
					else if (myMaze[j][k][i] == 1) { //Blocked
						oss << " X";
					}
					else if (myMaze[j][k][i] == 2 || myMaze[j][k][i] == 5 || myMaze[j][k][i] == 6 || //Path
						myMaze[j][k][i] == 7 || myMaze[j][k][i] == 8 || myMaze[j][k][i] == 9 || myMaze[j][k][i] == 10) {
						oss << " 2";
					}
					else if (myMaze[j][k][i] == 3) { //Exit
						oss << " 3";
					}
				}
				oss << endl;
			}
		}
		return oss.str();
	}

	/** Output maze with directions (same order as input maze)
	@return string of xx layers
	*/
	string bonusToString() const {
		ostringstream oss;
		for (int i = 0; i < layer; i++) {
			oss << "Layer " << i + 1 << endl;
			for (int j = 0; j < height; j++) {
				for (int k = 0; k < width; k++) {
					if (myMaze[j][k][i] == 0 || myMaze[j][k][i] == 4) { //Open or temporary
						oss << " _";
					}
					else if (myMaze[j][k][i] == 1) { //Blocked
						oss << " X";
					}
					else if (myMaze[j][k][i] == 5) { //Left
						oss << " L";
					}
					else if (myMaze[j][k][i] == 6) { //Right
						oss << " R";
					}
					else if (myMaze[j][k][i] == 7) { //Up
						oss << " U";
					}
					else if (myMaze[j][k][i] == 8) { //Down
						oss << " D";
					}
					else if (myMaze[j][k][i] == 9) { //In
						oss << " I";
					}
					else if (myMaze[j][k][i] == 10) { //Out
						oss << " O";
					}
					else if (myMaze[j][k][i] == 3) { //Exit
						oss << " E";
					}
				}
				oss << endl;
			}
		}
		return oss.str();
	}

};

#endif