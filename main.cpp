/*
    Actividad 1.1 Implementación de la técnica de programación "divide y vencerás"

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

    Miercoles 9 de agosto del 2022
*/

#include <iostream> 
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;


void merge(float arr[], int start, int mid, int end){
    int start2 = mid + 1;

	// If the direct merge is already sorted 
	if (arr[mid] >= arr[start2]) {
		return;
	}

	// Two pointers to maintain start 
	// of both arrays to merge 
	while (start <= mid && start2 <= end) {

		// If element 1 is in right place 
		if (arr[start] >= arr[start2]) {
			start++;
		}
		else {
			float value = arr[start2];
			int index = start2;

			// Shift all the elements between element 1 
			// element 2, right by 1. 
			while (index != start) {
				arr[index] = arr[index - 1];
				index--;
			}
			arr[start] = value;

			// Update all the pointers 
			start++;
			mid++;
			start2++;
		}
	}
}

void mergeSort(float arr[], int l, int r) {

    //check if the subarrays are greater than 1 in length
    if (l < r) {
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

void printArray(float arr[], int size) {
    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
}

int main(int argc, char *argv[]) {

    //Get the length of the array from command-line
    int arrLength = 0;
    cin >> arrLength;
    
    cout << "arrLength: " << arrLength << endl;

    float arr[arrLength];

    // Fill the array to sort
    for(int i = 0; i < arrLength; i++){
        //int num = 0;
        cin >> arr[i];
    }

    cout << endl << "Original array" << endl;
    printArray(arr, arrLength);
    cout << endl;

    cout << endl << "Sorted array" << endl;
    mergeSort(arr, 0, arrLength - 1);
    printArray(arr, arrLength);
    cout << endl << endl;

    return 0;
}