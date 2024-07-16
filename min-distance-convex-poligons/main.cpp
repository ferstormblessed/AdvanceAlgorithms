/*
    Actividad 4.2 Implementación Polígonos Convexos aplicando geometría computacional.

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

    Martes 1 de noviembre del 2022
*/

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

struct Point
{
    int x;
    int y;
};

//Time and space complexity O(1)
float distance(Point p1, Point p2){
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y , 2) * 1.0);
}

//Time Complexity O(n^2)
//Space Complexity O(n)
float minDistance(vector<Point> &points){
    vector<float> distances;

    for(int i = 0; i < points.size(); i++){
        for(int j = 0; j < points.size(); j++){
            float dis = distance(points[i], points[j]);
            distances.push_back(dis);
        }
    }

    float min = distances[1];
    for(int i = 0; i < distances.size(); i++){
        if(distances[i] < min && distances[i] > 0){
            min = distances[i];
        }
    }
    return min;
}

int main(){

    //n = number of points
    int n = 0;
    cin >> n;
    // cout << n << endl;

    //get points
    vector<Point> points(n);
    Point p;
    for(int i = 0; i < n; i++){
        cin >> p.x;
        cin >> p.y;
        points[i] = p;
    }

    float min = minDistance(points);
    cout << endl << endl;
    cout << "La distance mas corta es: " << min << endl;;
    cout << endl << endl;

    return 0;
}
