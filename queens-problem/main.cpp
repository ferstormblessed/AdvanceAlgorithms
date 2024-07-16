/*
    Actividad 5.3 Implementación backtracking con poda pesada: Queen's problem

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

    Domingo 22 de octubre del 2022
*/

//info from https://www.geeksforgeeks.org/n-queen-problem-backtracking-3/

#include <iostream>
#include <vector>

using namespace std;

int N;

//Print chessboard
//Time Complexity O(n^2)
//Space Complexity O(1)
void printSolution(vector<vector<int> > &board){
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << " " << board[i][j] << " ";
		printf("\n");
	}
}

//Check if a queen can be placed
//Time Complexity O(1)
//Space Complexity O(1)
bool isSafe(vector<vector<int> > &board, int row, int col){
	int i, j;

	/* Check this row on left side */
	for (i = 0; i < col; i++){
        if (board[row][i]){
            return false;
        }
    }

	/* Check upper diagonal on left side */
	for (i = row, j = col; i >= 0 && j >= 0; i--, j--){
        if (board[i][j]){
            return false;
        }
    }

	/* Check lower diagonal on left side */
	for (i = row, j = col; j >= 0 && i < N; i++, j--){
        if (board[i][j]){
            return false;
        }
    }

	return true;
}

//Time Complexity O(n!)
//Space Complexity O(n^2)
bool solveNQUtil(vector<vector<int> > &board, int col)
{
	//All queens are in place
	if (col >= N){
        return true;
    }

	//try all rows to place the queen
	for (int i = 0; i < N; i++) {
		if (isSafe(board, i, col)) {
			board[i][col] = 1;
            //recursive call
			if (solveNQUtil(board, col + 1))
				return true;
            
			//backtracking
			board[i][col] = 0;
		}
	}

	return false;
}

//Time Complexity O(n!)
//Space Complexity O(n^2)
bool solveNQ(vector<vector<int> > &board){
    //solutions does not exit
	if (solveNQUtil(board, 0) == false) {
		cout << "Solution does not exist";
		return false;
	}

	printSolution(board);
	return true;
}

// driver program to test above function
int main(){
    cout << endl << endl;

    cin >> N;
    cout << "N = " << N << endl << endl;

    vector<vector<int> > board(N, vector<int>(N, 0));

	solveNQ(board);

    cout << endl << endl;
	return 0;
}

// This code is contributed by Aditya Kumar (adityakumar129)
