#include "c_primary.hpp"
#include "c_structures.hpp"
#include "c_contour.hpp"
#include<bits/stdc++.h>
#include<fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>	 
using namespace std;

int main()
{
    fstream myfile;
    myfile.open("i7.txt");
    string n_str;
    getline(myfile, n_str);
    int n = stoi(n_str);
    //cout << n;
    vector<Rectangle> rectangles;
    vector<Rectangle> flipped_rectangles;
    for (int i = 0; i < n; i++)
    {
        string rect_str;
        getline(myfile, rect_str);
        vector<string> points = split(rect_str, " ");
        Point bottom_left = Point{stof(points[0]), stof(points[2])};
        Point top_right = Point{stof(points[1]), stof(points[3])};
        rectangles.push_back(Rectangle{bottom_left, top_right});
        Point flipped_bottom_left = Point{stof(points[2]), stof(points[0])};
        Point flipped_top_right = Point{stof(points[3]), stof(points[1])};
        flipped_rectangles.push_back(Rectangle{flipped_bottom_left, flipped_top_right});
    }
    myfile.close();

    set<ContourStripe> S_prime = contourRectangleDAC(rectangles);
    set<ContourPiece> horizontal = getContour(rectangles, S_prime);
    ofstream outData;
    outData.open("opC.txt");
    //cout << "HORIZONTAL CONTOUR" << endl;
    for (auto& piece : horizontal)
    {
        //cout << piece.y << " " << piece.x1 << " " << piece.x2 << endl;
        outData << piece.y << " " << piece.x1 << " " << piece.x2 << endl;
    }

    set<ContourStripe> S_prime_flipped = contourRectangleDAC(flipped_rectangles);
    set<ContourPiece> vertical = getContour(flipped_rectangles, S_prime_flipped);
    outData << "vert" <<endl;
    for (auto& piece : vertical)
    {
        outData << piece.y << " " << piece.x1 << " " << piece.x2 << endl;
    }
	
    return 0;
}
