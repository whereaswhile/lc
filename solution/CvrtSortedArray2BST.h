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

// Definition for binary tree
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    TreeNode *sortedArrayItrToBST(vector<int>::iterator &it, int n)
    {
        if (n<=0) return NULL;
        
        TreeNode *l=sortedArrayItrToBST(it, n/2);
        TreeNode *t=new TreeNode(*it);
        it++;
        TreeNode *r=sortedArrayItrToBST(it, n-1-n/2);
        t->left=l;
        t->right=r;
        return t;
    }

    TreeNode *sortedArrayToBST(vector<int> &num)
    {
        vector<int>::iterator it=num.begin();
        TreeNode *t=sortedArrayItrToBST(it, num.size());
        return(t);
    }

	//main test program
	void Test(void)
	{
		cout << "No test available." << endl;
	}
};

