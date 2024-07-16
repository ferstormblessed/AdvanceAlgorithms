/*
    Actividad 5.1 Implementación backtracking: El problema The Knight’s tour.

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

    Domingo 6 de noviembre del 2022
*/

#include <iostream>
#include <vector>
#include <iomanip>

int N;

using namespace std;

//declare at the top for rescurrsion
int solveKTUtil(int x, int y, int movei, vector<vector<int> > &sol, int xMove[], int yMove[]);
 
/* check if i,j are valid indexes for N*N chessboard */
//Time and Space Complexity O(1)
int isSafe(int x, int y, vector<vector<int> > &sol) {
    return (x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1);
}
 
//print matrix
//Time Complexity O(n)
//Space Complexity O(1)
void printSolution(vector<vector<int> > &sol) {
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++){
            cout << " " << setw(2) << sol[x][y] << " ";
        }
        cout << endl;
    }
}
 
/* This function solves the Knight Tour problem using Backtracking. 
It returns false if no complete tour is possible, otherwise return true and prints the tour. */
//Time Complexity O(8 ^(n^2))
//Space Complexity O(n^2)
int solveKT() {

    /* Initialization of solution matrix */
    vector<vector<int> > sol(N, vector<int>(N, -1));
 
    /* xMove[] and yMove[] define next move of Knight.
    xMove[] is for next value of x coordinate
    yMove[] is for next value of y coordinate */
    int xMove[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int yMove[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
 
    // Since the Knight is initially at the first block
    sol[0][0] = 0;
 
    /* Start from 0,0 and explore all tours using solveKTUtil() */
    if (solveKTUtil(0, 0, 1, sol, xMove, yMove) == 0) {
        cout << "Solution does not exist";
        return 0;
    }
    else{
        printSolution(sol);
    }
    return 1;
}
 
/* A recursive utility function to solve Knight Tour problem */
//Time Complexity O(8^n)
//Space Complexity(n)
int solveKTUtil(int x, int y, int movei, vector<vector<int> > &sol, int xMove[8], int yMove[8]) {
    int k, next_x, next_y;
    
    if (movei == N * N){
        return 1;
    }
 
    /* Try all next moves from the current coordinate x, y */
    for (k = 0; k < 8; k++) {
        next_x = x + xMove[k];
        next_y = y + yMove[k];
        if (isSafe(next_x, next_y, sol)) {
            sol[next_x][next_y] = movei;
            if (solveKTUtil(next_x, next_y, movei + 1, sol, xMove, yMove) == 1){
                return 1;
            }
            else{
                // backtracking
                sol[next_x][next_y] = -1;
            }
        }
    }
    return 0;
}

int main(){
    //get dimensions of the chessboard
    cin >> N;

    cout << endl << endl;

    cout << "Chessboard: " << N << "x" << N << endl << endl;
    
    solveKT();
    
    cout << endl << endl;
    

    return 0;
}