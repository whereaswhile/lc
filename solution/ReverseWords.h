
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
 
class Solution {
public:
    void reverseWords(string &s)
    {
        int wcnt=0, p1, p2, l;
        string s2="";
        char c, cprev=' ';

        s=" "+s+" ";
        l=s.length(); //mistake: calculate after appending " "
        for (int i=l-1; i>=0; i--)
        {
            c=s[i];
            if (c==' ' && cprev==' ')
                continue;
            if (c!=' ' && cprev!=' ')
                continue;

            if (c==' ') // && cprev!=' ', beginning of a word
            {
                p1=i+1;
                s2=s2+s.substr(p1, p2-p1+1)+" ";
                wcnt++;
            }
            if (c!=' ') // && cprev==' ', end of a word
            {
                p2=i;
            }
            cprev=c;
        }//end while

        if (wcnt>0) //remove trailing zero
            s2=s2.substr(0, s2.length()-1);
        s=s2;
    }

	//main test program
	void Test(void)
	{
		string s="God is highest";
		cout << s << endl;
		reverseWords(s);
		cout << s << endl;
	}
};

