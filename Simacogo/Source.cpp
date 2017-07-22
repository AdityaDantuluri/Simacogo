#include <stdio.h>
#include <iostream>
#include"Node.h"
#include"Functions.h"

using namespace std;

char EMPTY = '.';
char PLAYER = 'O';
char AI = 'X';

int main() {
	Board baseBoard;
	baseBoard.board = clearBoard();
	baseBoard.bScore = 0;
	baseBoard.wScore = 0;
	printBoard(baseBoard);
	printf("How many ply? ");
	int ply = 0;
	cin >> ply;


	Board active = baseBoard;
	while (true){
		int c;

		printf("\nPlayer Move\nWhich Column:");
		cin >> c;
		printf("\n");
		active = playerMove(active, c-1);
		printBoard(active);
		printf("\nAI is Thinking");
		active = getMove(active, ply , AI, PLAYER);
		printf("\nAI Move\n");
		printBoard(active);
	}

	pause();
}