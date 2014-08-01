/*
 * note: dont forget head and tail linkage when modifying linked list
 * note: merge sort, constance space for linked list, not for array
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <vector>
using namespace std;

// Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };
 
class Solution {
public:

    void printList(ListNode *node)
	{
        while(1)
		{
            if (node==NULL)
				break;
			cout << node->val << " ";
			node=node->next;
		}
		cout << "\b\n";
	}

    ListNode *getNextNode(ListNode *node, int n)
    {
        assert(n>=0);
        for (int i=0; i<n; i++)
        {
            if (node==NULL)
                break;
            node=node->next;
        }
        return(node);
    }
    
    int getListLength(ListNode *node)
    {
        int n=0;
        while(1)
        {
            if (node==NULL)
                break;
            node=node->next;
            n++;
        }
        return(n);
    }
    
    //merge [prev+1, prev+gsize] and [prev+gsize+1, prev+2*gsize], both sorted
    //list can be shorter, or empty
    //n is the number of processed nodes, beginning from prev+1
    //return the pointer to the last processed node, or NULL if second half list is empty
    ListNode *mergeHalfSortedList(ListNode *prev1, int gsize, int &n)
    {
        ListNode *list1, *list2, *prev2;
        assert(prev1!=NULL);

        list1=prev1->next;
        if (list1==NULL)
        {
            n=0;
            return (NULL);
        }
        prev2=getNextNode(list1, gsize-1);
        list2=getNextNode(prev2, 1);
        if (list2==NULL)
        {
            n=getListLength(list1);
            return (NULL);
        }
        
        //both lists are non-empty
        n=gsize; //length of list1
        while (1)
        {
			//cout << "current l1/l2:" << endl;
			//printList(list1);
			//printList(list2);
            if(list1==list2) //list1 empty
            {
                prev1->next=list2;
                while (1)
                {
                    if (n==gsize*2 || prev2->next==NULL)
                        break;
                    prev2=prev2->next;
                    n++;
                }
                return (prev2);
            }
            if (list2==NULL || n==gsize*2) //list1 remains, list2 empty
            {
                prev1->next=list1;
                return (prev2);
            }
            if (list1->val <= list2->val)
            {
                prev1->next=list1;
                prev1=list1;
                list1=list1->next;
            }
            else //list1->val > list2->val
            {
                prev1->next=list2;
                prev1=list2;
                list2=list2->next;
                prev2->next=list2;
                n++;
            }
        }//end while
    }

    //n is the length of list
    ListNode *sortListByGroup(ListNode *head, int gsize, int &n)
    {
        if (head==NULL)
        {
            n=0;
            return (head);
        }
        if (head->next==NULL)
        {
            n=1;
            return (head);
        }

        assert(gsize>=1);
        ListNode dummy(0);
        ListNode *prev;
        int ni;
        dummy.next=head;
        prev=&dummy;
        n=0;
        while (1) //group, O(N) complexity
        {
            prev=mergeHalfSortedList(prev, gsize, ni);
            n+=ni;
			cout << ni << " elements processed" << endl;
            if (ni<gsize*2 || prev==NULL) break;
        }
        return (dummy.next); //mistake: dont forget return
    }

    ListNode *sortList(ListNode *head)
    {
        int gsize=1, n=0;
        while (1) //layer, O(logN) complexity
        {
			cout << "sorting with group size " << gsize << endl;
            head=sortListByGroup(head, gsize, n);
            gsize*=2;
            if (n<=gsize) break;
        }
        return(head);
    }

	//main test program
	void Test(void)
	{
		ListNode a(2), b(1);
		a.next=&b;
		cout << "list:" << endl;
		printList(&a);
		ListNode *l=sortList(&a);
		cout << "sorted list:" << endl;
		printList(l);
	}
};

