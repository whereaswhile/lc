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

    int evalRPN(vector<string> &tokens)
    {
        vector<int> numbers;
        numbers.clear();
        
        for (int i=0; i<tokens.size(); i++)
        {
            int l=numbers.size();
            if(tokens[i][0]=='+' && tokens[i].length()==1)
            {
                numbers[l-2]=numbers[l-2]+numbers[l-1];
                numbers.pop_back();
            }
            else if(tokens[i][0]=='-' && tokens[i].length()==1) //mistake: negative number can start with "-"
            {
                numbers[l-2]=numbers[l-2]-numbers[l-1];
                numbers.pop_back();
            }
            else if(tokens[i][0]=='*')
            {
                numbers[l-2]=numbers[l-2]*numbers[l-1];
                numbers.pop_back();
            }
            else if(tokens[i][0]=='/')
            {
                numbers[l-2]=numbers[l-2]/numbers[l-1];
                numbers.pop_back();
            }
            else //number
            {
                numbers.push_back(atoi(tokens[i].c_str()));
            }
        }
        
        assert(numbers.size()==1);
        return(numbers[0]);
    }

	//main test program
	void Test(void)
	{
		vector<string> tokens;
		tokens.push_back(string("4"));
		tokens.push_back(string("13"));
		tokens.push_back(string("5"));
		tokens.push_back(string("/"));
		tokens.push_back(string("+"));
		cout << "result is: " << evalRPN(tokens) << endl;
	}
};

