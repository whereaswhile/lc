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
    int minPathSum(vector<vector<int> > &grid)
    {
        vector<vector<int> > dist; //mistake: space between "> >"
		dist=grid;
        int m=grid.size();
        int n=grid[0].size();
        for (int i=m-1; i>=0; i--)
        {
        for (int j=n-1; j>=0; j--)
        {
            if (i==m-1 && j==n-1)
            {
                dist[i][j]=grid[i][j];
            }
            else if (i==m-1)
            {
                dist[i][j]=grid[i][j]+dist[i][j+1];
            }
            else if (j==n-1)
            {
                dist[i][j]=grid[i][j]+dist[i+1][j];
            }
            else
            {
                dist[i][j]=grid[i][j]+min(dist[i+1][j], dist[i][j+1]);
            }
        }//end j
        }//end i
        return (dist[0][0]);
    }

	//main test program
	void Test(void)
	{
		cout << "no test available" << endl;
	}
};

