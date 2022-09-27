/*
    Actividad 2.2 Implementación de "Sufix Array"

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez Flores A01635304

*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//Time complexity O(n^2), because of the function substr has O(n) time complexity
//Space complexity O(n)
vector<string> substringArray(string s){
    vector<string> arr;
    string substring = "";
    
    //iterate through the string
    for(int i = 0; i < s.length(); i++){
        //get substring from the i position to the end
        substring = s.substr(i);
        arr.push_back(substring);
    }

    return arr;
}

//Time complexity O(n log n)
vector<string> suffixArray(vector<string> v){
    //function from algorithm library
    sort(v.begin(), v.end());
    
    return v;

}

//Time complexity O(n)
int findPattern(string subs, vector<string> &v){
    for(int i = 0; i < v.size(); i++){
        if(subs == v[i]){
            return i;
        }
    }
    //the substring is not part of the original string
    return -1;
}

//Time Complexity O(n)
void toLowerCase(string &s){
    for(int i = 0; i < s.length(); i++){
        if(!islower(s[i])){
            s[i] += 32;
        }
    }
}

void printVector(vector<string> v){
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << endl;
    }
}

int main(){

    string s = "";
    cin >> s;
    
    toLowerCase(s);

    cout << endl << "Original string: " << s << endl << endl;

    cout << "Substring array" << endl << endl;

    vector<string> subArr = substringArray(s);
    printVector(subArr);

    cout << endl << "Suffix array" << endl << endl;

    vector<string> suffArr = suffixArray(subArr);
    printVector(suffArr);

    cout << endl;

    int numSubstrings = 0;
    cin >> numSubstrings;
    vector<string> substrings(numSubstrings);
    for(int i = 0; i < numSubstrings; i++){
        cin >> substrings[i];
    }

    cout << "Substring --> Position" << endl << endl;
    for(int i = 0; i < substrings.size(); i++){
        cout << substrings[i] << " --> " << findPattern(substrings[i], suffArr) << endl;
    }
    cout << endl;

    return 0;
}