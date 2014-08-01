/*
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <vector>
using namespace std;

//Definition for undirected graph.
struct UndirectedGraphNode{
     int label;
     vector<UndirectedGraphNode *> neighbors;
     UndirectedGraphNode(int x) : label(x) {};
};

class Solution {
public:
    UndirectedGraphNode *findNode(int label, vector<UndirectedGraphNode *> &allNodes)
    {
        for (int i=0; i<allNodes.size(); i++)
        {
            if (allNodes[i]->label==label)
                return (allNodes[i]);
        }
        return (NULL); //not found
    }
    
    UndirectedGraphNode *cloneGraphRec(UndirectedGraphNode *node, vector<UndirectedGraphNode *> &allNodes)
    {
        assert(node!=NULL);
        UndirectedGraphNode *new_node;
        new_node=findNode(node->label, allNodes);
        if (new_node!=NULL) //existing
            return (new_node);
            
        //add new node
        new_node=new UndirectedGraphNode(node->label);
        //new_node->neighbors=node->neighbors; //mistake, new pointers need allocated!
        new_node->neighbors.clear();
        allNodes.push_back(new_node);
        //add neighbor
        for (int i=0; i<node->neighbors.size(); i++)
        {
            UndirectedGraphNode *nnode=cloneGraphRec(node->neighbors[i], allNodes);
            new_node->neighbors.push_back(nnode);
        }
        
        return(new_node);
    }
    
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node)
    {
        if (node==NULL)
            return NULL;

        vector<UndirectedGraphNode *> allNodes(0);
        UndirectedGraphNode *new_node=cloneGraphRec(node, allNodes);
        return(new_node);
    }

	//main test program
	void Test(void)
	{
		cout << "test not available!" << endl;
	}
};

