#include <stdio.h>
#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
 };
 
 
class Solution {
public:
    void resertList(ListNode **ptr_l)
    {
        ListNode *curr=*ptr_l, *prev=NULL, *tmp;
        while (curr!=NULL)
        {
			//cout << "adding node " << curr->val << endl;
            tmp=curr->next;
            curr->next=prev;
            prev=curr;
            curr=tmp;
        }
        *ptr_l=prev;
    }

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *s=NULL, *n=NULL, *n1=l1, *n2=l2, *new_node;
        int carryover=0, sum;
        while (n1!=NULL || n2!=NULL || carryover>0)
        {
            sum=carryover;
            if (n1!=NULL)
            {
                sum+=n1->val;
                n1=n1->next;
            }
            if (n2!=NULL)
            {
                sum+=n2->val;
                n2=n2->next;
            }
            new_node=new ListNode(sum%10);
            carryover=sum/10;
            if (n==NULL) //allocate head of s
            {
                s=n=new_node;
            }
            else
            {
                n->next=new_node;
                n=new_node;
            }
        }
        
        return(s);
    }

	void PrintList(ListNode *l)
	{
		while (l!=NULL)
		{
			cout << l->val;
			if(l->next!=NULL)
			{
				cout << " -> ";
				l=l->next;
			}
			else
			{
				cout << "\n";
				break;
			}
		}
	}

	//main test program
	void Test(void)
	{
		cout << "testing" << endl;
		ListNode *list=new ListNode(0);
		ListNode *n=list;
		for (int i=1; i<=5; i++)
		{
			n->next=new ListNode(i);
			n=n->next;
		}

		cout << "original: "; PrintList(list);
		resertList(&list);
		cout << "reversed: "; PrintList(list);
		resertList(&list);
		cout << "recovered: "; PrintList(list);

		ListNode *s=addTwoNumbers(list, list->next);
		cout << "sum: "; PrintList(s);
	}
};

