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
        cout << endl;
    }
    //nxn matrix that represents the max data flow between colonies
    vector<vector<int> > m_data_flow(N, vector<int>(N));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> m_data_flow[i][j];
            // cout << m_data_flow[i][j] << " ";
        }
        // cout << endl;
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
    cout << endl << endl;

    return 0;
}