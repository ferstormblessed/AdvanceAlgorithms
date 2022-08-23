/*
    Actividad 1.2 Implementación de la técnica de programación "Programación dinámica" y "algoritmos avaros"

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez Flores A01635304

    Sabado 20 de agosto del 2022

*/


#include <iostream>
#include <algorithm>

using namespace std;

//Dynamic programming
//Time complexity O(n * m), where n = the change and m = the number of coins
//Space complexity O(n) 
void moneyChangeDynamic(int change, int coinDenomination[], int numberCoins){
    
    //Declare the array where the solutions are stored
    int dp[change + 1];

    //Fill array with largest possible number (change value)
    for(int i = 0; i < change + 1; i++){
        dp[i] = change + 1;
    }

    //Base case
    dp[0] = 0;

    //Buttom-up
    for(int i = 1; i < change + 1; i++){
        int currentChange = i;
        for(int j = 0; j < numberCoins; j++){
            int currentCoin = coinDenomination[j];
            if(currentChange - currentCoin >= 0){
                //change in dp if there is a better solution of coins
                dp[i] = min(dp[currentChange], 1 + dp[currentChange - currentCoin]);            
            }
        }
    }
    cout << "Minimum number of coins with Dynamic: " << dp[change] << endl << endl;
}

//Greedy implementation
//Time complexity O(n)
//Space complexity O(n)
void moneyChangeGreedy(int change, int coinDenomination[], int numberCoins){
    int numOfCoins = 0;
    for (int i = numberCoins - 1; i > -1; i--){
        int currentCoin = coinDenomination[i]; // i.e. 1,2,5,10,20
        int numberOfCurrCoin = change / currentCoin; // The number of that coin (denomination) for the change
        numOfCoins += numberOfCurrCoin;
        change = change % currentCoin; // the current change after calculate the number of coins of certain denominatio

        if(change == 0){
            cout << "Minimum number of coins with Greedy: " << numOfCoins << endl << endl;
            return;
        }
    }
}

int main(){

    //get the total number of coins
    int numberCoins = 0;
    cin >> numberCoins;

    //get the denomination of all the possible coins
    int coinDenominations[numberCoins];
    int coin = 0;
    for(int i = 0; i < numberCoins; i++){
        cin >> coin;
        coinDenominations[i] = coin;
    }

    //get the value of the product
    int valueProduct = 0;
    cin >> valueProduct;

    //get the denomination of bill or coin 
    int denominationToPay = 0;
    cin >> denominationToPay;

    if(valueProduct > denominationToPay){
        cout << "The product cost more than " << denominationToPay << endl; 
        return 0;
    }

    int change = denominationToPay - valueProduct;

    cout << endl << "Dynamic Implementation" << endl << endl;
    moneyChangeDynamic(change, coinDenominations, numberCoins);


    cout << endl << "Greedy Implementation" << endl << endl;
    moneyChangeGreedy(change, coinDenominations, numberCoins);

    return 0;
}