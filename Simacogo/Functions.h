#pragma once
#pragma once
#include <stdio.h>
#include<iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "Node.h"
using namespace std;
int c = 0;

vector<Node> getChildren(Node pBor, char act) { //Returns all possible move that "act" can make for a give board state
	vector<Node> ret;
	for (int x = 0; x < 9; x++) {
		int t = 8;
		int y = 0;
		int score = 0;
		char temp[9][9];
		if (pBor.board[0][x] == '.') {
			vector<vector<char>> temp = pBor.board;
			do {
				if (pBor.board[t][x] == '.') {
					y = t;
				}
				t--;
			} while ((t > -1) && (y == 0));

			for (int j = -1; j <= 1; j++) {
				for (int i = -1; i <= 1; i++) {
					if (((y + j) > 8) || ((y + j) < 0) || ((x + i) > 8) || ((x + i) < 0)) {
						continue;
					}
					if (pBor.board[y + j][x + i] == act) {
						if ((abs(j) + abs(i)) == 2) {
							score += 1;
						}
						else if ((abs(j) + abs(i)) == 1) {
							score += 2;
						}
						else {
							score += 0;
						}

					}
				}
			}

			Node tempC = pBor;
			if (act == 'X') {
				tempC.bScore += score;
			}
			else {
				tempC.wScore += score;
			}
			tempC.board[y][x] = act;
			ret.push_back(tempC); c++;
		}
	}
	random_shuffle(ret.begin(), ret.end());
	return ret;
}


Board playerMove(Board b, int c) { // drops the players piece at the bottom of the selected column and adjusts score.
	vector<vector<char>> v = b.board;
	int y = 8;
	while (v[y][c] != '.') {
		y--;
		if (y == -1) {
			break;
		}
	};
	if (y == -1) {
		printf("invalid move");
		exit;
	}

	for (int j = -1; j <= 1; j++) {
		for (int i = -1; i <= 1; i++) {
			if (((y + j) > 8) || ((y + j) < 0) || ((c + i) > 8) || ((c + i) < 0)) {
				continue;
			}
			if (b.board[y + j][c + i] == 'O') {
				if ((abs(j) + abs(i)) == 2) {
					b.wScore += 1;
				}
				else if ((abs(j) + abs(i)) == 1) {
					b.wScore += 2;
				}
				else {
					b.wScore += 0;
				}

			}
		}
	}


	v[y][c] = 'O';
	b.board = v;
	return b;
}


Node getMin(Node bBoard);
Node getMax(Node bBoard);

Board getMove(Board bBoard, int plyMax, char actor, char opponent) { //Sets up the recusion behind the scenes adn returns the board state resulting from the AI's best move.
	Node root; 
	root.board = bBoard.board;
	root.bScore = bBoard.bScore;
	root.wScore = bBoard.wScore;
	root.ply = 1;
	root.plyMax = plyMax;
	root.actor = actor;
	root.opponent = opponent;
	Node m = getMax(root);
	Board max;
	max.board = m.board;
	max.bScore = m.bScore;
	max.wScore = m.wScore;
	printf("\nNodes:%i\n", c);
	c = 0;
	return max;
}


Node getMax(Node bBoard) { //recurive method that Calls on min which then calls on max and so on.
	Node max;
	int ret = INT_MIN;
	if (bBoard.ply > bBoard.plyMax) { // recursion break when the current ply is greater than the allowed ply max.
		max = bBoard;
		return max;
	}
	bBoard.ply++;
	vector<Node> children = getChildren(bBoard, bBoard.actor);


	for (int i = 0; i < children.size(); i++) {
		Node min;
		min = getMin(children[i]);
		int p = min.bScore - min.wScore;
		if (p > ret) {
			ret = p;
			max = children[i];
		}
	}

	return max;
}


Node getMin(Node bBoard) { //identical to getMax but slightly altered to allow for retrival of Min Node;
	Node min;
	int ret = INT_MAX;
	if (bBoard.ply > bBoard.plyMax) {
		min = bBoard;
		return min;
	}
	bBoard.ply++;

	vector<Node> children = getChildren(bBoard, bBoard.opponent);


	for (int i = 0; i < children.size(); i++) {
		Node max;
		max = getMax(children[i]);
		int p = max.bScore - max.wScore;
		if (p < ret) {
			ret = p;
			min = children[i];
		}
	}

	return min;
}

vector<vector<char>> clearBoard() { //returns an empty board state;
	vector<vector<char>> ret;
	for (int i = 0; i < 9; i++) {
		vector<char> vec;
		for (int j = 0; j < 9; j++) {
			vec.push_back('.');
		}
		ret.push_back(vec);
	}
	return ret;
}

void printBoard(Board board) { //Prints the as a 9 by 9 grid with column headers
	printf("1 2 3 4 5 6 7 8 9\n");
	for (int i = 0; i <9 ; i++) {
		for (int j = 0; j < 9; j++) {
			printf("%c ", board.board[i][j]);
		}
		printf("\n");
	}
	printf("White Score:%i\n", board.wScore);
	printf("Black Score:%i\n", board.bScore);
}

void pause() { //pauses teh console so that it doesn't dissapear immediately.
	cout << "Press ENTER to continue..." << flush;
	cin.clear();  // use only if a human is involved
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}