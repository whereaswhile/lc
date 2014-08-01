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

class Solution {
public:

/*
    void preorderRecTraversal(TreeNode *root, vector<int> &values)
    {
        if (root==NULL)
        {
            return;
        }
        
        values.push_back(root->val);
        preorderRecTraversal(root->left, values);
        preorderRecTraversal(root->right, values);
    }
    
    //recursive
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> values;
        values.clear();
        preorderRecTraversal(root, values);
        return values;
    }
*/

    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> values;
        vector<TreeNode *> path;
        vector<int> status; //0: init; 1: left done; 2: right done
        TreeNode *curr_node;
        int curr_stat;
        values.clear();
        path.clear();
        status.clear();

        if (root==NULL)
        {
            return values;
        }
        
        curr_node=root;
        curr_stat=0;
        while (1)
        {
            if (curr_node==NULL)
            {
                curr_node=path.back();
                path.pop_back();
                curr_stat=status.back()+1;
                status.pop_back();
                continue;
            }
            
            //curr_node!=NULL
            if (curr_stat==0)
            {
                values.push_back(curr_node->val);
                path.push_back(curr_node);
                status.push_back(curr_stat);
                curr_node=curr_node->left;
                curr_stat=0;
            }
            else if (curr_stat==1)
            {
                path.push_back(curr_node);
                status.push_back(curr_stat);
                curr_node=curr_node->right;
                curr_stat=0;
            }
            else //if (curr_stat==2)
            {
                //this node is done, move up
                if (path.size()==0) //curr_node==root, done
                {
                    break;
                }
                curr_node=path.back();
                path.pop_back();
                curr_stat=status.back()+1;
                status.pop_back();
            }
        }
        return values;
    }


	//main test program
	void Test(void)
	{
		cout << "no test available" << endl;
	}
};

