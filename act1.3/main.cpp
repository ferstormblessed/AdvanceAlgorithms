/*
    Actividad 1.3 Implementación de la técnica de programación "backtracking" y "ramificación y poda"

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez Flores A01635304

    Miercoles 24 de agosto del 2022
*/

#include <iostream>
#include <queue>
#include <utility>

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
    printMatrix(maze, m, n);
    printMatrix(solution, m, n);
}


void branchBoundMaze(int **maze, int **solutionBnB, int x, int y, int m, int n){
    // int maze2[m][n];

    // for(int i = 0; i < m; i++){
    //     for(int j = 0; j < n; j++){
    //         maze2[i][j] = maze[i][j];
    //     }
    // }

    queue< pair<int, int> > q;
    pair<int, int> start;
    start.first = x;
    start.second = y;
    q.push(start);

    while(x <= m - 1 && y <= n - 1 && maze[x][y] == 1){
        maze[x][y] = 0;
        solutionBnB[x][y] = 1;

        pair<int, int> currPos = q.front();
        q.pop();
        int currX = currPos.first;
        int currY = currPos.second;

        pair<int, int> next;
        
        cout << "Current position: (" << currX << ", " << currY << ")" << endl;

        if(isSafeToMove(maze, currX, currY + 1, m, n) && maze[currX][currY + 1] == 1){
            next.first = currX;
            next.second = currY + 1;
            q.push(next);
        }
        if(isSafeToMove(maze, currX + 1, currY, m, n) && maze[currX + 1][currY] == 1){
            next.first = currX + 1;
            next.second = currY;
            q.push(next);
        }
        if(isSafeToMove(maze, currX, currY - 1, m, n) && maze[currX][currY - 1] == 1){
            next.first = currX;
            next.second = currY - 1;
            q.push(next);
        }
        if(isSafeToMove(maze, currX - 1, currY, m, n) && maze[currX - 1][currY] == 1){
            next.first = currX - 1; 
            next.second = currY;
            q.push(next);
        }

        pair<int, int> nextNode = q.front();
        x = nextNode.first;
        y = nextNode.second;

        
    }


    printMatrix(solutionBnB, m, n);
}


int main(){
    int m, n;

    cin >> m;
    cin >> n;
    m = 4;
    n = 4;

    int **maze = new int*[m];
    int **solution = new int*[m];
    int **solutionBnB = new int*[m];
    // queue< pair<int, int> > *queueBnB;

    // pair<int, int> start;
    // start.first = 0;
    // start.second = 0;
    // queueBnB -> push(start);

    for(int i = 0; i < m; i++){
        maze[i] = new int[n];
        solution[i] = new int[n];
        solutionBnB[i] = new int[n];
        for(int j = 0; j < n; j++){
            cin >> maze[i][j];
            solution[i][j] = 0;
            solutionBnB[i][j] = 0;
        }
    }

    maze[0][0] = 1;
    maze[0][1] = 0;
    maze[0][2] = 0;
    maze[0][3] = 0;
    maze[1][0] = 1;
    maze[1][1] = 1;
    maze[1][2] = 0;
    maze[1][3] = 1;
    maze[2][0] = 0;
    maze[2][1] = 1;
    maze[2][2] = 0;
    maze[2][3] = 0;
    maze[3][0] = 1;
    maze[3][1] = 1;
    maze[3][2] = 1;
    maze[3][3] = 1;

    //backtrackingMaze(maze, solution, 0, 0, m, n);
    branchBoundMaze(maze, solutionBnB, 0, 0, m, n);

    return 0;
}