#include "measure_structures.hpp"
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

/// \fn findFrame
///    Function that helps find the bounding frame around the given set of iso-rectangles
///    \brief Finds bounding frame around set of rectangles
///    \return returns a rectangle structure containing information about the boundaries of the frame
///
rectangle findFrame(vector<rectangle> iso_rectangles_input)
{
    rectangle frame;
    ll minY=INT_MAX;
    ll minX=INT_MAX;
    ll maxY = INT_MIN;
    ll maxX = INT_MIN;
    for(ll i=0;i<iso_rectangles_input.size();i++)
    {
        rectangle r = iso_rectangles_input[i];
        if(r.x_int.bottom <= minX)
        {
            minX = r.x_int.bottom ;
        }
        if(r.x_int.top >= maxX)
        {
            maxX = r.x_int.top;
        }
        if(r.y_int.top >= maxY)
        {
            maxY = r.y_int.top;
        }
        if(r.y_int.bottom <= minY)
        {
            minY = r.y_int.bottom;
        }
    }
    interval x_bound;
    interval y_bound;
    x_bound.bottom = minX-2; x_bound.top = maxX+2;
    y_bound.bottom = minY-2; y_bound.top = maxY+2;
    frame.x_int = x_bound; frame.y_int = y_bound;
    return frame;
}

/*! Creates continuous intervals for a given set of points along Y axis
    \param y_coordinates a set of integers representing the coordinate points for partitioning
    \return Set of intervals representing the partition induced by y coordinates 
*/  
set<interval> y_partition(set<ll> y_coordinates)
{
    priority_queue <ll, vector<ll>, greater<ll>> partition_maker;
    set<interval> plane_partitions;
    set<ll>::iterator it = y_coordinates.begin();
    while(it != y_coordinates.end())
    {
        partition_maker.push(*it);
        ++it;
    }
    interval inter;
    ll prev = partition_maker.top();
    partition_maker.pop();
    while(!partition_maker.empty())
    {
        inter.bottom = prev;
        inter.top = partition_maker.top();
        prev = partition_maker.top();
        plane_partitions.insert(inter);
        partition_maker.pop();
    }
    return plane_partitions;
}

/*! Creates continuous intervals for a given set of points along Y axis
    \return Set of integers representing the unique y coordinates of vertices of the input iso rectangles
*/  
set<ll> y_set(vector<rectangle> iso_rectangles_input)
{
    set<ll> y_coordinates;
    for(ll i=0;i<iso_rectangles_input.size();i++)
    {
        y_coordinates.insert(iso_rectangles_input[i].y_int.bottom);
        y_coordinates.insert(iso_rectangles_input[i].y_int.top);
    }
    return y_coordinates;
}

/*! Gets the intersection of two sets of intervals
    \param i1 defines a set of intervals
    \param i2 defines a set of intervals
    \return A set of intervals which contain those intervals in i1 and i2 which have the same minimum and maximum values
*/
set<interval> set_intersection(set<interval> i1, set<interval> i2)
{
    auto ite = i1.begin();
    auto itr = i2.begin();
    set<interval> i3;
    while(ite!=i1.end() and itr!=i2.end())
    {
        interval a = *ite;
        interval b = *itr;

        if(a.bottom < b.bottom)
        {
            ite++;
        }
        else if(a.bottom == b.bottom)
        {
            if(a.top == b.top)
            {
                i3.insert(a);
                ite++;
                itr++;
            }
            else if(a.top < b.top)
            {
                ite++;
            }
            else
            {
                itr++;
            }
        }
        else
        {
            itr++;
        }
    }
    return i3;
}

/*! Gets the difference of two sets of intervals
    \param i1 defines a set of intervals
    \param i2 defines a set of intervals
    \return Set of intervals in i1 that do not belong to i2
*/
set<interval> set_difference(set<interval> i1,set<interval> i2)
{
    auto ite = i1.begin();
    auto itr = i2.begin();
    set<interval> i3;
    while(ite!=i1.end() and itr!=i2.end())
    {
        interval a = *ite;
        interval b = *itr;

        if(a.bottom < b.bottom)
        {
            i3.insert(a);
            ite++;
        }
        else if(a.bottom == b.bottom)
        {
            if(a.top == b.top)
            {
                ite++;
                itr++;
            }
            else if(a.top < b.top)
            {
                i3.insert(a);
                ite++;
            }
            else
            {
                itr++;
            }
        }
        else
        {
            itr++;
        }
    }

    while(ite != i1.end())
    {
        i3.insert((*ite));
        ite++;
    }

    return i3;
}
/*! Gets the union of two sets of intervals
    \param i1 defines a set of intervals
    \param i2 defines a set of intervals
    \return Set of unique intervals belonging to i1 or i2
*/
set<interval> set_union(set<interval> i1, set<interval> i2)
{
    set<interval> i3;
    auto ite = i1.begin();
    auto itr = i2.begin();
    while(ite != i1.end())
    {
        i3.insert(*ite);
        ++ite;
    }
    while(itr != i2.end())
    {
        i3.insert(*itr);
        ++itr;
    }
    return i3;
}
/*! Adds additional stripes to the existing set of stripes S based on the intervals induced by partition of P
    \param S defines a set of existing stripes
    \param P defines a set of partition points
    \param x_ext depicts the width of the stripe
    \return Updated set of stripes containing the additional stripes induced by partition of P
*/
set<stripe> copy(set<stripe> S, set<ll> P, interval x_ext)
{
    set<interval> part = y_partition(P);
    auto ite = part.begin();
    auto itr = S.begin();
    set<stripe> s1;
    while(ite != part.end())
    {
        stripe stemp;
        stemp.x_int = x_ext;
        stemp.y_int = *ite;
        stemp.x_union = 0;
        
        while(itr!= S.end())
        {
            interval c = (*itr).y_int; //S
            if(stemp.y_int.bottom >= c.bottom)
            {
                if(stemp.y_int.top <= c.top)
                {
                    //useful S
                    stemp.x_union = (*itr).x_union;
                    break;
                }
                else
                {
                    itr++;
                }
            }
            else
            {
                break;
            }
        }

        s1.insert(stemp);
        ++ite;
    }

    return s1;

}
/*! Updates the x_union values for the stripes that have not found a partner edge in S
    \param S defines a set of existing stripes
    \param J defines the set of intervals which do not have a matching edge in S
    \return Modified set of stripes with updated x_union values
*/
set<stripe> blacken(set<stripe> S, set<interval> J)
{
    auto itr = S.begin();
    auto ite = J.begin();
    set<stripe> s_final;
    while(itr != S.end())
    {
        stripe stemp = *itr;
        interval i1 = stemp.y_int;
        while(ite != J.end())
        {
            //i1 should be subset of i2
            interval i2 = (*ite);
            if(i1.bottom < i2.bottom)
            {
                break;
            }
            else if(i1.bottom == i2.bottom)
            {
                if(i1.top <= i2.top)
                {
                    stemp.x_union = stemp.x_int.top - stemp.x_int.bottom;
                    break;
                }
                else
                {
                    ite++;
                }
            }
            else
            {
                if(i1.top <= i2.top)
                {
                    stemp.x_union = stemp.x_int.top - stemp.x_int.bottom;
                    break;
                }
                else
                {
                    ite++;
                }
            }
        }
        s_final.insert(stemp);
        ++itr;
    }

    return s_final;
}
/*! Combines stripes located across the median line
    \param s_left defines a set of stripes on the left side of the median line
    \param s_right defines a set of stripes on the right side of the median line
    \param P defines a set of partition points
    \param x_ext depicts the width of the stripe
    \return Updated set of stripes formed using s_left and s_right after dissolving the median line 
*/
set<stripe> concat(set<stripe> s_left, set<stripe> s_right, set<ll> P, interval x_ext)
{
    set<interval> part = y_partition(P);
    auto ite = part.begin();
    auto itr1 = s_left.begin();
    auto itr2 = s_right.begin();
    set<stripe> S;

    while(ite != part.end())
    {
        stripe stemp;
        stemp.x_int = x_ext;
        stemp.y_int = *ite;
        stemp.x_union = 0;
        ll val1 = (*itr1).x_union;
        ll val2 = (*itr2).x_union;
        stemp.x_union = val1+val2;
        itr1++; 
        itr2++;
        S.insert(stemp);
        ++ite;
    }

    return S;
}
/*! Divde and conquer algorithm that computes the set of stripes along with their x_union values for the given set of vertical edges
    \param VRX defines a set of stripes on the left side of the median line
    \param x_ext depicts the width of the frame
    \param ylimits represents the height of the frame
    \return Intermediary results required for producing the result of the previous call (comprising of interval L, interval R, set of coordinates P and set of stripes S)
*/
SRT stripes(set<edge> VRX, interval x_ext, interval ylimits)
{
    SRT temp;
    set<interval> l,r;
    set<ll> p;
    set<stripe> s;
    
    if(VRX.size()==1)
    {
        auto it = VRX.begin();
        edge e = *it;
        if(e.edgetype == "LEFT")
        {
            interval l1 = e.i;
            l.insert(l1);
        }
        else
        {
            interval r1 = e.i;
            r.insert(r1);    
        }

        p.insert(ylimits.bottom);
        p.insert(e.i.bottom);
        p.insert(e.i.top);
        p.insert(ylimits.top);

        set<interval> part = y_partition(p);
        auto ite = part.begin();
        while(ite != part.end())
        {
            stripe stemp;
            stemp.x_int = x_ext;
            stemp.y_int = *ite;
            stemp.x_union = 0;
            if((stemp.y_int.bottom == e.i.bottom) and (stemp.y_int.top == e.i.top))
            {
                if(e.edgetype == "LEFT")
                {
                    stemp.x_union = x_ext.top - e.x;
                }
                else
                {
                    stemp.x_union = e.x - x_ext.bottom;
                }
            }

            s.insert(stemp);
            ++ite;
        }
    }
    else
    {
        ll n = VRX.size();
        ll xm = 0;
        set<edge> v1,v2;
        auto it = VRX.begin();
        for(ll i=0;i<n/2;i++)
        {
            v1.insert(*it);
            xm += (*it).x;
            ++it;
        }
        for(ll i=n/2;i<n;i++)
        {
            if(i==n/2)
            {
                xm += (*it).x;
            }
            v2.insert(*it);
            ++it;
        }
        xm = xm / n;
        
        SRT left,right;
        interval left_call,right_call;
        left_call.bottom = x_ext.bottom;
        left_call.top = xm;
        right_call.bottom = xm;
        right_call.top = x_ext.top;

        left = stripes(v1, left_call,ylimits);
        right = stripes(v2,right_call,ylimits);
        
        //Merge step to be writen
        set<interval> L1=left.L;
        set<interval> R2=right.R;
        
        set<interval> LR;
        
        LR = set_intersection(L1,R2);
        set<interval> l1lr = set_difference(L1,LR);
        set<interval> r2lr = set_difference(R2,LR);
        l = set_union(right.L,l1lr);
        r = set_union(left.R,r2lr);
        
        for(auto a: l)
        {
        	 //cout << "xm = " << xm << endl;
        	 //cout << "left " << a.bottom << " " << a.top << endl;
        }
        for(auto a: r)
        {
        	 //cout << "xm = " << xm << endl;
        	 //cout << "right " << a.bottom << " " << a.top << endl;
        }
      
        

        set<ll> P1= left.P;
        set<ll> P2= right.P;
        auto itr=P1.begin();
        while(itr!=P1.end())
        {
            p.insert(*itr);
            itr++;
        }
        itr=P2.begin();
        while(itr!=P2.end())
        {
            p.insert(*itr);
            itr++;
        }


        set<stripe> S_left,S_right;
        interval slefttemp;
        slefttemp.bottom=x_ext.bottom;
        slefttemp.top=xm;
        interval srighttemp;
        srighttemp.bottom=xm;
        srighttemp.top=x_ext.top;
        S_left=copy(left.S,p,slefttemp);
        S_right=copy(right.S,p,srighttemp);
        

        S_left = blacken(S_left,r2lr);
        S_right = blacken(S_right,l1lr);
        

        s = concat(S_left, S_right, p, x_ext);

    }
    
    temp.L = l;
    temp.R = r;
    temp.P = p;
    temp.S = s;
    
    return temp;
}
/*! Driver function used to call the divide and conquer algorithm stripes when provided with a set of iso-oriented rectangles
    \param rect defines the collection of iso oriented rectangles input by the users
    \return Final set of stripes computed by the stripes algorithm
*/
set<stripe> rectangle_DAC(vector<rectangle> rect)
{
    vector<rectangle>::iterator it = rect.begin();
    set<edge> VRX;
    while(it != rect.end())
    {
        edge e1;
        e1.edgetype = "LEFT";
        e1.i = (*it).y_int;
        e1.x =  (*it).x_int.bottom;

        edge e2;
        e2.edgetype = "RIGHT";
        e2.i = (*it).y_int;
        e2.x =  (*it).x_int.top;

        VRX.insert(e1);
        VRX.insert(e2);
        it++;
    }
    set<interval> L,R;
    set<ll> P;
    interval ylimits;
    rectangle frame = findFrame(rect);
    ylimits.bottom = frame.y_int.bottom;
    ylimits.top = frame.y_int.top;
    interval xlimits;
    xlimits.bottom = frame.x_int.bottom;
    xlimits.top = frame.x_int.top;
    SRT srt;
    srt = stripes(VRX,xlimits, ylimits);
    return srt.S;
    // set<edge>::iterator ite = VRX.begin();
    // while(ite != VRX.end())
    // {
    //     cout<<(*ite).x<<" "<<(*ite).edgetype<<endl;
    //     ite++;
    // }
}
