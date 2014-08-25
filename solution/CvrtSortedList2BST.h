/*
 * note: two passes of list
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <vector>
#include <algorithm>
using namespace std;

//Definition for singly-linked list.
struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};

// Definition for binary tree
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode *sortedListNToBST(ListNode *&head, int n)
    {
        if (n<=0) return NULL;
        
        TreeNode *l, *r, *t;
        l=sortedListNToBST(head, n/2);
        t=new TreeNode(head->val);
        head=head->next;
        r=sortedListNToBST(head, n-n/2-1);
        t->left=l;
        t->right=r;
        return t;
    }
    
    TreeNode *sortedListToBST(ListNode *head)
    {
        int n=0;
        ListNode *tmp=head;
        while (tmp!=NULL)
        {
            tmp=tmp->next;
            n++;
        }
        
        TreeNode *tree;
        tree=sortedListNToBST(head, n);
        return(tree);
    }

	//main test program
	void Test(void)
	{
		cout << "No test available." << endl;
	}
};

