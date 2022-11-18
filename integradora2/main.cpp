/*
    E2. Actividad Integradora 2

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

    Viernes 18 de noviembre del 2022
*/

#include <iostream>
#include <vector>

using namespace std;

int main(){
    // number of colonies
    int n;
    cin >> n;
    //nxn matrix that represents distances between colonies in km
    vector<vector<int> > m_distance(n, vector<int>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> m_distance[i][j];
            // cout << m_distance[i][j] << " ";
        }
        // cout << endl;
    }
    //nxn matrix that represents the max data flow between colonies
    vector<vector<int> > m_data_flow(n, vector<int>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> m_data_flow[i][j];
            // cout << m_data_flow[i][j] << " ";
        }
        // cout << endl;
    }
    //coordenates of the energy/internet central
    vector<pair<int, int> > central_coordinates(n);
    for(int i = 0; i < n; i++){
        pair<int, int> p;
        cin >> p.first;
        cin >> p.second;
        central_coordinates.push_back(p);
        // cout << p.first << ", " << p.second << endl;
    }

    
    return 0;
}