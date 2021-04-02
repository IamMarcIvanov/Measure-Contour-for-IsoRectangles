#pragma once
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


///Description of point class
///
///This structure represents the x and y coordinates of the point
typedef struct point
{
    ll x,y;
}point;

///Brief description of interval structure
///
///This structure contains the lowest coordinate and highest coordinate which the interval spans through.
typedef struct interval
{
    ///Represents that lowest coordinate
    ll bottom;
    ///Represents that highest coordinate
    ll top;
    ///Definition of comparator to facilitate set insertions in a sorted order
    ///
    bool operator<(const interval& e) const
    { 
        if(this->bottom<e.bottom)
        {
            return true;
        }
        else if(this->bottom==e.bottom)
        {
            if(this->top<e.top)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
}interval;
///Description of rectangle structure
///
///A rectangle can be defined by two intervals
typedef struct rectangle
{
    ///This data Structure gives the X bounds of the rectangle
    interval x_int;
    ///This data Structure gives the Y bounds of the rectangle
    interval y_int;
}rectangle;
///Description of edge structure
///
///This structure contains a point, an interval between which the edge spans, and an edge type.
typedef struct edge
{
    ///An Edge could be of type TOP, BOTTOM, LEFT, RIGHT in a rectangle
    string edgetype;
    ///An Edge spans between this interval also giving the length of the edge,
    interval i;
    ///This is the fixed coordinate of the edge
    ll x;
    ///Definition of comparator to facilitate set insertions in a sorted order
    ///
    bool operator<(const edge& e) const
    { 
        if(this->x < e.x)
        {
            return true;
        }
        else if(this->x == e.x)
        {
        
            if(this->edgetype == "LEFT" and e.edgetype == "RIGHT")
            {
                return true;
            }
            else if(this->edgetype == "RIGHT" and e.edgetype == "LEFT")
            {
                return false;
            }
            else
            {
                if(this->i.bottom < e.i.bottom)
                {
                    return true;
                }
                else if(this->i.bottom == e.i.bottom)
                {
                    if(this->i.top < e.i.top)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
        } 
        else
        {
            return false;
        }
    }
}edge;

///Description of stripe structure
///
///The frame is partitioned into horizontal stripes which is represented by this structure.
typedef struct stripe
{
    ///This represents bounds of the stripe in X-direction as an interval.
    interval x_int;
    ///This represents bounds of the stripe in Y-direction as an interval.
    interval y_int;
    ///this represents bounds of the stripe which belongs to the union of the rectangle.
    ll x_union;
    ///Definition of comparator to facilitate set insertions in a sorted order
    ///
    bool operator<(const stripe& e) const
    { 
        if(this->y_int.bottom<e.y_int.bottom)
        {
            return true;
        }
        else if (this->y_int.bottom==e.y_int.bottom)
        {
            if(this->y_int.top<e.y_int.top)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
}stripe;





///Description of StripeReturnType
///
///This structure is a collection of all the returned components in the stripes algorithm
typedef struct StripeReturnType
{
    ///This represents a set of interval to the Left side of the median
    set<interval> L;
    ///This represents a set of interval to the Right side of the median
    set<interval> R;
    ///This represents a set of all the points used in partitioning 
    set<ll> P;
    ///This represents a set of stripes in that given interval
    set<stripe> S;
}SRT;
