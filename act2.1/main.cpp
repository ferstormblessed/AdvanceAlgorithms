/*
    Actividad 2.1 Implementación de "Hash String"

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez Flores A01635304

    Sabado 2 de septiembre del 2022

    Output = A string of length n / 4 in hexadecimal format
    n is an integer multiple of 4 and 16 <= n <= 64
    n = number of columns where the characters of the file are stored, '\n' char included
    if n not multiple of 4 add a new column with the value of n


*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

string readFile(string fileName){
    string t = "";
    //read file
    ifstream file(fileName, ios::in);
   
    //file to text
    while(file){
        char c;
        c = file.get();
        t += c;
    }

    file.close();
    t.pop_back();
    return t;
}

void fillChar(int n, vector< vector <int> > *arr, string text){
    int textLen = text.length();
    int counter = 0; //number of characters added
    int iter = 0; // number of rows

    while(counter < textLen){
        vector<int> v;
        v.clear();
        for(int i = n * iter; i < n + n * iter; i++){
            int c;
            if(counter > textLen) {
                c = n;
            }
            else {
                c = text[i];
            }
            v.push_back(c);
            counter++;
        }
        iter++;
        arr->push_back(v);
    }
}

void hashFunc(vector< vector <int> > &arr, int output[], int n){
    for(int i = 0; i < n; i++){
        int sum = 0;
        for(int j = 0; j < arr.size(); j++){
            sum += arr[j][i];
        }
        output[i] = sum % 256;
    }
}

int main(int argc, char *argv[]){
    int n = 0;
    string fileName = "";

    n = stoi(argv[2]);
    fileName =  argv[1];

    string text = readFile(fileName);

    vector< vector<int> > arr;
    // fill the array with the characters
    fillChar(n, &arr, text);

    // print matrix whit chars
    // for(int i = 0; i < arr.size(); i++){
    //     for(int j = 0; j < n; j++){
    //         cout << arr[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    int output[n];
    hashFunc(arr, output, n);

    string result = "";

    cout << "output: ";
    stringstream ss;
    for(int i = 0; i < n; i++){
        ss << hex << output[i];
    }
    result = ss.str();

    for(int i = 0; i < result.length(); i++){
        if(isalpha(result[i])){
            result[i] -= 32;
        }
    }
    //62c0beace4ab3e756a9428a366631116
    //62C0BEACE4AB3E756A9428A366631116
    cout << result << endl;
    return 0;
}