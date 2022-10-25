/*
    Actividad 3.3 Implementación de "Knapsack problem"

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

    Jueves 20 de octubre del 2022
*/

#include <iostream>
#include <vector>

using namespace std;

int NODE = 0;

//Greedy implementation of graph coloring

//Time Complexity O(n^2)
//Space Complexity O(n)
void graphColoring(vector<vector<int> > &graph) {
    //array for the color of each node
    int color[NODE];
    //Assign first color for the first node
    color[0] = 0;
    //Used to check whether color is used or not
    bool colorUsed[NODE];

    for(int i = 1; i < NODE; i++){
        //initialize all other vertices are unassigned
        color[i] = -1;
    }

    for(int i = 0; i < NODE; i++){
        //initially any colors are not chosen
        colorUsed[i] = false;
    }

    for(int u = 1; u < NODE; u++){   
        for(int v = 0; v < NODE; v++){
            if(graph[u][v]){
                //when one color is assigned, make it unavailable
                if(color[v] != -1){  
                    colorUsed[color[v]] = true;
                }
            }
        }

        int col;
        for(col = 0; col < NODE; col++){
            if(!colorUsed[col]){    //find a color which is not assigned
                break;
            }
        }
        //assign found color in the list
        color[u] = col;
        
        //for next iteration make color availability to false
        for(int v = 0; v < NODE; v++) {   
            if(graph[u][v]) {
                if(color[v] != -1){
                    colorUsed[color[v]] = false;
                }
            }
        }  
    }

    for(int u = 0; u < NODE; u++){
        cout << "Color: " << u << ", Assigned with Color: " <<color[u] <<endl;
    }
}

int main() {
    //get num of nodes
    cin >> NODE;

    //create and fill matrix
    vector<vector<int> > matrix(NODE, vector<int>(NODE, 0));
    for(int i = 0; i < NODE; i++){
        for(int j = 0; j < NODE; j++){
            cin >> matrix[i][j];
        }
    }
    
    cout << endl << endl;
    graphColoring(matrix);
    cout << endl << endl;
    
    return 0;
}