/*
    Actividad 3.3 Implementación de "Knapsack problem"

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

    Jueves 20 de octubre del 2022
*/

#include <iostream>
#include <vector>

using namespace std;

//Time Complexity O(1)
//Space Complexity O(1)
int max(int a, int b) { 
    return (a > b) ? a : b; 
}

//Time Complexity O(n * c), where n = number of elemets and c = total knapsack capacity
//Space Complexity O(n * c), where n = number of elemets and c = total knapsack capacity
int knapsack(vector<int> &w, vector<int> &v, int &capacity, int &n){
    vector<vector<int> > dp(n + 1, vector<int>(capacity + 1, 0));

    for(int i = 1; i < n + 1; i++){
        for(int j = 1; j < capacity + 1; j++){
            if(w[i - 1] <= j){
                dp[i][j] = max(v[i - 1] + dp[i - 1][j - w[i - 1]], dp[i - 1][j]);
            }
            else{
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[n][capacity];}

int main(){
    //number of elements
    int n = 0;
    cin >> n;
    // cout << "elements: " << n << endl;

    //weight of elements
    vector<int> weights(n, 0);
    for(int i = 0; i < n; i++){
        cin >> weights[i];
    }

    //value of elements
    vector<int> values(n, 0);
    for(int i = 0; i < n; i++){
        cin >> values[i];
    }

    //knapsack capacity
    int capacity = 0;
    cin >> capacity;
    // cout << "capacity: " << capacity << endl;
    
    int res = knapsack(weights, values, capacity, n);
    cout << endl << endl << "Max profit: " << res << endl << endl;

    return 0;
}