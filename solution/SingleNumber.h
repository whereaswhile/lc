/*
 * note: double operations cancel each other
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
 
class Solution {
public:

    int singleNumber(int A[], int n)
	{
		int s=0;
		for (int i=0; i<n; i++)
		{
			s=s^A[i];
		}
		return s;
	}

	//main test program
	void Test(void)
	{
		int A[]={2, 3, 53, 2, 3, 7, 1, 1, 53};
		int n=9;
		for (int i=0; i<n; i++)
			cout << A[i] << ", ";
		cout << "\b\n";
		cout << "single: " << singleNumber(A, n) << endl;
	}
};

