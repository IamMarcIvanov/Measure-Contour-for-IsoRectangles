#include "measure_primary.hpp"
#include "measure_structures.hpp"
#include "measure.hpp"
#include<bits/stdc++.h>
#include<fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>	 
using namespace std;
typedef long long ll;

int main()
{
for(int m=1; m<=8 ; m++)
{
	string s = std::to_string(m);
	vector<rectangle> iso_rectangles_input;
    ll n; //number of iso oriented rectangles
    fstream inData;
	inData.open("i" + s + ".txt");
    inData>>n;
    interval x,y;
    ll x1,x2,y1,y2;
    for(ll i=0;i<n;i++)
    {
        inData>>x1>>x2>>y1>>y2;
        x.bottom = x1; 
        x.top = x2;
        y.bottom = y1;
        y.top = y2;
        rectangle r;
        r.x_int = x;
        r.y_int = y;
        iso_rectangles_input.push_back(r);
    }
    if(n % 2 == 1)
    {
    	x.bottom = 1; 
        x.top = 1;
        y.bottom = 1;
        y.top = 1;
        rectangle r;
        r.x_int = x;
        r.y_int = y;
        iso_rectangles_input.push_back(r);
    }
    rectangle frame = findFrame(iso_rectangles_input);
    
    set<stripe> S = rectangle_DAC(iso_rectangles_input);

    ll measure_val = measure(S);
    cout<<"The area of the rectangles is "<<measure_val<<endl;
    inData.close();
    }
}
