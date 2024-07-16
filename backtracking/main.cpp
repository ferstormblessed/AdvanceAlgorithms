/*
    Actividad 1.3 Implementación de la técnica de programación "backtracking" y "ramificación y poda"

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez Flores A01635304

    Miercoles 24 de agosto del 2022
*/

#include <iostream>
#include <queue>
#include <utility>
#include <stdlib.h>

using namespace std;

// print matrices
void printMatrix(int **matrix, int m, int n){
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){

            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

//Space and time complexity O(1)
bool isSafeToMove(int **maze, int currentX, int currentY, int m, int n){
    // Verifies that the position passed is in the maze and is a valid position (1)
    if(currentX >= 0 && currentY >= 0 && currentX <= m - 1 && currentY <= n - 1 && maze[currentX][currentY] == 1) {
        return true;
    }
    return false;
}

//Time complexity O(2^(n^2))
//Space complexity O(n^2)
bool solveMaze(int **maze, int **solution, int currentX, int currentY, int m, int n){
    //The maze has been solve
    if(currentX == m - 1 && currentY == n - 1 && maze[currentX][currentY] == 1){
        solution[currentX][currentY] = 1;
        return true;
    }
    
    if(isSafeToMove(maze, currentX, currentY, m, n)){
        //That position is already part of the path
        if(solution[currentX][currentY] == 1){
            return false;
        }
        //valid position and the correct path
        solution[currentX][currentY] = 1;

        //Traverse right in the maze through recurssion
        if(solveMaze(maze, solution, currentX + 1, currentY, m, n)){
            return true;
        }
        //Travers down in the maze through recurssion
        if(solveMaze(maze, solution, currentX, currentY + 1, m, n)){
            return true;
        }
        //Not possible solution
        return false;
    }
    return false;
}

void backtrackingMaze(int **maze, int **solution, int xPosition, int yPosition, int m, int n){
    if(!solveMaze(maze, solution, xPosition, yPosition, m, n)){
        cout << endl << "Solution not possible" << endl << endl;
    }
    cout << endl << "Original maze" << endl << endl;
    printMatrix(maze, m, n);
    cout << endl << "Backtracking algorithm" << endl << endl;
    printMatrix(solution, m, n);
}

void branchBoundMaze(int **maze, int **solutionBnB, int x, int y, int m, int n){

    queue< pair<int, int> > q;
    pair<int, int> start;
    start.first = x;
    start.second = y;
    q.push(start);

    while(x <= m - 1 && y <= n - 1 && maze[x][y] == 1){
        maze[x][y] = 0;

        pair<int, int> currPos = q.front();
        q.pop();
        int currX = currPos.first;
        int currY = currPos.second;

        pair<int, int> next;
        
        //cout << "Current position: (" << currX << ", " << currY << ")" << endl;

        //go right
        if(isSafeToMove(maze, currX, currY + 1, m, n) && maze[currX][currY + 1] == 1){
            next.first = currX;
            next.second = currY + 1;
            q.push(next);
        }
        //go down
        if(isSafeToMove(maze, currX + 1, currY, m, n) && maze[currX + 1][currY] == 1){
            next.first = currX + 1;
            next.second = currY;
            q.push(next);
        }
        //go left
        if(isSafeToMove(maze, currX, currY - 1, m, n) && maze[currX][currY - 1] == 1){
            next.first = currX;
            next.second = currY - 1;
            q.push(next);
        }
        //go up
        if(isSafeToMove(maze, currX - 1, currY, m, n) && maze[currX - 1][currY] == 1){
            next.first = currX - 1; 
            next.second = currY;
            q.push(next);
        }

        pair<int, int> nextNode = q.front();
        x = nextNode.first;
        y = nextNode.second;
    }
    cout << endl << "Branch and bound algorithm" << endl << endl;
    printMatrix(solutionBnB, m, n);
    cout << endl;
}


int main(){
    int m, n;

    cin >> m;
    cin >> n;

    int **maze = new int*[m];
    int **solution = new int*[m];

    for(int i = 0; i < m; i++){
        maze[i] = new int[n];
        solution[i] = new int[n];
        for(int j = 0; j < n; j++){
            cin >> maze[i][j];
            solution[i][j] = 0;
        }
    }

    backtrackingMaze(maze, solution, 0, 0, m, n);
    branchBoundMaze(maze, solution, 0, 0, m, n);

    return 0;
}