/*
    Actividad 3.2 Implementación de "Dijkstra and Floyd"

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

    Martes 11 de octubre del 2022
*/

#include <iostream>
#include <vector>
#include <limits.h>

#define INF INT_MAX

using namespace std;

//Global variable for size of matrix
int matrixN;

//Time Complexity O(n)
//Space Complexity O(1)
int getMin(vector<int> &dist , vector<bool> &visited){
    int key = 0; 
    int min = INF; 

    for(int i = 0; i < matrixN; i++){
        if(!visited[i] && dist[i] < min){
            min = dist[i]; 
            key = i; 
        }
    }

    return key ; 
}

//Time Complexity O(n)
//Space Complexity O(1)
void showDistances(vector<int> &distance, int node){
    for(int i = 0; i < matrixN; i++){
        if(i != node){
            if(distance[i] == INF){
                cout << "node " << node + 1 << " to node " << i + 1 << " : INF" << endl;
            }
            else{
                cout << "node " << node + 1 << " to node " << i + 1 << " : " << distance[i] << endl;
            }
        }
    }
}

//Time Complexity O(n^2)
//Space Complexity O(n), if we dont count the matrix the function gets as a parameter. If we count it space complexity is O(n^2)
void dijkstra(int node, vector<vector<int> > &matrix){
    vector<int> distance (matrixN, INF);
    vector<bool> visited (matrixN, false);

    distance[node] = 0;

    for(int i = 0; i < matrixN; i++){
        //get the closest node also current node
        int closest = getMin(distance, visited);
        //mark it as visited
        visited[closest] = true;

        //get the distance from the current node to all the nodes
        for(int j = 0; j < matrixN; j++){
            //check that we havent visited the node and the node has a connection and the distance is less than previous distance
            if(!visited[j] && matrix[closest][j] != INF && (distance[closest] + matrix[closest][j]) < distance[j]) {
                distance[j] = distance[closest] + matrix[closest][j]; 
            }
        }
    }
    //show distances
    showDistances(distance, node);
}

//Time Complexity O(n^3)
//Space Complexity O(n^2)
vector<vector<int> > floydWarshall(vector<vector<int> > &matrix){
    //create result matrix as a copy of the input matrix, initially
    vector<vector<int> > result = matrix;

    for(int i = 0; i < matrixN; i++){
        for(int j = 0; j < matrixN; j++){
            for(int k = 0; k < matrixN; k++){
                if(result[i][k] != INF && result[k][j] != INF && result[i][j] > result[i][k] + result[k][j]){
                    result[i][j] = result[i][k] + result[k][j];
                }
            }
        }
    }

    return result;
}

int main(){

    //dimension of the matrix
    cin >> matrixN;

    //create matrix
    vector<vector<int> > matrix(matrixN);
    for(int i = 0; i < matrix.size(); i++){
        matrix[i].resize(matrixN);
    }

    //fill matrix
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            int num = 0;
            cin >> num;
            if(num == -1){
                matrix[i][j] = INF;
            }
            else{
                matrix[i][j] = num;
            }
        }
    }

    // //print matrix
    // for(int i = 0; i < matrix.size(); i++){
    //     for(int j = 0; j < matrix[i].size(); j++){
    //         cout << " " << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    //DIJKSTRA IMPLEMENTATION
    cout << endl << endl << "Dijkstra: " << endl << endl;
    for(int i = 0; i < matrixN; i++){
        dijkstra(i, matrix);
    }

    //FLOYD-WARSHALL IMPLEMENTATION
    cout << endl << endl << "Floyd-warshall: " << endl << endl;
    vector<vector<int> > floyd = floydWarshall(matrix);
    for(int i = 0; i < matrixN; i++){
        for(int j = 0; j < matrixN; j++){
            if(floyd[i][j] >= INF){
                cout << " INF ";
            }
            else{
                cout << " " << floyd[i][j] << " ";
            }
        }
        cout << endl;
    }

    cout << endl << endl;

    return 0;
}
