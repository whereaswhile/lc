/*
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;
 
class Solution {
public:
    int singleNumber(int A[], int n)
    {
        int r1=0, r2=0, tmp;
        for (int i=0; i<n; i++)
        {
            //r1=(r1 & ~A[i])|(r2 & 0)|(~r1&~r2 & A[i]);
            //r2=(r1 & A[i])|(r2 & ~A[i])|(~r1&~r2 & 0);
            tmp=(r1 & A[i])|(r2 & ~A[i]); //mistake: keep old values of r1 and r2
            r1=(r1 & ~A[i])|(~r1 & ~r2 & A[i]); //mistake: condition in the last | cannot be omitted
            r2=tmp;
        }
        assert(r2==0);
        return r1;
    }

	//main test program
	void Test(void)
	{
		int A[]={2, 3, 53, 2, 3, 7, 3, 2, 53, 53};
		int n=10;
		for (int i=0; i<n; i++)
			cout << A[i] << ", ";
		cout << "\b\n";
		cout << "single: " << singleNumber(A, n) << endl;
	}
};

