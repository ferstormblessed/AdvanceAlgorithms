/*
    Actividad 4.2 Implementación Polígonos Convexos aplicando geometría computacional.

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

    Domingo 22 de octubre del 2022
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

//Time and Space complexity O(n)
string readFile(string fileName){
    string t = "";
    //read file
    ifstream file(fileName);
   
    //file to text
    while(file){
        char c;
        c = file.get();
        if(c == ',' || c == '\n'){
            c = '%';
        }
        t += c;
    }

    file.close();
    t.pop_back();
    
    return t;
}

//Time and Space complexity O(n)
vector<int> convertStringToInt(string &in){
    string num = "";
    vector<int> nums;
    for(int i = 0; i < in.length(); i++){
        num += in[i];
        if(in[i] == '%'){
            // cout << "Num antes de conversion " << num << endl;
            num.pop_back();
            int n = stoi(num);
            nums.push_back(n);
            num = "";
        }

        //edge case
        if(i == in.length() - 1 && num.length() >= 1){
            int n = stoi(num);
            nums.push_back(n);
        }

    }
    return nums;
}

// generate random number in a range
int getRandom(int x, int y){
    srand(time(NULL));
    return (x + rand() % (y - x + 1));
}

int randomizedBinarySearch(vector<int> &arr, int l, int r, int x){
    if (r >= l){
        // get our middle pointer randomly
        int mid = getRandom(l, r);
 
        if (arr[mid] == x)
            return mid;
        
        //element in left subarray
        if (arr[mid] > x)
          return randomizedBinarySearch(arr, l, mid-1, x);
 
        //element in right subsarray
        return randomizedBinarySearch(arr, mid + 1, r, x);
    }
    
    //element not in array
    return -1;
}

int main(){
    string s = readFile("in.txt");

    //get array
    vector<int> nums = convertStringToInt(s);
    //taget
    int target = nums[0];
    nums.erase(nums.begin());
    // for(int i = 0; i < nums.size(); i++){
    //     cout << nums[i] << " ";
    // }

    int search = randomizedBinarySearch(nums, 0, nums.size(), target);

    cout << endl << endl;

    if(search != -1){
        cout << "El elemento esta presente en el indice: " << search << endl;
    }
    else{
        cout << "El elemento no esta presente en el arreglo" << endl;
    }

    cout << endl << endl;

    return 0;
}