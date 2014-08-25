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

class Solution
{
public:
    void rotate(vector<vector<int> > &matrix)
    {
        int n=matrix.size();
        for (int i=0; i<n/2; i++)
        {
            for (int j=0; j<(n+1)/2; j++)
            {
                int tmp=matrix[j][n-1-i];
                matrix[j][n-1-i]=matrix[i][j];
                matrix[i][j]=matrix[n-1-j][i];
                matrix[n-1-j][i]=matrix[n-1-i][n-1-j];
                matrix[n-1-i][n-1-j]=tmp;
            }
        }
    }

	//main test program
	void Test(void)
	{
		cout << "No test available." << endl;
	}
};

