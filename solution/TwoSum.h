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
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        //sort
        vector<int> numsort=numbers;
        sort(numsort.begin(), numsort.end());

        //find number
        vector<int> v(2);
        int idxs=0, idxe=numsort.size()-1;
        while (1)
        {
            if (idxs==idxe) //not found
                break;
            if (numsort[idxs]+numsort[idxe]==target)
            {
                v[0]=numsort[idxs];
                v[1]=numsort[idxe];
                break;
            }
            else if (numsort[idxs]+numsort[idxe]>target)
            {
                idxe--;
            }
            else //if (numsort[idxs]+numsort[idxe]<target)
            {
                idxs++;
            }
        }//end while
        numsort.clear();
        
        //search index
        vector<int> u;
        u.clear();
        for (int i=0; i<numbers.size(); i++)
        {
            if (numbers[i]==v[0] || numbers[i]==v[1])
            {
                u.push_back(i+1);
            }
        }
        return(u);
    }

	//main test program
	void Test(void)
	{
		cout << "no test available" << endl;
	}
};

