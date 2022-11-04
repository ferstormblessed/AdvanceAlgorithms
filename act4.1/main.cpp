/*
    Actividad 4.1 Implementación Intersección y proximidad aplicando geometría computacional.

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

    Sabado 22 de octubre del 2022
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

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

struct Point
{
    int x;
    int y;
};

//Time and Space complexity O(n)
vector<Point> generatePoints(vector<int> &nums){
    vector<Point> points;
    Point p;
    for(int i = 0; i < nums.size(); i += 2){
        p.x = nums[i];
        p.y = nums[i + 1];
        points.push_back(p);
    }
    return points;
}

//Info on how to know if two segments of line intersect found on https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/

//Time and Space complexity O(1)
bool onSegment(Point p, Point q, Point r){
    //checking orientations
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) {
        return true;
    }
  
    return false;
}
  
// Find orientation of ordered triplet (p, q, r).
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
//Time and Space complexity O(1)
int orientation(Point p, Point q, Point r){
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
  
    if (val == 0) return 0;  // collinear
  
    return (val > 0)? 1: 2; // clock or counterclock wise
}
  
//Time and Space complexity O(n)
bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    // Find the four orientations needed for general and special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
  
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
  
    // Special Cases

    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
  
    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
  
    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
  
     // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
  
    return false; // Doesn't fall in any of the above cases
}


int main(){

    //read input for the points
    string s = readFile("in.txt");
    // cout << s << endl;

    //convert input to integers
    vector<int> p = convertStringToInt(s);
    // for(int i = 0; i < p.size(); i++){
    //     cout << p[i] << " ";
    // }

    //generate points
    vector<Point> points = generatePoints(p);

    // // print points
    // for(int i = 0; i < points.size(); i++){
    //     cout << points[i].x << " " << points[i].y << endl;
    // }

    cout << endl << endl;

    for(int i = 0; i < points.size(); i += 4){
        cout << doIntersect(points[i], points[i + 1], points[i + 2], points[i + 3]) << endl;
    }

    cout << endl << endl;


    return 0;
}