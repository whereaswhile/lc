/*
 * note: r^2<=x<(r+1)^2
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

    int sqrt(int x)
    {
        assert(x>=0);
        if (x<=1)
        {
            return(x);
        }
        
        int s=1, e=x, r, d1, d2;
        while (s<=e)
        {
            r=(s+e)/2;
            //r2=r*r; //mistake: r*r may overflow!
            d1=x/r;
            d2=x/(r+1);
            if (d1<r)
            {
                e=r-1;
            }
            else if (d2>=(r+1))
            {
                s=r+1;
            }
            else
            {
                break;
            }
        }//end while
        return (r);
    }

	//main test program
	void Test(void)
	{
		int x=2147395599;
		cout << "sqrt of " << x << " is: " << sqrt(x) << endl;
	}
};

