#pragma once
#include "c_structures.hpp"
#include<bits/stdc++.h>
using namespace std;

set<Interval> planePartition(set<float> coords);

set<Interval> setIntersection(set<Interval> first, set<Interval> second);

set<Interval> setUnion(set<Interval> first, set<Interval> second);

set<float> floatUnion(set<float> first, set<float> second);

set<Interval> setDifference(set<Interval> first, set<Interval> second);

set<Edge> getVerticalEdges(vector<Rectangle> rectangles);

set<Edge> getHorizontalEdges(vector<Rectangle> rectangles);

tuple<set<Edge>, set<Edge>, float> divide(set<Edge> V);

CommonStripeOutput baseCaseLRP(Edge e);

CommonMergeOutput mergeLRP(pair<CommonStripeOutput, CommonStripeOutput> conquer_output);

