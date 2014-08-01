/*
 * note: recursion and series
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
    int climbStairs(int n)
    {
        assert(n>0);
        if (n<=2)
            return n;

        int a1=1, a2=2, a3;
        for (int i=3; i<=n; i++)
        {
            a3=a2+a1;
            a1=a2;
            a2=a3;
        }
        return(a3);
    }

	//main test program
	void Test(void)
	{
		cout << "no test available" << endl;
	}
};

