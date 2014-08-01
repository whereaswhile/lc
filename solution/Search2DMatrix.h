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
    int getMatrixValue(vector<vector<int> > &matrix, int pos)
    {
        int m=matrix.size(), n=matrix[0].size();
        assert(m>0 && n>0);
        assert(pos>=0 && pos<m*n); //mistake: pos>=0!
        return(matrix[pos/n][pos%n]);
    }
    
    bool searchMatrix(vector<vector<int> > &matrix, int target)
    {
        int m=matrix.size(), n=matrix[0].size();
        assert(m>0 && n>0);
        int pos_s=0, pos_e=m*n-1, pos, val;
        while(1)
        {
            if (pos_s>pos_e)
                return false;
            pos=(pos_s+pos_e)/2;
            val=getMatrixValue(matrix, pos);
            if (val==target)
                return true;
            else if (val>target)
            {
                pos_e=pos-1;
            }
            else //val<target
            {
                pos_s=pos+1;
            }
        }
    }

	//main test program
	void Test(void)
	{
		cout << "test not available!" << endl;
	}
};

