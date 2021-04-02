#pragma once
#include "measure_structures.hpp"
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;



rectangle findFrame(vector<rectangle> iso_rectangles_input);

set<interval> y_partition(set<ll> y_coordinates);

set<ll> y_set(vector<rectangle> iso_rectangles_input);

set<interval> set_intersection(set<interval> i1, set<interval> i2);

set<interval> set_difference(set<interval> i1,set<interval> i2);

set<interval> set_union(set<interval> i1, set<interval> i2);

set<stripe> copy(set<stripe> S, set<ll> P, interval x_ext);

set<stripe> blacken(set<stripe> S, set<interval> J);

set<stripe> concat(set<stripe> s_left, set<stripe> s_right, set<ll> P, interval x_ext);

SRT stripes(set<edge> VRX, interval x_ext, interval ylimits);

set<stripe> rectangle_DAC(vector<rectangle> rect);
