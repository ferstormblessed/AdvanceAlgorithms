/*
    Actividad 1.2 Implementación de la técnica de programación "Programación dinámica" y "algoritmos avaros"

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez Flores A01635304

    Miercoles 17 de agosto del 2022

*/


#include <iostream>

using namespace std;

//Dynamic programming
//Time complexity O(n)
//Space complexity O(n)

void moneyChangeDynamic(int change, int coinDenomination[], int numberCoins, int coinChange[]){
    for (int i = numberCoins - 1; i > -1; i--){
        int currentCoin = coinDenomination[i]; // i.e. 1,2,5,10,20
        int numberOfCurrCoin = change / currentCoin; // The number of that coin (denomination) for the change
        coinChange[i] = numberOfCurrCoin;
        change = change % currentCoin; // the current change after calculate the number of coins of certain denominatio

        if(change == 0){
            return;
        }
    }
}

//Greedy implementation
//Time complexity O(1)
//Space complexity O(1)

void moneyChangeGreedy(int change, int coinDenomination[], int numberCoins, int coinChange[]){
    for (int i = numberCoins - 1; i >= 0; i--) {
        // Find denominations
        int currCoin = coinDenomination[i];
        int numberOfCurrCoin = 0;
        while (change >= currCoin) {
            change -= currCoin;
            numberOfCurrCoin++;
        }
        coinChange[i] = numberOfCurrCoin;
    }
}

void printArray(int arr[], int coins[], int size) {
    for(int i = 0; i < size; i++){
        cout << "$" << coins[i] << " -> " << arr[i] << endl;
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

    //array of number of coins of each denomination for the change /dynamic/
    int coinsChangeDynamic[numberCoins];
    for(int i = 0; i < numberCoins; i++){
        coinsChangeDynamic[i] = 0;
    }
    //array of number of coins of each denomination for the change /greedy/
    int coinsChangeGreedy[numberCoins];
    for(int i = 0; i < numberCoins; i++){
        coinsChangeDynamic[i] = 0;
    }

    cout << endl << "Dynamic Implementation" << endl << endl;
    moneyChangeDynamic(change, coinDenominations, numberCoins, coinsChangeDynamic);
    cout << "Expected change: $" << change << endl;
    printArray(coinsChangeDynamic, coinDenominations, numberCoins);
    cout << endl << endl; 

    cout << endl << "Greedy Implementation" << endl << endl;
    moneyChangeGreedy(change, coinDenominations, numberCoins, coinsChangeGreedy);
    cout << "Expected change: $" << change << endl;
    printArray(coinsChangeGreedy, coinDenominations, numberCoins);
    cout << endl << endl; 

    return 0;
}