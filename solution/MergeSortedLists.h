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

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:

	void printList(ListNode *l)
	{
		while (l!=NULL)
		{
			cout << l->val << ", ";
		}
		cout << endl;
	}

    void pushHeap(vector<ListNode *> &minhp, ListNode *nd)
    {
        minhp.push_back(nd);
        int pos=minhp.size()-1, parpos;
        ListNode *tmp;
        while (1)
        {
            if (pos==0) break;
            parpos=(pos+1)/2-1;
            if (minhp[pos]->val >= minhp[parpos]->val) break;
            //swap
            tmp=minhp[pos];
            minhp[pos]=minhp[parpos];
            minhp[parpos]=tmp;
            pos=parpos;
        }
    }
    
    ListNode *popHeap(vector<ListNode *> &minhp)
    {
        ListNode *min_nd=minhp[0], *tmp;
        minhp[0]=minhp.back();
        minhp.pop_back();
        int pos=0, pos1, pos2;

        while(1)
        {
            pos1=pos*2+1;
            pos2=pos1+1;
            if (pos1>=int(minhp.size()))
				break;
            if (pos2<int(minhp.size()) && minhp[pos2]->val<minhp[pos1]->val)
                pos1=pos2;
            if (minhp[pos1]->val >= minhp[pos]->val)
				break;
            //swap
            tmp=minhp[pos];
            minhp[pos]=minhp[pos1];
            minhp[pos1]=tmp;
            pos=pos1;
        }
        
        return(min_nd);
    }
    

/*    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        vector<ListNode *> cur_pos=lists;
        ListNode *outlist=NULL, *out_pos=NULL;
        for (int i=cur_pos.size()-1; i>=0; i--)
		{
			if (cur_pos[i]==NULL)
				cur_pos.erase(cur_pos.begin()+i); //mistake: remove initial NULL list
		}

        while(1)
        {
            if (int(cur_pos.size())==0)
            {
                break;
            }
                
            int vmin=cur_pos[0]->val, imin=0;
            for (int i=1; i<cur_pos.size(); i++)
            {
                if (cur_pos[i]->val<vmin)
                {
                    vmin=cur_pos[i]->val;
                    imin=i;
                }
            }
            if (outlist==NULL)
            {
                outlist=cur_pos[imin];
                out_pos=outlist;
            }
            else
            {
                out_pos->next=cur_pos[imin];
                out_pos=out_pos->next;
            }
            if (cur_pos[imin]->next==NULL)
            {
                cur_pos.erase(cur_pos.begin()+imin);
            }
            else
            {
                cur_pos[imin]=cur_pos[imin]->next;
            }
            out_pos->next=NULL;
        }
        return outlist;
    }
*/

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        vector<ListNode *> minhp;
        ListNode *outlist=NULL, *out_pos=NULL, *l;

        minhp.clear();
        for (int i=0; i<int(lists.size()); i++)
        {
            if (lists[i]!=NULL)
                pushHeap(minhp, lists[i]);
        }

        while(minhp.size()>0)
        {
            l=popHeap(minhp);
            if (outlist==NULL)
            {
                outlist=l;
            }
            else
            {
                out_pos->next=l;
            }
            out_pos=l;
            l=l->next;
            out_pos->next=NULL;
            if (l!=NULL)
				pushHeap(minhp, l);
        }
        return outlist;
    }

	//main test program
	void Test(void)
	{
		ListNode *outlist;
		vector<ListNode *> lists;
		lists.clear();

		outlist=mergeKLists(lists);
		cout << "output list: "  << endl;
		printList(outlist);
	}
};

