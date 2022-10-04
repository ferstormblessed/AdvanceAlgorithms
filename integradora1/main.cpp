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

/*
t1 = abcdef
t2 = zabcht
    0   1   2   3   4   5   6
0   0   z   a   b   c   h   t
    0   0   0   0   0   0   0
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
    vector<vector<int> > dp(t1.length() + 2);
    for(int i = 0; i < dp.size(); i++){
        dp[i].resize(t2.size() + 2);
    }
    dp[0][0] = 0;
    dp[0][1] = 0;
    dp[1][0] = 0;
    dp[1][1] = 0;
    //fill column 0 with the characters from t1
    for(int i = 2; i < dp.size(); i++){
        dp[i][0] = t1[i - 2];
    }
    //fill row 0 with the characters from t2
    for(int i = 2; i < dp[0].size(); i++){
        dp[0][i] = t2[i - 2];
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
vector<int> longestSubstring(string &t1, string &t2){
    //create dp
    vector<vector<int> > dp = createDP(t1, t2);
    //length of the longest common substring
    int lenSubstring = 0;
    //position in the string where the substring ends
    int finishPosSubstring = 0;

    for(int i = 2; i < dp.size(); i++){
        for(int j = 2; j < dp[i].size(); j++){
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

    vector<int> res;
    res.push_back(lenSubstring);
    res.push_back(finishPosSubstring);

    // generate substring with the length it's supposed to be and the position it finish
    // string s = t1.substr(finishPosSubstring - lenSubstring, lenSubstring);
    // cout << finishPosSubstring - lenSubstring + 1 << " " << finishPosSubstring + 1 << endl;
    return res;
}

// PARTE 1
// mcodes in transmissions?

//Time Complexity = LongestSubstring Time Complexity
//Space Complexity = LongestSubstring Space Complexity
bool checkMcodeInTransmission(string &transmission, string &mcode){
    vector<int> res = longestSubstring(transmission, mcode);
    int len = res[0];
    // cout << "len: " << len << " mcode.length: " << mcode.length() << endl;
    if(len == mcode.length()){
        return true;
    }
    return false;
}

//Time Complexity O(m * n), where m = number of transmission files and n = number of mcode files
//Space Complexity = checkMcodeInTransmission Space Complexity
void part1(vector<string> &transmissionFiles, vector<string> &mcodeFiles){
    for(int i = 0; i < transmissionFiles.size(); i++){
        for(int j = 0; j < mcodeFiles.size(); j++){
            if(checkMcodeInTransmission(transmissionFiles[i], mcodeFiles[j])){
                cout << "True | mcode" << j + 1 << ".txt in transmission" << i + 1 << ".txt" << endl; 
            }
            else{
                cout << "False | mcode" << j + 1 << ".txt in transmission" << i + 1 << ".txt" << endl; 
            }

        }
    }
}

// PARTE 2
// CODIGO ESPEJEADO

void part2(vector<string> transmissionFiles, vector<string> mcodeFiles){
    for(int i = 0; i < transmissionFiles.size(); i++){
        for(int j = 0; j < mcodeFiles.size(); j++){
             if(transmissionFiles[i].find(mcodeFiles[j]) != -1){
                int index = transmissionFiles[i].find(mcodeFiles[j]);
                cout << "mcode" << j + 1 << " en transmissions" << i + 1 << "\n";
                cout << "inicio: " << index << "\n";
                cout << "fin: " << index + mcodeFiles[j].length() << "\n\n";
            }
        }
    }
}

// PARTE 3 
// LONGEST COMMON SUBSTRING BETWEEN TRANSMISSION 1 AND TRANSMISSION 2

//Time Complexity O(1)
//Space Complexity O(1)
void part3(vector<int> strs){
    //print positions of start and finish of the longest common substring 
    int len = strs[0];
    if(len <= 1){
        cout << "Longest common substring is equal or less than length 1" << endl;
        return;
    }
    int finishPos = strs[1];
    // cout << "Finish pos: " << finishPos << " len: " << len << endl;
    cout << finishPos - len << " " << finishPos - 1 << endl;
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

    // //PARTE 1
    cout << endl <<  "PARTE 1" << endl;
    vector<string> transmissionFiles;
    vector<string> mcodeFiles;

    transmissionFiles.push_back(trans1_data);
    transmissionFiles.push_back(trans2_data);
    mcodeFiles.push_back(mcode1_data);
    mcodeFiles.push_back(mcode2_data);
    mcodeFiles.push_back(mcode3_data);
    part1(transmissionFiles, mcodeFiles);

    // PARTE 2
    cout << endl << "PARTE 2" << endl << endl;
    part2(transmissionFiles, mcodeFiles);

    //PARTE 3
    cout << endl <<  "PARTE 3" << endl;
    vector<int> part3strings = longestSubstring(trans1_data, trans2_data);
    part3(part3strings);

    //ver el dp
    // vector<vector<int> > dp = createDP(trans1_data, mcode1_data);
    // for(int i = 0; i < dp.size(); i++){
    //     for(int j = 0; j < dp[i].size(); j++){
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}