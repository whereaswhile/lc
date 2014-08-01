/*
 * note: tree can be unbalanced
 * note: negative weights need considered
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

class Solution {
public:
 // Definition for binary tree
   struct TreeNode {
       int val;
       TreeNode *left;
       TreeNode *right;
       TreeNode(int x) : val(x), left(NULL), right(NULL) {}
   };

    bool isLeafNode(const TreeNode *root)
    {
        assert(root!=NULL);
        return(root->left==NULL && root->right==NULL);
    }

    //root_sum: max-weighted path with root node as an end
    //s: max-weighted path
    //s_root: max-weighted path containing root node
    //s>=s_root>=root_sum
    int maxPathSumRec(TreeNode *root, int &root_sum)
    {
        if(root==NULL)
        {
            root_sum=0;
            return 0;
        }
        if (isLeafNode(root))
        {
            root_sum=root->val;
            return root->val;
            //return max(0, root->val); //empty path for negative node
        }

        //has subtrees
        int s_l, s_r, p_l, p_r, s, s_root;
        s_l=maxPathSumRec(root->left, p_l);
        s_r=maxPathSumRec(root->right, p_r);
        root_sum=root->val+max(0, max(p_l, p_r));
        s_root=root->val;
        s_root+=max(0, p_l);
        s_root+=max(0, p_r);
        s=s_root;
        if (root->left!=NULL) //mistake: empty child cannot be represented by 0
            s=max(s, s_l);
        if (root->right!=NULL)
            s=max(s, s_r);
        return(s);
    }

    int maxPathSum(TreeNode *root)
    {
        int s, root_sum;
        s=maxPathSumRec(root, root_sum);
        return s;
    }

	//main test program
	void Test(void)
	{
		cout << "no test available!" << endl;
	}
};

