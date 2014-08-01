/*
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <vector>
#include <algorithm>
using namespace std;

class Solution{
public:

 // Definition for an interval.
   struct Interval {
       int start;
       int end;
       Interval() : start(0), end(0) {}
       Interval(int s, int e) : start(s), end(e) {}
   };

    //return true if val belongs to one of the intervals
    //if ture, v in intervals[idxv], otherwise v >= intervals[idxv]
    bool searchIntervals(vector<Interval> &intervals, int val, int &idxv)
    {
        int n=intervals.size();
        int idxs=0, idxe=n-1, i;
        bool found=false;

        if (n==0 || val<intervals[0].start)
        {
            idxv=-1;
            return (false);
        }
        
        while (1)
        {
            if (idxs>idxe)
            {
                break;
            }
            i=(idxs+idxe)/2;
            if (intervals[i].start>val)
            {
                idxe=i-1;
            }
            else if (intervals[i].end<val)
            {
                idxs=i+1;
                idxv=i; //mistake: keep track of the lower bound
            }
            else //val in intervals[i]
            {
                found=true;
                idxv=i;
                break;
            }
        }
        return (found);
    }
    
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval)
    {
        vector<Interval> newIntervals=intervals;
        if (intervals.size()==0)
        {
            newIntervals.push_back(newInterval);
            return(newIntervals);
        }
        
        int idx_a, idx_b;
        bool found_a, found_b;
        found_a=searchIntervals(intervals, newInterval.start, idx_a);
        found_b=searchIntervals(intervals, newInterval.end, idx_b);

        vector<Interval>::iterator itr;
        if (found_a)
        {
            newIntervals[idx_a].end=found_b ? intervals[idx_b].end : newInterval.end; //modify
        }
        else //!found_a
        {
            newInterval.end=found_b ? intervals[idx_b].end : newInterval.end; //interval to insert
            itr=newIntervals.begin();
            newIntervals.insert(itr+1+idx_a, newInterval); //insert
            idx_b++;
            idx_a++;
        }
        itr=newIntervals.begin(); //mistake: update itr to the beginning after insersion
        newIntervals.erase(itr+idx_a+1, itr+idx_b+1); //delete
        return(newIntervals);
    }

	//main test program
	void Test(void)
	{
		cout << "no test available" << endl;
	}
};

