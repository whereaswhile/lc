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


class Solution {
public:
    int candySeg(int seg_s, int seg_e, int grad)
    {
        int l=seg_e-seg_s+1;
        if(l<=0)
        {
            return(0);
        }
        
        if (grad==0) //1 candy each
        {
            return(l);
        }
        else
        {
            return((1+l)*l/2);
        }
    }

    //peak segment
    int candyPeak(int seg_s, int seg_m, int seg_e)
    {
        int l1=seg_m-seg_s+1;
        int l2=seg_e-seg_m+1;
        assert(l1>=1);
        assert(l2>=1);
        if (l1>=l2)
        {
            return(candySeg(seg_s, seg_m, 1)+candySeg(seg_m+1, seg_e, -1));
        }
        else
        {
            return(candySeg(seg_s, seg_m-1, 1)+candySeg(seg_m, seg_e, -1));
        }
    }
    
    int candy(vector<int> &ratings)
    {
        if (ratings.size()==0)
        {
            return(0);
        }

        int grad=0, new_grad;
        int seg_s=0, seg_m=0;
        int s=0; //running sum
        for (int i=1; i<ratings.size(); i++)
        {
            new_grad=min(max(-1, ratings[i]-ratings[i-1]), 1); //-1, 0 or 1
            
            if (new_grad==0)
            {
                s+=candyPeak(seg_s, seg_m, i-1);
                seg_s=seg_m=i;
                grad=0;
            }
            else if (grad==0) //the first element
            {
                grad=new_grad;
            }
            else if (grad*new_grad==1) //save direction
            {
                //do nothing
            }
            else //grad*new_grad==-1, change direction
            {
                if (new_grad==-1) //i-1 at maximum
                {
                    seg_m=i-1;
                }
                else //new_grad==1, i-1 at minimum, begins a new peak
                {
                    s+=(candyPeak(seg_s, seg_m, i-1)-1);
                    seg_s=seg_m=i-1;
                }
                grad=new_grad;
            }
        }//end for
        
        //last segment
        if (grad==1)
        {
            seg_m=ratings.size()-1;
        }
        s+=candyPeak(seg_s, seg_m, ratings.size()-1);

        return(s);
    }

	//main test program
	void Test(void)
	{
		cout << "no test available" << endl;
	}
};

