/*
    Actividad 5.2 Implementación backtracking con Bitmask

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

    Martes 8 de noviembre del 2022
*/

//info from https://www.tutorialspoint.com/bitmasking-and-dynamic-programming-in-cplusplus AND https://www.geeksforgeeks.org/bitmasking-and-dynamic-programming-set-1-count-ways-to-assign-unique-cap-to-every-person/

#include <iostream>
#include <vector>
#include <fstream>

#define MOD 1000000007

using namespace std;

//store the caps of each person by id of person
//hat[1] = persons(1, 2)
vector<int> capList[101];

//keep record of who is wearing which cap
int dp[1025][101];

//store all combinations, to check if all persons hava a cap
int allmask;

//Time and Space complexity O(n)
string readFile(string fileName){
    string t = "";
    //read file
    ifstream file(fileName);
   
    //file to text
    while(file){
        char c;
        c = file.get();
        if(c == ' '){
            c = '%';
        }
        t += c;
    }

    file.close();
    t.pop_back();
    
    return t;
}

//Time and Space complexity O(n)
vector<vector<int> > convertStringToInt(string &in){
    string num = "";
    vector<int> nums;
	vector<vector<int> > hats;
    for(int i = 0; i < in.length(); i++){
        num += in[i];
        if(in[i] == '%'){
            // cout << "Num antes de conversion " << num << endl;
            num.pop_back();
            int n = stoi(num);
            nums.push_back(n);
            num = "";
        }
		if(in[i] == '\n'){
			num.pop_back();
            int n = stoi(num);
            nums.push_back(n);
            num = "";
			hats.push_back(nums);
			nums.clear();
		}

        //edge case
        if(i == in.length() - 1 && num.length() >= 1){
            int n = stoi(num);
            nums.push_back(n);
			hats.push_back(nums);
        }

    }
    return hats;
}

//Time Complexity O()
//Space Complexity O(2^n * n)
long long int countWays(int mask, int i) {
	//everyone has a cap
	if (mask == allmask) return 1;

	//no possible answer
	if (i > 100) return 0;

	//already store in dp
	if (dp[mask][i] != -1) return dp[mask][i];

	//recursive call 
	long long int ways = countWays(mask, i+1);

	// total number of persons having cap with id i.
	int size = capList[i].size();

	// assign caps
	for (int j = 0; j < size; j++) {
		if (mask & (1 << capList[i][j])) continue;

		else{
			ways += countWays(mask | (1 << capList[i][j]), i+1);
		}
		ways %= MOD;
	}

	return dp[mask][i] = ways;
}


// Driver Program
int main()
{
	string s = readFile("in.txt");
    //get hats
    vector<vector<int> > hats = convertStringToInt(s);
    //n = num of persons
    int n = hats[0][0];
    hats.erase(hats.begin());

	// cout << n << endl << endl;
	// for(int i = 0; i < hats.size(); i++){
	// 	for(int j = 0; j < hats[i].size(); j++){
	// 		cout << hats[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }

	//fill caplist
	for(int i = 0; i < hats.size(); i++){
		for(int j = 0; j < hats[i].size(); j++){
			int pos = hats[i][j];
			capList[pos].push_back(i);
		}
	}

	allmask = (1 << n) - 1;
   	memset(dp, -1, sizeof dp);


	cout << endl << endl;
	cout << countWays(0, 1) << endl;
	cout << endl << endl;

	return 0;
}
