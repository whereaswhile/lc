/*
 * note: recursion and stack
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:

    int maxDepth(TreeNode *root)
    {
        //recursion
/*      if(root==NULL)
            return 0;
        else
            return(1+max(maxDepth(root->left), maxDepth(root->right)));
*/

        vector<pair<TreeNode *, int> > stk;
        stk.clear();
        pair<TreeNode *, int> p(root, 0);
        int l=0;
        while(1)
        {
            if(p.first==NULL || p.second==2) //up from leaf or right
            {
                if (stk.size()==0) break;
                p=stk.back();
                stk.pop_back();
                p.second+=1;
            }
            else if (p.second==1) //up from left, now to right
            {
                stk.push_back(p);
                l=max((int)stk.size(), l);
                p=make_pair(p.first->right, 0);
            }
            else //going down
            {
                stk.push_back(p);
                l=max((int)stk.size(), l);
                p=make_pair(p.first->left, 0);
            }
        }//end while
        return(l);
    }

	//main test program
	void Test(void)
	{
		cout << "no test available" << endl;
	}
};

