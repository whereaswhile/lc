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

class Solution{
public:
    string spaceString(int n)
    {
        string s="";
        assert(n>=0);
        for (int i=0; i<n; i++)
            s=s+" ";
        return(s);
    }
    
    vector<string> fullJustify(vector<string> &words, int L)
    {
        vector<string> lines;
        string line;
        int l=0, lnew, li, idxs=0, idxe, nspace, nword;
        lines.clear();
        for (int i=0; i<words.size(); i++)
        {
            li=words[i].length(); //word with one space
            assert(li<=L);
            l+=(li+1);
            if (L>=l+1 && i!=words.size()-1)
            {
                continue;
            }

            //prepare new line
            if (L>=l-1)
            {
                idxe=i;
                lnew=0;
            }
            else //if (L<l-1)
            {
                idxe=i-1;
                l-=(li+1);
                lnew=li+1;
            }
            nword=(idxe-idxs+1);
            nspace=L-l+nword;
            line="";
            for (int j=0; j<nword; j++)
            {
                line=line+words[idxs+j];
                int n;
                if (nword==1) //single word line
                {
                    n=nspace;
                }
                else if (idxe==words.size()-1) //mistake: last line right justified!
                {
                    if(j<nword-1)
                    {
                        n=1;
                    }
                    else
                    {
                        n=nspace-(nword-1);
                    }
                }
                else //middel lines
                {
                    if(j==nword-1)
                    {
                        n=0;
                    }
                    else
                    {
                        n=nspace/(nword-1);
                        n+=(j<nspace%(nword-1)) ? 1 : 0;
                    }
                }
                line=line+spaceString(n);
            }
            lines.push_back(line);
            idxs=idxe+1;
            l=lnew;
        }//end for i
        assert(idxs>=words.size()-1);
        if(idxs==words.size()-1) //mistake: when last word not added
        {
            line=words[idxs]+spaceString(L-words[idxs].length());
            lines.push_back(line);
        }
        return(lines);
    }

	//main test program
	void Test(void)
	{
		cout << "no test available" << endl;
	}
};

