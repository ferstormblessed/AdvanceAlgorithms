/*
    Actividad 5.4 Implementación encontrarse en el medio (meet in the middle)

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

    Jueves 17 de noviembre del 2022
*/

#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

// info from https://www.geeksforgeeks.org/meet-in-the-middle/

typedef long long int ll;
ll X[2000005],Y[2000005];

// Find all possible sum of elements of a[] and store in x[]
//Time Complexity O(n^2)
//Space Complexity O(n)
void calcsubarray(ll a[], ll x[], int n, int c){
	for (int i = 0; i < (1 << n); i++){
		ll s = 0;
		for (int j = 0; j < n; j++){
            if (i & (1 << j))
				s += a[j + c];
        }
		x[i] = s;
	}
}

// Returns the maximum possible sum less or equal to S
//Time Complexity O(2^(n/2) * log(2^(n/2)))
//Space Complexity O(2^(n/2))
ll solveSubsetSum(ll a[], int n, ll S){
	// Compute all subset sums of first and second halves
	calcsubarray(a, X, n/2, 0);
	calcsubarray(a, Y, n-n/2, n/2);

	int size_X = 1 << (n/2);
	int size_Y = 1 << (n-n/2);

	// Sort Y (we need to do doing binary search to lower the complexity)
	sort(Y, Y + size_Y);

	//keep track of max sum
	ll max = 0;

	// Traverse all elements of X and do Binary Search for a pair in Y with maximum sum less than S.
	for (int i = 0; i < size_X; i++){
		if (X[i] <= S){
			// return the first address with value greater than or equal to S-X[i].
			int p = lower_bound(Y, Y + size_Y, S - X[i]) - Y;

			// If S-X[i] was not in array Y then decrease p by 1
			if (p == size_Y || Y[p] != (S - X[i])){
                p--;
            }

			if ((Y[p]+X[i]) > max){
                max = Y[p] + X[i];
            }
		}
	}
	return max;
}

int main(){
    //get n = number of elements in array
    int n;
    cin >> n;
    //initialize and fill array
    ll a[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    //get S = target sum
    ll S;
    cin >> S;
    //output
    cout << endl << endl;
    cout << "Output: " << solveSubsetSum(a, n, S) << endl;
    cout << endl << endl;
	return 0;
}
