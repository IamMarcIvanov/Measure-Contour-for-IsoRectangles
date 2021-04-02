#include "c_structures.hpp"
#include "c_primary.hpp"
#include<bits/stdc++.h>
using namespace std;

/*! Adds additional stripes to the existing set of stripes S based on the intervals induced by partition of P
    \param S defines a set of existing stripes
    \param P defines a set of partition points
    \param x_ext depicts the width of the stripe
    \return Updated set of stripes containing the additional stripes induced by partition of P
*/
 set<ContourStripe> contourCopy(set<ContourStripe> S, set<float> P, Interval x_int)
{
    set<ContourStripe> ans;
    set<Interval> partitions = planePartition(P);
    for(auto& part : partitions)
    {
        ContourStripe stripe{x_int, part, 0};
        for(auto& s : S)
        {
            if(part.bottom >= s.y_interval.bottom)
            {
                if(part.top <= s.y_interval.top)
                {
                    stripe.tree = s.tree;
                    break;
                }
            }
            else
            {
                break;
            }
        }
        ans.insert(stripe);
    }
    return ans;
}
/*! Updates the x_union values for the stripes that have not found a partner edge in S
    \param S defines a set of existing stripes
    \param J defines the set of intervals which do not have a matching edge in S
    \return Modified set of stripes with updated trees in stripes
*/
set<ContourStripe> contourBlacken(set<ContourStripe> S, set<Interval> J)
{
    set<ContourStripe> ans;
    for(auto& s : S)
    {
        ContourStripe stripe;
        stripe.x_interval = s.x_interval;
        stripe.y_interval = s.y_interval;
        bool updated = false;
        for(auto& i : J)
        {
            if (s.y_interval.bottom >= i.bottom)
            {
                if (s.y_interval.top <= i.top)
                {
                    Ctree* holder = (Ctree*)malloc(sizeof(Ctree));
                    stripe.tree = holder;
                    stripe.tree->lson = 0;
                    stripe.tree->rson = 0;
                    stripe.tree->side = U;
                    updated = true;
                }
            }
            else
            {
                break;
            }
        }
        if(!updated)
        {
            stripe.tree = s.tree;
        }
        ans.insert(stripe);
    }
    return ans;
}
/*! Combines stripes located across the median line
    \param s_left defines a set of stripes on the left side of the median line
    \param s_right defines a set of stripes on the right side of the median line
    \param P defines a set of partition points
    \param x_ext depicts the width of the stripe
    \return Updated set of stripes formed using s_left and s_right after dissolving the median line 
*/
set<ContourStripe> contourConcat(set<ContourStripe> S1, set<ContourStripe> S2, set<float> P, Interval x_int)
{
    set<ContourStripe> ans;
    set<Interval> partitions = planePartition(P);
    auto f = S1.begin();
    auto s = S2.begin();
    for (auto& part : partitions)
    {
        ContourStripe stripe;
        stripe.x_interval = x_int;
        stripe.y_interval = part;
        Ctree* a = (Ctree*)malloc(sizeof(Ctree));
        if ((*((*f).tree) == Ctree{}) and (*((*s).tree) == Ctree{}))
        {
            stripe.tree = a;
            stripe.tree->lson = 0;
            stripe.tree->rson = 0;
            stripe.tree->side = U;
        }
        else if (*((*f).tree) == Ctree{})
        {
            stripe.tree = (*s).tree;
        }
        else if (*((*s).tree) == Ctree{})
        {
            stripe.tree = (*f).tree;
        }
        else
        {
            Ctree* value = (Ctree*)malloc(sizeof(Ctree));
            value->x = (*f).x_interval.top;
            value->side = U;
            value->lson = (*f).tree;
            value->rson = (*s).tree;
            stripe.tree = value;
        }
        ans.insert(stripe);
        f++;
        s++;
    }
    return ans;
}
/*! this function gives the contour base case final
    \param intermediate is the common stripe output
    \param e represents the edge of the rectangle
    \param x_ext is the x extension of the stripe
    \return the final contour base case
*/
 ContourStripeOutput contourBaseCaseFinal(CommonStripeOutput intermediate, Edge e, Interval x_ext)
{
    set<Interval> partitions = planePartition(intermediate.P);
    set<ContourStripe> S;
    for(auto& part : partitions)
    {
        ContourStripe stripe;
        stripe.x_interval = x_ext;
        stripe.y_interval = part;
        Ctree* a = (Ctree*)malloc(sizeof(Ctree));
        stripe.tree = a;
        stripe.tree->lson = 0;
        stripe.tree->rson = 0;
        stripe.tree->side = U;
        if((e.span.bottom == part.bottom) and (e.span.top == part.top))
        {
            if(e.side == LEFT)
            {
                stripe.tree->x = e.coord;
                stripe.tree->side = L;
            }
            else
            {
                stripe.tree->x = e.coord;
                stripe.tree->side = R;
            }
        }
        S.insert(stripe);
    }
    return ContourStripeOutput{intermediate, S};
}
/*! this function gives the contour base case final
    \param intermediate is the common merge output
    \param conquer_output represents the output of the conquer in the base case
    \param x_ext is the x extension of the stripe
    \param xm represents the average line of the x_interval
    \return the final set of stripes for the contour 
*/
set<ContourStripe> contourFinal(CommonMergeOutput intermediate, pair<ContourStripeOutput, ContourStripeOutput> conquer_output, Interval x_ext, float x_m)
{
    set<ContourStripe> S_left = contourCopy(conquer_output.first.S, intermediate.CSO.P, Interval{x_ext.bottom, x_m});
    set<ContourStripe> S_right = contourCopy(conquer_output.second.S, intermediate.CSO.P, Interval{x_m, x_ext.top});
    S_left = contourBlacken(S_left, intermediate.R2LR);
    S_right = contourBlacken(S_right, intermediate.L1LR);
    set<ContourStripe> S = contourConcat(S_left, S_right, intermediate.CSO.P, x_ext);
    return S;
}
/*! Divde and conquer algorithm that computes the set of stripes along with their x_union values for the given set of vertical edges
    \param VRX defines a set of stripes on the left side of the median line
    \param x_ext depicts the width of the frame
    \param ylimits represents the height of the frame
    \return Intermediary results required for producing the result of the previous call (comprising of interval L, interval R, set of coordinates P and set of stripes S)
*/
ContourStripeOutput contourStripes(set<Edge> V, Interval x_ext)
{
    if (V.size() == 1)
    {
        auto e = V.begin();
        CommonStripeOutput intermediate = baseCaseLRP(*e);
        return contourBaseCaseFinal(intermediate, *e, x_ext);
    }
    tuple<set<Edge>, set<Edge>, float> divide_output = divide(V);
    ContourStripeOutput left_result = contourStripes(get<0>(divide_output), Interval{x_ext.bottom, get<2>(divide_output)});
    ContourStripeOutput right_result = contourStripes(get<1>(divide_output), Interval{get<2>(divide_output), x_ext.top});
    pair<ContourStripeOutput, ContourStripeOutput> conquer_output;
    conquer_output.first = left_result;
    conquer_output.second = right_result;
    pair<CommonStripeOutput, CommonStripeOutput> conquer_output_lrp;
    conquer_output_lrp.first = left_result.CSO;
    conquer_output_lrp.second = right_result.CSO;
    CommonMergeOutput intermediate = mergeLRP(conquer_output_lrp);
    set<ContourStripe> S = contourFinal(intermediate, conquer_output, x_ext, get<2>(divide_output));
    return ContourStripeOutput{intermediate.CSO, S};
}
/*! Driver function used to call the divide and conquer algorithm stripes when provided with a set of iso-oriented rectangles
    \param rect defines the collection of iso oriented rectangles input by the users
    \return Final set of stripes computed by the stripes algorithm
*/
set<ContourStripe> contourRectangleDAC(vector<Rectangle> rectangles)
{
    set<Edge> V = getVerticalEdges(rectangles);
    ContourStripeOutput output = contourStripes(V, Interval{-FLT_MAX, FLT_MAX});
    return output.S;
}
/*! this function gives leafnodes of the tree
    \param root defines the tree structure we want leaf nodes of
    \return gives the leaf nodes of the given 
*/
vector<Ctree*> getLeafNodes(Ctree* root)
{
    vector<Ctree*> leaf_nodes;
    if (!root)
    {
        return leaf_nodes;
    }
    if (!root->lson && !root->rson)
    {
        leaf_nodes.push_back(root);
        return leaf_nodes;
    }
    if (root->lson)
    {
        vector<Ctree*> left_nodes = getLeafNodes(root->lson);
        leaf_nodes.insert(leaf_nodes.end(), left_nodes.begin(), left_nodes.end());

    }
    if (root->rson)
    {
        vector<Ctree*> right_nodes = getLeafNodes(root->rson);
        leaf_nodes.insert(leaf_nodes.end(), right_nodes.begin(), right_nodes.end());
    }
    return leaf_nodes;
}
/*! this function gives contour pieces of the given stripe
    \param edge represents the edge of the rectangle 
    \param s is the contour stripe for which we get the contour peices
    \return set of contour pieces computed by the algorithm
*/
set<ContourPiece> getContourPieces(Edge h, ContourStripe s)
{
    set<ContourPiece> contour_pieces;
    vector<Ctree*> leaf_nodes = getLeafNodes(s.tree);
    float x1 = h.span.bottom;
    float x2 = h.span.top;
    float prev_val = -FLT_MAX;
    for (auto& node : leaf_nodes)
    {
        if (node->x <= x1)
        {
            if (node->side == L or node->side == R)
            {
                prev_val = node->x;
            }
        }
        else if (node->x < x2)
        {
            if (node->side == L)
            {
                ContourPiece piece{fmax(x1, prev_val), node->x, h.coord};
                contour_pieces.insert(piece);
                prev_val = node->x;
            }
            else if (node->side == R)
            {
                prev_val = node->x;
            }
        }
        else
        {
            if (node->side == L)
            {
                if (prev_val < x2)
                {
                    ContourPiece piece{fmax(x1, prev_val), x2, h.coord};
                    contour_pieces.insert(piece);
                    prev_val = node->x;
                }
            }
            else if (node->side == R)
            {
                prev_val = node->x;
            }
        }
    }
    if (prev_val < x2)
    {
        ContourPiece piece{fmax(x1, prev_val), x2, h.coord};
        contour_pieces.insert(piece);
    }
    return contour_pieces;
}
/*! this function gives contour
    \param rectangles represents the rectangle 
    \param s set of contour peices computed that make the contour
    \return Final set of contour pieces computed by the algorithm
*/
set<ContourPiece> getContour(vector<Rectangle> rectangles, set<ContourStripe> S)
{
    set<Edge> H = getHorizontalEdges(rectangles);
    set<ContourPiece> contour_pieces;
    for (auto& h : H)
    {
        if (h.side == BOTTOM)
        {
            for (auto& s : S)
            {
                if (s.y_interval.top == h.coord)
                {
                    set<ContourPiece> pieces = getContourPieces(h, s);
                    contour_pieces.insert(pieces.begin(), pieces.end());
                    break;
                }
            }
        }
        if (h.side == TOP)
        {
            for (auto& s : S)
            {
                if (s.y_interval.bottom == h.coord)
                {
                    set<ContourPiece> pieces = getContourPieces(h, s);
                    contour_pieces.insert(pieces.begin(), pieces.end());
                    break;
                }
            }
        }
    }
    return contour_pieces;
}
/*! this function gives contour
    \param str is the string that is to be splitted
    \param delim is the delimiter that is used to split the string 
    \return a vector string after the split
*/
vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

