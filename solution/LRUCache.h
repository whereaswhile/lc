/*
 * note: linear search is not accepted
 * note: to use binary search, use vector template
 * note: to rank by age, use linked list 
 * note: use hash map simplify the key search
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <vector>
#include <map>
using namespace std;

class LRUCacheOld{
public:
struct Node{
    int val;
    int key;
    unsigned long age;
    Node(int x, int k): val(x), key(k), age(0) {}
};

private:
    int n, size;
    Node *array;
    
public:
    LRUCacheOld(int capacity)
    {
        assert(capacity>0);
        size=capacity;
        n=0;
        array=(Node *)malloc(sizeof(Node)*capacity);
    }
    
    ~LRUCacheOld()
    {
        free(array);
    }

    int get(int key)
    {
        int val=-1;
        for (int i=0; i<n; i++)
        {
            if (array[i].key==key)
            {
                val=array[i].val;
                array[i].age=0;
            }
            else
            {
                array[i].age++;
            }
        }
        return (val);
    }
    
    void set(int key, int value)
    {
        bool found=false;
        Node *old_node=array;
        for (int i=0; i<n; i++)
        {
            if (array[i].key==key)
            {
                array[i].val=value;
                array[i].age=0;
                found=true;
            }
            else
            {
                array[i].age++;
                if (array[i].age<old_node->age)
                {
                    old_node=array+i;
                }
            }
        }
        if (!found && n<size) //append
        {
            array[n]=Node(value, key);
            n++;
        }
        else if (!found && n==size) //replace least visited, //mistake: else if, n changed in previous if
        {
            *old_node=Node(value, key);
        }
    }
};


class LRUCacheVec{
public:
struct LinkNode{
    int key; //key in CacheElt array
    LinkNode *prev, *next;
    LinkNode(int k): key(k), prev(NULL), next(NULL) {}
};

struct CacheElt{
    int val;
    int key;
    LinkNode *agenode;
    CacheElt(int x, int k): val(x), key(k), agenode(NULL) {}
};

private:
    int max_n;
    vector<CacheElt> array; //sorted by key in ascending
    LinkNode *agehead, *agetail; //ranked by age from old to young

public:
    LRUCacheVec(int capacity)
    {
        assert(capacity>0);
        max_n=capacity;
        array.clear();
        agehead=agetail=NULL;
    }
    
    ~LRUCacheVec()
    {
        array.clear();
        LinkNode *tmp;
        while(agehead!=NULL)
        {
            tmp=agehead;
            agehead=agehead->next;
            delete tmp;
        }
    }
    
private:
    //search for key
    //if not found, return -1
    //if found, return its value, or change its value to nv if set==true
    int search(int key, bool set, int nv, int &idxs, int &idxe)
    {
        int val=-1, i;
        idxs=0, idxe=array.size()-1;
        while (1)
        {
            if (idxs>idxe) break;
            i=(idxs+idxe)/2;
            if (array[i].key==key)
            {
                if (set==true)
                    array[i].val=nv;
                val=array[i].val;
                if (agetail->key!=key) //move to the tail of age list
                {
                    if (agehead->key==key) //from head to tail
                    {
                        agehead=agehead->next;
                        agehead->prev=NULL;
                        array[i].agenode->next=NULL;
                        array[i].agenode->prev=agetail;
                        agetail->next=array[i].agenode;
                        agetail=array[i].agenode;
                    }
                    else //from middle to tail
                    {
                        array[i].agenode->prev->next=array[i].agenode->next;
                        array[i].agenode->next->prev=array[i].agenode->prev;
                        array[i].agenode->next=NULL;
                        array[i].agenode->prev=agetail;
                        agetail->next=array[i].agenode;
                        agetail=array[i].agenode;
                    }
                }
                idxs=idxe=i;
                break;
            }
            else if (array[i].key<key)
            {
                idxs=i+1;
            }
            else //if (array[i].key>key)
            {
                idxe=i-1;
            }
        }//end while
        return (val);
    }

public:
    int get(int key)
    {
        int idxs, idxe;
        return (search(key, false, 1, idxs, idxe));
    }
    
    void set(int key, int value)
    {
        assert(value>0);
        int res, idxs, idxe;
        res=search(key, true, value, idxs, idxe);
        if (res==value) return; //existing key

        //new key
		cout << "adding new key " << key << endl;
        CacheElt elt(value, key);
        LinkNode *agenode=new LinkNode(key);
        elt.agenode=agenode;
        if (agehead==NULL) //empty cache
        {
			cout << "adding first item..." << endl;
            array.push_back(elt);
            agehead=agetail=agenode;
            agenode->prev=NULL;
            agenode->next=NULL;
            return;
        }
        
        //insert new key at position near idxs/idxe
        if (array[0].key>key) //insert at head
        {
			cout << "inserting at head..." << endl;
            array.insert(array.begin(), elt);
        }
        else if (array[array.size()-1].key<key) //insert at tail
        {
			cout << "inserting at tail..." << endl;
            array.push_back(elt);
        }
        else //insert in middle
        {
			cout << "inserting at middle..." << endl;
            idxs=max(0, min(idxs, idxe)-1);
            for (; idxs<array.size(); idxs++)
            {
                if (array[idxs].key>key)
                {
                    break;
                }
            }
            array.insert(array.begin()+idxs, elt);
        }
        agetail->next=agenode;
        agenode->prev=agetail;
        agenode->next=NULL;
        agetail=agenode;
    
        //full cache, remote the least recent visited (agehead) key
        if (array.size()>max_n)
        {
			cout << "removing key " << agehead->key << endl;
            search(agehead->key, false, 1, idxs, idxe); //move agenode to end
            agetail=agetail->prev;
            delete agetail->next;
            agetail->next=NULL;
            array.erase(array.begin()+idxs);
        }
    }
};

class LRUCache{
private:
	struct CacheElt{
		int val;
		list<int>::iterator agenode;
		CacheElt(int x): val(x) {}
	};
    int max_n;
    map<int, CacheElt> cachemap; //indexed by key
    list<int> agelist; //ranked by age from old to young

public:
    LRUCache(int capacity)
    {
        assert(capacity>0);
        max_n=capacity;
        cachemap.clear();
        agelist.clear();
    }
    
    ~LRUCache()
    {
        cachemap.clear();
        agelist.clear();
    }

    int get(int key)
    {
		map<int, CacheElt>::iterator itr=cachemap.find(key);
		if (itr==cachemap.end())
		{
			return -1;
		}
		else
		{
			//update agelist
			agelist.erase(itr->second.agenode);
			agelist.push_back(key);
			itr->second.agenode=--agelist.end();
        	return itr->second.val;
		}
    }
    
    void set(int key, int value)
    {
        assert(value>0);
        
        pair<int, CacheElt> p(key, CacheElt(value));
		pair<map<int, CacheElt>::iterator,bool> res=cachemap.insert(p);
		map<int, CacheElt>::iterator itr=res.first;
		if (res.second==true) //new key
		{
    		cout << "adding new key " << key << endl;
		}
		else //existing key
		{
			cout << "updating existing key " << key << endl;
			itr->second.val=value;
    		agelist.erase(itr->second.agenode);
		}
		//update agelist
		agelist.push_back(key);
		itr->second.agenode=--agelist.end();
		
        //full cache, remote the least recent visited (agelist head) key
        if (cachemap.size()>max_n)
        {
			cout << "removing key " << *agelist.begin() << endl;
			cachemap.erase(*agelist.begin());
			agelist.erase(agelist.begin());
        }
    }
};

class Solution{
public:
	//main test program
	void Test(void)
	{
		LRUCache *c=new LRUCache(2);
		cout << "set(2, 1)..." << endl;
		c->set(2, 1);
		cout << "set(1, 1)..." << endl;
		c->set(1, 1);
		cout << "get(2): " << c->get(2) << endl;
		cout << "set(4, 1)..." << endl;
		c->set(4, 1);
		cout << "get(1): " << c->get(1) << endl;
		cout << "get(2): " << c->get(2) << endl;
	}
};

