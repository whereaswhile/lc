/*
 * note: merge from back
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
    void merge(int A[], int m, int B[], int n)
    {
        int posA=m-1, posB=n-1, pos=m+n-1;
        while(1)
        {
            if (posB==-1)
                break;
            if (posA==-1 || B[posB]>A[posA]) //move elements in B to A
            {
                A[pos]=B[posB];
                posB--;
                pos--;
            }
            else //B[posB]<=A[posA]
            {
                A[pos]=A[posA];
                posA--;
                pos--;
            }
        }
    }

	//main test program
	void Test(void)
	{
		cout << "no test available" << endl;
	}
};

