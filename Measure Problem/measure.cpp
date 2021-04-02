#include "measure_structures.hpp"
#include "measure_primary.hpp"
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


/*! Finding the measure of the iso oriented rectangles from the given input file
    \param S Set of stripes
    \return Value of measure based on the given parameter - set of stripes
*/
ll measure(set<stripe> S)
{
    ll ans = 0;
    auto itr = S.begin();
    while(itr!=S.end())
    {
        stripe s1 = (*itr);
        ans += ((s1.x_union) * (s1.y_int.top - s1.y_int.bottom));
        ++itr;
    }
    return ans;
}
