/*
    E2. Actividad Integradora 2

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

    Viernes 18 de noviembre del 2022
*/

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <map>
// #include <set>
#include <bits/stdc++.h>
#include <queue>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#define INF INT_MAX

using namespace std;

int N; 

//Time Complexity O(n)
//Space Complexity O(1)
int getMin(vector<int> &dist , vector<bool> &visited){
    int key = 0; 
    int min = INF; 

    for(int i = 0; i < N; i++){
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
    //assign a letter to each city
    vector<char> letter_cities(N);
    for(int i = 0; i < N; i++){
        letter_cities[i] = i + 65;
    }
    for(int i = 0; i < N; i++){
        if(i != node){
            if(distance[i] == INF){
                cout << "(" << letter_cities[node] << ", " << letter_cities[i] << ") : INF" << endl;
            }
            else{
                cout << "(" << letter_cities[node] << ", " << letter_cities[i] << ") : " << distance[i] << " km" << endl;
            }
        }
    }
}

//Time Complexity O(n^2)
//Space Complexity O(n), if we dont count the matrix the function gets as a parameter. If we count it space complexity is O(n^2)
void dijkstra(int node, vector<vector<int> > &matrix){
    vector<int> distance (N, INF);
    vector<bool> visited (N, false);

    distance[node] = 0;

    for(int i = 0; i < N; i++){
        //get the closest node also current node
        int closest = getMin(distance, visited);
        //mark it as visited
        visited[closest] = true;

        //get the distance from the current node to all the nodes
        for(int j = 0; j < N; j++){
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

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                if(result[i][k] != INF && result[k][j] != INF && result[i][j] > result[i][k] + result[k][j]){
                    result[i][j] = result[i][k] + result[k][j];
                }
            }
        }
    }

    return result;
}

// algorithm implementation from https://www.geeksforgeeks.org/traveling-salesman-problem-tsp-implementation/

//travelling salesman problem
//Time Complexity O(n^3)
//Space Complexity O(n^2)
vector<char> tsp(vector<vector<int> > &graph, int s) {
    // store path
    vector<char> path(N);
    //assign a letter to each city
    vector<char> letter_cities(N);
    for(int i = 0; i < N; i++){
        letter_cities[i] = i + 65;
    }
    // store all vertex apart from source vertex
    vector<int> vertex;
    for (int i = 0; i < N; i++){
        if (i != s){
            vertex.push_back(i);
        }
    }   
    // store minimum weight Hamiltonian Cycle.
    int min_path = INT_MAX;
    // the person starts in the first city
    path.push_back(letter_cities[0]);
    do {
        // store current Path weight(cost)
        int current_pathweight = 0;
        // compute current path weight
        int k = s;
        for (int i = 0; i < vertex.size(); i++) {
            current_pathweight += graph[k][vertex[i]];
            k = vertex[i];
        }
        current_pathweight += graph[k][s];
        path.push_back(letter_cities[k]);
        // update minimum
        min_path = min(min_path, current_pathweight);
 
    } 
    while (next_permutation(vertex.begin(), vertex.end()));
    // the person finishes in the city they started
    path.push_back(letter_cities[0]);
 
    return path;
    // return min_path;
}

//Time Complexity O(n^3)
//Space Complexity O(n^2)
int max_flow(vector<vector<int> > &graph, int s) {
    // store all vertex apart from source vertex
    vector<int> vertex;
    for (int i = 0; i < N; i++){
        // if (i != s){
        //     vertex.push_back(i);
        // }
        vertex.push_back(i);
    }   
    // store minimum weight Hamiltonian Cycle.
    int min_path = 0;
    do {
        // store current Path weight(cost)
        int current_pathweight = 0;
        // compute current path weight
        int k = s;
        for (int i = 0; i < vertex.size(); i++) {
            current_pathweight += graph[k][vertex[i]];
            k = vertex[i];
        }
        current_pathweight += graph[k][s];
        // update minimum
        min_path = max(min_path, current_pathweight);
 
    } 
    while (next_permutation(vertex.begin(), vertex.end()));
 
    return min_path;
}


int main(){

    // LEER INPUT

    // number of colonies
    cin >> N;
    // cout << N << endl;
    //nxn matrix that represents distances between colonies in km
    vector<vector<int> > m_distance(N, vector<int>(N));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> m_distance[i][j];
            if(m_distance[i][j] == 0){
                m_distance[i][j] = INF;  
                // cout << "INF" << " ";
            }
            // else{
            //     cout << m_distance[i][j] << " ";
            // }
            // cout << m_distance[i][j] << " ";

        }
        // cout << endl;
    }
    //nxn matrix that represents the max data flow between colonies
    vector<vector<int> > m_data_flow(N, vector<int>(N));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> m_data_flow[i][j];
            cout << m_data_flow[i][j] << " ";
        }
        cout << endl;
    }
    //coordenates of the energy/internet central
    vector<pair<int, int> > central_coordinates(N);
    for(int i = 0; i < N; i++){
        pair<int, int> p;
        cin >> p.first;
        cin >> p.second;
        central_coordinates.push_back(p);
        // cout << p.first << ", " << p.second << endl;
    }

    // PARTE 1
    cout << endl << endl << "1. Forma de cablear las colonias con fibra" << endl << endl;
    for(int i = 0; i < N; i++){
        dijkstra(i, m_distance);
    }

    // PARTE 2

    cout << endl << endl;
    vector<vector<int> > floyd = floydWarshall(m_distance);
    // for(int i = 0; i < N; i++){
    //     for(int j = 0; j < N; j++){
    //         if(floyd[i][j] >= INF){
    //             cout << " INF ";
    //         }
    //         else{
    //             cout << " " << floyd[i][j] << " ";
    //         }
    //     }
    //     cout << endl;
    // }

    // cout << endl << endl;

    vector<char> ruta = tsp(floyd, 0);
    cout << "2. Ruta: ";
    for(int i = 0; i < ruta.size(); i++){
        cout << ruta[i] << " ";
    }

    // PARTE 3
    cout << endl << endl;
    cout << "3. Flujo maximo entre el nodo inicial y nodo final:" << max_flow(m_data_flow, 0) << endl;



    cout << endl << endl;

    return 0;
}