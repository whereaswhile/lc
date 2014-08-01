/*
 * note: use flat structure to save duplicated computation in recursion
 * */


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
 
class Solution {
public:
    int minDistanceSlow(string word1, string word2)
    {
        //reduce length
        int l1=word1.length();
        int l2=word2.length();
        while (l1>0 && l2>0 && word1[0]==word2[0])
        {
            word1=word1.substr(1);
            word2=word2.substr(1);
            l1--;
            l2--;
        }
        while (l1>0 && l2>0 && word1[l1-1]==word2[l2-1])
        {
            word1=word1.substr(0, l1-1);
            word2=word2.substr(0, l2-1);
            l1--;
            l2--;
        }

        //base case
        if(word1.compare(word2)==0)
            return (0);
        if(l1==0)
            return (l2);
        if(l2==0)
            return (l1);

        //recursion
        int l_del=minDistance(word1, word2.substr(1));
        int l_add=minDistance(word1.substr(1), word2);
        int l_rep=minDistance(word1.substr(1), word2.substr(1));
        return (min(l_del, min(l_add, l_rep))+1);
    }

    int minDistance(string word1, string word2)
    {
        int l1=word1.length();
        int l2=word2.length();
        int **dmat, d;

        //check empty cases (mistake)
        if(l1==0)
            return (l2);
        if(l2==0)
            return (l1);
        if(word1.compare(word2)==0)
            return (0);

        //allocate distance matrix (l1+1)x(l2+1)
        dmat=(int **)malloc(sizeof(int *)*(l1+1));
        for (int i=0; i<l1+1; i++)
            dmat[i]=(int *)malloc(sizeof(int)*(l2+1));
        
        //evaluate distance
        for (int i=0; i<l1+1; i++)
        {
            for (int j=0; j<l2+1; j++)
            {
                if (i==0)
                {
                    dmat[i][j]=j; continue;
                }
                if (j==0)
                {
                    dmat[i][j]=i; continue;
                }
                if (word1[i-1]==word2[j-1])
                {
                    dmat[i][j]=dmat[i-1][j-1]; continue;
                }
                
                dmat[i][j]=1+dmat[i-1][j-1]; //replace
                dmat[i][j]=min(dmat[i][j], 1+dmat[i-1][j]); //insert
                dmat[i][j]=min(dmat[i][j], 1+dmat[i][j-1]); //delete
            }
        }
        d=dmat[l1][l2];
        
        //free distance matrix
        for (int i=0; i<l1+1; i++)
            free(dmat[i]);
        free(dmat);
        
        return(d);
    }

	//main test program
	void Test(void)
	{
		string a1="safdaxbcsfad", a2="fabcsdaolsza";
		//string a1="dinitrophenylhydrazine", a2="benzalphenylhydrazone";
		int d=minDistance(a1, a2);
		cout << "d(\"" << a1 << "\", \"" << a2 << "\")=" << d << endl;
	}
};

