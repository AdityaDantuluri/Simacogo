#pragma once
#pragma once
#include <vector>
#include <list>

using namespace std;

class Node { //Node class for neat tree traversal
public:
	vector<vector<char>> board;
	int ply;
	int plyMax;
	int bScore;
	int wScore;
	char actor;
	char opponent;
	Node() {};
};


class Board {
public:
	int bScore;
	int wScore;
	vector<vector<char>> board;
	Board() {};
};