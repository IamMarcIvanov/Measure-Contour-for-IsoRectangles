#pragma once
#include "c_structures.hpp"
#include<bits/stdc++.h>
using namespace std;

set<ContourStripe> contourCopy(set<ContourStripe> S, set<float> P, Interval x_int);

set<ContourStripe> contourBlacken(set<ContourStripe> S, set<Interval> J);

set<ContourStripe> contourConcat(set<ContourStripe> S1, set<ContourStripe> S2, set<float> P, Interval x_int);

ContourStripeOutput contourBaseCaseFinal(CommonStripeOutput intermediate, Edge e, Interval x_ext);

set<ContourStripe> contourFinal(CommonMergeOutput intermediate, pair<ContourStripeOutput, ContourStripeOutput> conquer_output, Interval x_ext, float x_m);

ContourStripeOutput contourStripes(set<Edge> V, Interval x_ext);

set<ContourStripe> contourRectangleDAC(vector<Rectangle> rectangles);

vector<Ctree*> getLeafNodes(Ctree* root);

set<ContourPiece> getContourPieces(Edge h, ContourStripe s);

set<ContourPiece> getContour(vector<Rectangle> rectangles, set<ContourStripe> S);

vector<string> split(const string& str, const string& delim);
