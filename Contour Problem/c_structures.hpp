#pragma once
#include<bits/stdc++.h>
#include <iostream>
#include<string>
#include<sstream>
using namespace std;

///Description of point class
///
///This structure represents the x and y coordinates of the point
struct Point
{
    float x{};
    float y{};
};
///Brief description of interval structure
///
///This structure contains the lowest coordinate and highest coordinate which the interval spans through.
struct Interval
{
    ///Represents that lowest coordinate
    float bottom{};
    ///Represents that highest coordinate
    float top{};
    ///Definition of comparator to facilitate set insertions in a sorted order
    ///
    bool operator<(const Interval& i) const
    {
        if (this->bottom < i.bottom)
        {
            return true;
        }
        if (this->bottom == i.bottom)
        {
            if (this->top < i.top)
            {
                return true;
            }
        }
        return false;
    }
};
///Description of rectangle structure
///
///A rectangle can be defined by two intervals
struct Rectangle
{
    ///This data Structure gives the X bounds of the rectangle
    Point bottom_left{};
    ///This data Structure gives the Y bounds of the rectangle
    Point top_right{};
};
///Description of Edgetype structure
///
///This represents type of an Edge which could be TOP, BOTTOM, LEFT, RIGHT in a rectangle
enum Edgetype
{
    LEFT, RIGHT, BOTTOM, TOP
};

struct ContourPiece
{
    float x1;
    float x2;
    float y;
    ///Definition of comparator to facilitate set insertions in a sorted order
    ///
    bool operator<(const ContourPiece& cp) const
    {
        if (this->x1 < cp.x1)
        {
            return true;
        }
        if (this->x1 > cp.x1)
        {
            return false;
        }
        if (this->x2 < cp.x2)
        {
            return true;
        }
        if (this->x2 > cp.x2)
        {
            return false;
        }
        if (this->y < cp.y)
        {
            return true;
        }
        return false;
    }
};
///Description of edge structure
///
///This structure contains a point, an interval between which the edge spans, and an edge type.
struct Edge
{
    ///An Edge spans between this interval also giving the length of the edge,
    Interval span{};
    ///This is the fixed coordinate of the edge
    float coord{};
    ///This shows the edge type of the edge
    Edgetype side{};

    /*
     * Only handles vertical edge sorting
     */
    ///Definition of comparator to facilitate set insertions in a sorted order
    ///
    bool operator<(const Edge& e) const
    {
        if (this->coord < e.coord)
        {
            return true;
        }
        if (this->coord == e.coord)
        {
            if(this->side == LEFT and e.side == RIGHT) {
                return true;
            }
            else if (this->side == RIGHT and e.side == LEFT)
            {
                return false;
            }
            else
            {
                if (this->span.bottom < e.span.bottom)
                {
                    return true;
                }
                if (this->span.bottom == e.span.bottom)
                {
                    if (this->span.top < e.span.top)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

enum Lru
{
    L, R, U
};
///Description of Ctree
///
///
struct Ctree
{
    float x{};
    Lru side{};
    struct Ctree* lson{};
    struct Ctree* rson{};

    bool operator==(const Ctree& c1) const
    {
        if ((this->x == c1.x) and
            (this->side == c1.side) and
            (this->lson == c1.lson) and
            (this->rson == c1.rson))
        {
            return true;
        }
        return false;
    }
};
///Description of ContourStripe
///
struct ContourStripe
{
    Interval x_interval{};
    Interval y_interval{};
    Ctree* tree{};

    bool operator<(const ContourStripe& s) const
    {
        if (this->y_interval.bottom < s.y_interval.bottom)
        {
            return true;
        }
        if (this->y_interval.bottom == s.y_interval.bottom)
        {
            if (this->y_interval.top < s.y_interval.top)
            {
                return true;
            }
        }
        return false;
    }
};
///Description of CommonStripeOutput
///
///
struct CommonStripeOutput
{
    set<Interval> L{};
    set<Interval> R{};
    set<float> P{};
};
///Description of CommonMergeOutput
///
///
struct CommonMergeOutput
{
    CommonStripeOutput CSO{};
    set<Interval> L1LR;
    set<Interval> R2LR;
};

///Description of ContourStripe
///
///
struct ContourStripeOutput
{
    CommonStripeOutput CSO{};
    set<ContourStripe> S{};
};

