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

//read file and returns a string with all the characters of the file
//Time and Space complexity O(n)
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

//Fill a vector of vectors with the ASCII value of the characters of the file 
//Time complexity O(n) 
//Space complexity O(n * m), where m = number of rows and n = number of colums 
void fillChar(int n, vector< vector <int> > *arr, string text){
    int textLen = text.length();
    int counter = 0; //number of characters added
    int iter = 0; // number of rows

    while(counter < textLen){
        vector<int> v;
        v.clear();
        for(int i = n * iter; i < n + n * iter; i++){
            int c;
            //the characters of the file are not multiple of 4
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

//Time complexity O(n * m), where m = lenght of vector and n = length of each of the individual vectors
//Space complexity O(n)
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

    int output[n];
    hashFunc(arr, output, n);

    string result = "";

    cout << endl << "output: ";
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

    cout << endl << result << endl << endl;
    return 0;
}