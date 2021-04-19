#include <iostream>
#include<stdio.h>
#include <map>
#include<vector>
#include<iterator>
#include <bits/stdc++.h>

using namespace std;

struct Point{
    string address;
    float x;
    float y;
};

map <string, int> mapper;
list<Point> opAddress; //Return ordered list
float c = 0;
float cost = 1000;


// MATRIX IMPLEMENTATION FROM VECTOR OF ADDRESSES

float getDistance (int x1, int x2, int y1, int y2){
    float distance = 0;

    distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2))*1.0f;
    return distance;
}

float** createMatrix(vector <Point> addresses) {
    float** graph = 0;
   // float graph[addresses.size()][addresses.size()];
    graph = new float*[addresses.size()];
    for(int h = 0; h < addresses.size(); h++){
        graph[h] = new float[addresses.size()];
    }
    Point from;
    Point to;
    float distance;
    int j = 0;

    for (int i = 0; i < addresses.size(); i++) {
        from = addresses[i];
        for (int k = 0; k < addresses.size(); k++) {

            to = addresses[k];
            distance = getDistance(from.x, to.x, from.y, to.y);

            if (mapper.find(from.address) == mapper.end()) {
                mapper[from.address] = j++;
            }
            if (mapper.find(to.address) == mapper.end()) {
                mapper[to.address] = j++;
            }
            graph[mapper[from.address]][mapper[to.address]] = distance;
        }
       // cout << graph[mapper[from.address]][mapper[to.address]] << endl;
    }
    return graph;
}


float** createMatrixTest(vector <float> addresses) {
    float** graph = 0;
    // float graph[addresses.size()][addresses.size()];
    graph = new float*[addresses.size()];
    for(int h = 0; h < addresses.size(); h++){
        graph[h] = new float[addresses.size()];
    }

    int cnt = 0;
    for (int i = 0; i < addresses.size(); i++) {
        for (int j = 0; j < addresses.size(); j++) {
            graph[i][j] = addresses[cnt];
            cnt++;
        }

    }
        // cout << graph[mapper[from.address]][mapper[to.address]] << endl;

    return graph;
}

// NEAREST NEIGHBOR ALGORITHM

void swap(int *x, int *y)
{
    float temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
void minCost(vector<Point> points, float**graph){

    int i;
    float sum = 0;
    int dimensions[points.size()];
    float temp;

    for (i = 0; i< points.size(); i++){ //array with dimensions of graph
        dimensions[i] = i;
    }

    for (i = 0; i <= points.size(); i++){
        sum += graph[dimensions[i % points.size()]][dimensions[(i + 1) % points.size()]];
//        cout << sum << endl;
    }

    if (cost > sum){
        cost = sum;

    }
}

void fixMinCost( float**graph, vector<Point> points, int i){

    int dimensions[points.size()];

    for (i = 0; i< points.size(); i++){ //array with dimensions of graph
        dimensions[i] = i;
    }

    if (i == points.size()){
        minCost(points, graph);
    }

    else{

        for (int j = i; j <= points.size(); j++)
        {
            swap((dimensions + i), (dimensions + j));
            fixMinCost( graph, points, i+1);
            swap((dimensions + i), (dimensions + j));
        }
    }
}

//CHRISTOFIDES ALGORITHM



int main() {

    Point p1;
    p1.address = "addy1";
    p1.x = 10.5;
    p1.y = 5;

    Point p2;
    p2.address = "addy2";
    p2.x = 21;
    p2.y = 38.2;

    Point p3;
    p3.address = "addy3";
    p3.x = 31;
    p3.y = 33;


    vector<Point> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    float **graph = createMatrix(points);


    printf("Array contents: \n");

    for (int h = 0; h < points.size(); h++)
    {
        for (int w = 0; w < points.size(); w++)
        {
            cout << graph[h][w] << ",";
        }
        cout << endl;
    }


   fixMinCost(graph, points, 0);
    cout << cost << endl;


        return 0;
    }


