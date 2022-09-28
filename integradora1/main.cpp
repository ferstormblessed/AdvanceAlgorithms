/*

    E1. Actividad Integradora 1

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

    transmission files represent data share between devices
    mcode file represent potential malicious code in the transmissions

*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctype.h>

using namespace std;

//read file and returns a string with all the characters of the file
//Time and Space complexity O(n)
string readFile(string fileName){
    string t = "";
    //read file
    ifstream file(fileName);
   
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

//Time Complexity O(n)
void toLowerCase(string &s){
    for(int i = 0; i < s.length(); i++){
        if(!islower(s[i]) && !isdigit(s[i])){
            s[i] += 32;
        }
    }
}

// PARTE 3 
// LONGEST COMMON SUBSTRING BETWEEN TRANSMISSION 1 AND TRANSMISSION 2

/*
t1 = abcdef
t2 = zabcht
    0   1   2   3   4   5   6
0   0   z   a   b   c   h   t
1   a   0   1   0   0   0   0
2   b   0   0   2   0   0   0
3   c   0   0   0   3   0   0
4   d   0   0   0   0   0   0
5   e   0   0   0   0   0   0
6   f   0   0   0   0   0   0

*/

//Time Complexity O(m * n), where m = length of string 1 and n = length of string 2
//Space Complexity O(m * n), where m = length of string 1 and n = length of string 2
vector<vector<int> > createDP(string &t1, string &t2){
    //create dp
    vector<vector<int> > dp(t1.length() + 1);
    for(int i = 0; i < dp.size(); i++){
        dp[i].resize(t2.size() + 1);
    }
    dp[0][0] = 0;
    //fill column 0 with the characters from t1
    for(int i = 1; i < dp.size(); i++){
        dp[i][0] = t1[i - 1];
    }
    //fill row 0 with the characters from t2
    for(int i = 1; i < dp[0].size(); i++){
        dp[0][i] = t2[i - 1];
    }

    for(int i = 1; i < dp.size(); i++){
        for(int j = 1; j < dp[i].size(); j++){
            dp[i][j] = 0;
        }
    }
    return dp;
}

//Time Complexity O(m * n), where m = length of string 1 and n = length of string 2
//Space Complexity O(m * n), where m = length of string 1 and n = length of string 2
void longestSubstring(string &t1, string &t2){
    //create dp
    vector<vector<int> > dp = createDP(t1, t2);
    //length of the longest common substring
    int lenSubstring = 0;
    //position in the string where the substring ends
    int finishPosSubstring = 0;

    for(int i = 1; i < dp.size(); i++){
        for(int j = 1; j < dp[i].size(); j++){
            if(dp[i][0] == dp[0][j]){
                dp[i][j] = dp[i - 1][j - 1] + 1;

                // length of longest common substring
                if(dp[i][j] > lenSubstring){
                    lenSubstring = dp[i][j];
                    finishPosSubstring = i;
                }
            }
        }
    }

    // generate substring with the length it's supposed to be and the position it finish
    // string s = t1.substr(finishPosSubstring - lenSubstring, lenSubstring);
    cout << finishPosSubstring - lenSubstring + 1 << " " << finishPosSubstring + 1 << endl;
    // return s;
}


int main(){

    //file names
    string transmission1 = "transmission1.txt";
    string transmission2 = "transmission2.txt";
    string mcode1 = "mcode1.txt";
    string mcode2 = "mcode2.txt";
    string mcode3 = "mcode3.txt";

    //get file data
    string trans1_data = readFile(transmission1);
    string trans2_data = readFile(transmission2);
    string mcode1_data = readFile(mcode1);
    string mcode2_data = readFile(mcode2);
    string mcode3_data = readFile(mcode3);

    //set data to lowercase
    toLowerCase(trans1_data);
    toLowerCase(trans2_data);
    toLowerCase(mcode1_data);
    toLowerCase(mcode2_data);
    toLowerCase(mcode3_data);

    cout << "PARTE 3" << endl;
    longestSubstring(trans1_data, trans2_data);
    // string s = longestSubstring(trans1_data, trans2_data);
    // cout << s << endl;

    return 0;
}