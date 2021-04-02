#include "c_structures.hpp"
#include<bits/stdc++.h>
using namespace std;

/*! Creates continuous intervals for a given set of points along Y axis
    \param y_coordinates a set of integers representing the coordinate points for partitioning
    \return Set of intervals representing the partition induced by y coordinates 
*/
set<Interval> planePartition(set<float> coords)
{
    float min_val = -FLT_MAX;
    set<Interval> output;
    for (auto& coord : coords)
    {
        if(coord > min_val)
        {
            output.insert(Interval{min_val, coord});
            min_val = coord;
        }
    }
    return output;
}
/*! Gets the intersection of two sets of intervals
    \param i1 defines a set of intervals
    \param i2 defines a set of intervals
    \return A set of intervals which contain those intervals in i1 and i2 which have the same minimum and maximum values
*/
set<Interval> setIntersection(set<Interval> first, set<Interval> second)
{
    set<Interval> ans;
    auto f = first.begin();
    auto s = second.begin();
    while(f!=first.end() and s!=second.end())
    {
        if((*f).bottom < (*s).bottom)
        {
            f++;
        }
        else if((*f).bottom > (*s).bottom)
        {
            s++;
        }
        else
        {
            if((*f).top < (*s).top)
            {
                f++;
            }
            else if((*f).top > (*s).top)
            {
                s++;
            }
            else
            {
                ans.insert(*f);
                f++;
                s++;
            }
        }
    }
    return ans;
}
/*! Gets the union of two sets of intervals
    \param i1 defines a set of intervals
    \param i2 defines a set of intervals
    \return Set of unique intervals belonging to i1 or i2
*/
set<Interval> setUnion(set<Interval> first, set<Interval> second)
{
    set<Interval> ans;
    for(auto& f : first)
    {
        ans.insert(f);
    }
    for(auto& s : second)
    {
        ans.insert(s);
    }
    return ans;
}

/*! Gets the union of two sets of intervals
    \param first defines a set of floats
    \param second defines a set of floats
    \return Set of floats which is union of the sets
*/
set<float> floatUnion(set<float> first, set<float> second)
{
    set<float> ans;
    for(auto& f : first)
    {
        ans.insert(f);
    }
    for(auto& s : second)
    {
        ans.insert(s);
    }
    return ans;
}
/*! Gets the difference of two sets of intervals
    \param i1 defines a set of intervals
    \param i2 defines a set of intervals
    \return Set of intervals in i1 that do not belong to i2
*/
set<Interval> setDifference(set<Interval> first, set<Interval> second)
{
    set<Interval> ans;
    auto f = first.begin();
    auto s = second.begin();
    while(f!=first.end() and s!=second.end())
    {
        if((*f).bottom < (*s).bottom)
        {
            ans.insert(*f);
            f++;
        }
        else if((*f).bottom > (*s).bottom)
        {
            s++;
        }
        else
        {
            if((*f).top < (*s).top)
            {
                ans.insert(*f);
                f++;
            }
            else if((*f).top == (*s).top)
            {
                f++;
                s++;
            }
            else
            {
                s++;
            }
        }
    }
    while(f!=first.end())
    {
        ans.insert(*f);
        f++;
    }
    return ans;
}
/*! this function gives the vertical edges of the given rectangle
    \param rectangles are the rectangle whose vertical edges is to be found
    \return gives the set of vertical edges 
*/
set<Edge> getVerticalEdges(vector<Rectangle> rectangles)
{
    set<Edge> verticalEdges;
    for (auto& rectangle : rectangles)
    {
        Interval y_interval = Interval{rectangle.bottom_left.y, rectangle.top_right.y};
        Edge left_edge{y_interval, rectangle.bottom_left.x, LEFT};
        Edge right_edge{y_interval, rectangle.top_right.x, RIGHT};
        verticalEdges.insert(left_edge);
        verticalEdges.insert(right_edge);
    }
    return verticalEdges;
}
/*! this function gives the horizontal edges of the given rectangle
    \param rectangles are the rectangle whose vertical edges is to be found
    \return gives the set of horizontal edges 
*/
set<Edge> getHorizontalEdges(vector<Rectangle> rectangles)
{
    set<Edge> horizontalEdges;
    for (auto& rectangle : rectangles)
    {
        Interval x_interval = Interval{rectangle.bottom_left.x, rectangle.top_right.x};
        Edge bottom_edge{x_interval, rectangle.bottom_left.y, BOTTOM};
        Edge top_edge{x_interval, rectangle.top_right.y, TOP};
        horizontalEdges.insert(bottom_edge);
        horizontalEdges.insert(top_edge);
    }
    return horizontalEdges;
}

/*! divides vertical edges and finds xm
    \param V represents set of edges in V
    \return two Set of edges that are divided by xm
*/
tuple<set<Edge>, set<Edge>, float> divide(set<Edge> V)
{
    float x_m;
    set<Edge> left;
    set<Edge> right;
    int n = V.size();
    auto edge = V.begin();
    for(int i=0; i<n/2; i++)
    {
        left.insert(*edge);
        edge++;
    }
    x_m = (*edge).coord;
    for(int i=n/2; i<n; i++)
    {
        right.insert(*edge);
        edge++;
    }
    tuple<set<Edge>, set<Edge>, float> output(left, right, x_m);
    return output;
}
/*! Gets the stripe output
    \param e represents an edge 
    \return a stripe for the given edge
*/
CommonStripeOutput baseCaseLRP(Edge e)
{
    set<Interval> L;
    set<Interval> R;
    set<float> P;
    if (e.side == LEFT)
    {
        L.insert(e.span);
    }
    else
    {
        R.insert(e.span);
    }
    P.insert(-FLT_MAX);
    P.insert(e.span.bottom);
    P.insert(e.span.top);
    P.insert(FLT_MAX);
    return CommonStripeOutput{L, R, P};
}
/*! Gives the merge output after conquer of smaller cases
    \param Conquer_output gives the stripe of the base cases conquered
    \return merge of the pair of conquer output given
*/
CommonMergeOutput mergeLRP(pair<CommonStripeOutput, CommonStripeOutput> conquer_output)
{
    CommonStripeOutput left_output = conquer_output.first;
    CommonStripeOutput right_output = conquer_output.second;
    set<Interval> L1 = left_output.L;
    set<Interval> L2 = right_output.L;
    set<Interval> R1 = left_output.R;
    set<Interval> R2 = right_output.R;
    set<float> P1 = left_output.P;
    set<float> P2 = right_output.P;
    set<Interval> LR = setIntersection(L1, R2);
    set<Interval> L1LR = setDifference(L1, LR);
    set<Interval> R2LR = setDifference(R2, LR);
    set<Interval> L = setUnion(L1LR, L2);
    set<Interval> R = setUnion(R1, R2LR);
    set<float> P = floatUnion(P1, P2);
    CommonStripeOutput CSO = CommonStripeOutput{L, R, P};
    return CommonMergeOutput{CSO, L1LR, R2LR};
}
