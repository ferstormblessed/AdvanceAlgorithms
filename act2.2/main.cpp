/*
    Actividad 2.2 Implementación de "Sufix Array"

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez Flores A01635304

    Sabado 11 de septiembre del 2022

*/

#include <iostream>
#include <string>
#include <vector>

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

//Time complexity O(n^2)
//Space complexity O(n)
vector<string> suffixArray(vector<string> v){
    vector<string> output;

    int leftPtr = 0;
    int rightPtr = v.size() - 1;

    //we pass through the vector only once
    while(leftPtr < rightPtr){
        int pos = 0;
        string sub1 = v[leftPtr];
        string sub2 = v[rightPtr];
        bool compare = true;

        //check which string goes first alphabetically
        while(!sub1.empty() && !sub2.empty() && compare){
            //checking by character
            if(sub1[pos] < sub2[pos]){
                output.push_back(sub1);
                leftPtr++;
                compare = false;
            }
            else if(sub1[pos] > sub2[pos]){
                output.push_back(sub2);
                rightPtr--;
                compare = false;
            }
            //both strings start with the same letter
            pos++;
        }
    }

    //last string in the vector
    if(leftPtr == rightPtr){
        output.push_back(v[leftPtr]);
    }

    return output;
}

void printVector(vector<string> v){
    for(int i = 0; i < v.size(); i++){
        cout << i << " | " << v[i] << endl;
    }
}

int main(){

    string s = "";
    cin >> s;

    // s = "apple";

    // cout << "string: " << s << endl;

    cout << "Substring array" << endl;
    vector<string> subArr = substringArray(s);
    printVector(subArr);

    cout << endl << "Suffix array" << endl;

    vector<string> suffArr = suffixArray(subArr);
    printVector(suffArr);

    cout << endl;

    // cout << "comparison e and apple: "<< subArr[3].compare(subArr[0]) << endl;

    return 0;
}