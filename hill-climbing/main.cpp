/*
    Actividad 5.7 Implementación Hill-Climbing

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

    Miercoles 23 de octubre del 2022
*/

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

// info from https://www.geeksforgeeks.org/n-queen-problem-local-search-using-hill-climbing-with-random-neighbour/

// board dimensions
int N;

// randomly provide a starting point to the algoritm
//Time Complexity O(n)
//Space Complexity O(n^2) if we count the parameters the function takes
void configureRandomly(vector<vector<int> > &board, vector<int> &state){
	// Seed for the random function
	srand(time(0));

	for (int i = 0; i < N; i++) {
		// Getting a random row index
		state[i] = rand() % N;

		// Placing a queen on the obtained place in chessboard.
		board[state[i]][i] = 1;
	}
}

//Time Complexity O(n^2)
//Space Complexity O(1)
void printBoard(vector<vector<int> > &board){
	for (int i = 0; i < N; i++) {
		cout << " ";
		for (int j = 0; j < N; j++) {
			cout << board[i][j] << " ";
		}
		cout << "\n";
	}
}

//Time Complexity O(n)
//Space Complexity O(1)
void printState(vector<int> &state){
	for (int i = 0; i < N; i++) {
		cout << " " << state[i] << " ";
	}
	cout << endl;
}

//returns true if state1 and state2 are equal
bool compareStates(vector<int> &state1, vector<int> &state2){
	for (int i = 0; i < N; i++) {
		if (state1[i] != state2[i]) {
			return false;
		}
	}
	return true;
}

//fill array with a value
//Time Complexity O(n^2)
//Space complexity O(n^2) if we count the parameters the function takes
void fill(vector<vector<int> > &board, int value){
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = value;
		}
	}
}

// calculate the objective value of the state(queens attacking each other)
//Time Complexity O(n^2)
//Space Complexity O(n^2)
int calculateObjective(vector<vector<int> > &board, vector<int> state){
	// Number of queens attacking each other,
	// initially zero.
	int attacking = 0;

	int row, col;

	for (int i = 0; i < N; i++) {
        // At each column 'i', the queen is placed at row 'state[i]'

        // To the left of same row (row remains constant and col decreases)
		row = state[i], col = i - 1;
		while (col >= 0 && board[row][col] != 1) {
			col--;
		}
		if (col >= 0 && board[row][col] == 1) {
			attacking++;
		}

        // To the right of same row (row remains constant and col increases)
		row = state[i], col = i + 1;
		while (col < N && board[row][col] != 1) {
			col++;
		}
		if (col < N && board[row][col] == 1) {
			attacking++;
		}

        // Diagonally to the left up (row and col simultaneously decrease)
		row = state[i] - 1, col = i - 1;
		while (col >= 0 && row >= 0 && board[row][col] != 1) {
			col--;
			row--;
		}
		if (col >= 0 && row >= 0 && board[row][col] == 1) {
			attacking++;
		}

		// Diagonally to the right down (row and col simultaneously increase)
		row = state[i] + 1, col = i + 1;
		while (col < N && row < N && board[row][col] != 1) {
			col++;
			row++;
		}
		if (col < N && row < N && board[row][col] == 1) {
			attacking++;
		}

		// Diagonally to the left down (col decreases and row increases)
		row = state[i] + 1, col = i - 1;
		while (col >= 0 && row < N && board[row][col] != 1) {
			col--;
			row++;
		}
		if (col >= 0 && row < N && board[row][col] == 1) {
			attacking++;
		}

		// Diagonally to the right up (col increases and row decreases)
		row = state[i] - 1, col = i + 1;
		while (col < N && row >= 0 && board[row][col] != 1) {
			col++;
			row--;
		}
		if (col < N && row >= 0 && board[row][col] == 1) {
			attacking++;
		}
	}

	// Return pairs.
	return (int)(attacking / 2);
}

//generate a board with a given state array
//Time Complexity O(n)
//Space Complexity O(n^2) if we count the parameters taken by the function
void generateBoard(vector<vector<int> > &board, vector<int> &state){
	fill(board, 0);
	for (int i = 0; i < N; i++) {
		board[state[i]][i] = 1;
	}
}

// copy the state to another
//Time Complexity O(n)
//Space Complexity O(n)
void copyState(vector<int> &state1, vector<int> &state2){
	for (int i = 0; i < N; i++) {
		state1[i] = state2[i];
	}
}

// This function gets the neighbour of the current state having the least objective value amongst all neighbours as well as the current state.
//Time Complexity O(n^2)
//Space Complexity O(n^2)
void getNeighbour(vector<vector<int> > &board, vector<int> &state){
	// optimal board and state with the current board and the state as the starting point.
	vector<vector<int> > opBoard(N, vector<int>(N));
    vector<int> opState(N);

	copyState(opState, state);
	generateBoard(opBoard, opState);

	// optimal objective value
	int opObjective = calculateObjective(opBoard, opState);

	// temporary board and state for the purpose of computation.
    vector<vector<int> > NeighbourBoard(N, vector<int>(N));
    vector<int> NeighbourState(N);

	copyState(NeighbourState, state);
	generateBoard(NeighbourBoard, NeighbourState);

	// Iterating through all possible neighbours of the board.
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// skip the current state
			if (j != state[i]) {
				// temporary neighbour = current neighbour
				NeighbourState[i] = j;
				NeighbourBoard[NeighbourState[i]][i] = 1;
				NeighbourBoard[state[i]][i] = 0;

				// Calculating the objective value of the neighbour.
				int temp = calculateObjective(NeighbourBoard, NeighbourState);

				// Comparing temporary and optimal neighbour objectives 
				if (temp <= opObjective) {
                    opObjective = temp;
					copyState(opState, NeighbourState);
					generateBoard(opBoard, opState);
				}

				// Going back to the original configuration for the next iteration.

				NeighbourBoard[NeighbourState[i]][i] = 0;
				NeighbourState[i] = state[i];
				NeighbourBoard[state[i]][i] = 1;
			}
		}
	}

	copyState(state, opState);
	fill(board, 0);
	generateBoard(board, state);
}

//Time Complexity O(n^n)
//Space Complexity O(n^2)
void hillClimbing(vector<vector<int> > &board, vector<int> &state){
	vector<vector<int> > neighbourBoard(N, vector<int>(N));
    vector<int> neighbourState(N);

	copyState(neighbourState, state);
	generateBoard(neighbourBoard, neighbourState);

	do {
		copyState(state, neighbourState);
		generateBoard(board, state);

		// Getting the optimal neighbour
		getNeighbour(neighbourBoard, neighbourState);

		if (compareStates(state, neighbourState)) {
			// If neighbour and current are equal then no optimal neighbour exists 
			printBoard(board);
			break;
		}
		else if (calculateObjective(board, state) == calculateObjective(neighbourBoard, neighbourState)) {

			// reaching a local optimum, jump to skip it
			// Random neighbour
			neighbourState[rand() % N] = rand() % N;
			generateBoard(neighbourBoard, neighbourState);
		}
	} while (true);
}

// Driver code
int main(){

    cin >> N;

    cout << endl << endl << "N = " << N << endl << endl;

    vector<int> state(N);
    vector<vector<int> > board(N, vector<int>(N));

	// Getting a starting point by
	// randomly configuring the board
	configureRandomly(board, state);

	// Do hill climbing on the
	// board obtained
	hillClimbing(board, state);

    cout << endl << endl;
	return 0;
}
