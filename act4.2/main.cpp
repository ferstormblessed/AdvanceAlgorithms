/*
    Actividad 4.2 Implementación Polígonos Convexos aplicando geometría computacional.

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

    Domingo 22 de octubre del 2022
*/

#include <iostream>
#include <stack>

using namespace std;

// Info on what is a convex hull and how to calculate it with points and graham's scan algorithm from https://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/

struct Point
{
    int x;
    int y;
};

//Bottom-most point. Needed for sorting points
Point p0;

//Find the next to top the stack
//Time and Space Complexity O(1)
Point nextToTop(stack<Point> &S){
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

//Swap two points
//Time and Space Complexity O(1)
void swap(Point &p1, Point &p2){
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

//Get the square distance between point1 and point2
//Time and Space Complexity O(1)
int distSq(Point p1, Point p2){
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

// To find orientation of ordered triplet (p, q, r).
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
//Time and Space Complexity O(1)
int orientation(Point p, Point q, Point r){
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;  // collinear
    return (val > 0) ? 1: 2; // clock or counterclock wise
}
 
// A function used by library function qsort() 
// qsort() sorts an array of points with respect to the first point
//Time and Space Complexity O(1)
int compare(const void *vp1, const void *vp2){
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;
 
    // Find orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0){
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;
    }
 
    return (o == 2) ? -1 : 1;
}
 
// Prints convex hull of a set of n points.
//Time Complexity O(nlogn)
//Space Complexity O(n)
void convexHull(Point points[], int n){
    // Find the bottommost point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++){
        int y = points[i].y;
    
        // Pick the bottom-most or choose the left most point in case of tie
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)){
            ymin = points[i].y, min = i;
        }
    }
    
    // Place the bottom-most point at first position
    swap(points[0], points[min]);
    
    // Sort n-1 points with respect to the first point.
    // A point p1 comes before p2 in sorted output if p2  has larger polar angle (in counterclockwise direction) than p1
    p0 = points[0];
    qsort(&points[1], n-1, sizeof(Point), compare);
    
    // If two or more points make same angle with p0, Remove all but the one that is farthest from p0
    
    // Initialize size of modified array
    int m = 1; 
    for (int i = 1; i < n; i++){
        // Keep removing i while angle of i and i+1 is same with respect to p0
        while (i < n-1 && orientation(p0, points[i], points[i+1]) == 0){
            i++;
        }
    
        points[m] = points[i];

        // Update size of modified array
        m++; 
    }
    
    // If modified array of points has less than 3 points, convex hull is not possible
    if (m < 3) return;
    
    // Create an empty stack and push first three points to it.
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);
    
    // Process remaining n-3 points
    for (int i = 3; i < m; i++){
        // Keep removing top while the angle formed by points next-to-top, top, and points[i] makes a non-left turn
        while (S.size()>1 && orientation(nextToTop(S), S.top(), points[i]) != 2){
            S.pop();
        }

        S.push(points[i]);
    }
    
    // Now stack contains the output points
    while (!S.empty()){
        Point p = S.top();
        cout << "(" << p.x << ", " << p.y <<")" << endl;
        S.pop();
    }
}


int main(){

    //n = number of points
    int n;
    cin >> n;
    // array with the points
    Point points[n];
    //fill array
    Point p;
    for(int i = 0; i < n; i++){
        cin >> p.x;
        cin >> p.y;
        points[i] = p;
    }

    cout << endl << endl;
    convexHull(points, n);
    cout << endl << endl;

    return 0;
}