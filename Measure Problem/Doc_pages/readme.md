@mainpage ReadMe

The Measure Problem
Given a set of n iso-oriented rectangles in the plane, determine the measure of
their union.
In other words we ask for the size of the covered area of the plane.

This HTML provides the documentation for code submitted to calculate measure of iso-oriented rectangles

Submitted By;


Anirudh Sood


Danish Mohammed


Utkarsh Jha





@section subsection Timing Analysis:

Function/Part of Code


Difference/Union/Intersection=θ(nlogn)


Blacken/Copy=O(n^2)


Concat=θ(nlogn)


Divide Step=2T(n/2)


Merge Step=O(n^2)


Base Case=θ(nlogn)


In worst case:
T(n)=2T(n/2)+c n^2


So, T(n)=θ(n^2)