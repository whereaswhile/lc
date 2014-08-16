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


class Solution {
public:
    void printSudoku(vector<vector<char> > &board)
    {
		assert(board.size()==9);
		assert(board[0].size()==9);
        for (int i=0; i<board.size(); i++)
        {
            for (int j=0; j<board[0].size(); j++)
            {
                cout << board[i][j] << " ";
                if (j%3==2 && j!=board[0].size()-1)
                {
                    cout << "| ";
                }
            }
            cout << endl;
            if (i%3==2 && i!=board.size()-1)
            {
                cout << "-----------------------" << endl;
            }
        }
    }

    void initCand(vector<vector<vector<bool> > > &cand, vector<vector<char> > &board)
    {
        cand.clear();
        cand.resize(board.size());
        for (int i=0; i<board.size(); i++) //each row
        {
            cand[i].clear();
            cand[i].resize(board[i].size());
            for (int j=0; j<board[i].size(); j++) //each col
            {
                cand[i][j].clear();
                cand[i][j].resize(10, true); //only [1-9] useful
            }
        }
    }

    //update cand with kowning board[i, j]=v
    void updateCand(vector<vector<vector<bool> > > &cand, int i, int j, int v)
    {
        //update row-i
        for (int k=0; k<cand[i].size(); k++)
        {
            cand[i][k][v]=false;
        }
        //update col-j
        for (int k=0; k<cand.size(); k++)
        {
            cand[k][j][v]=false;
        }
        //update 3x3 block-(i, j)
        int bi=i/3, bj=j/3; //mistake: divide, not modulus
        for (int k=bi*3; k<bi*3+3; k++)
        {
            for (int l=bj*3; l<bj*3+3; l++)
            {
                cand[k][l][v]=false;
            }
        }
        cand[i][j].clear();
        cand[i][j].resize(10, false);
        cand[i][j][v]=true;
    }

    //1: updated board; 2: solved board; 0: cannot update and not solved; -1: conflict
    int updateBoard(vector<vector<char> > &board, vector<vector<vector<bool> > > &cand, int &i0, int &j0)
    {
        bool updated=false, solved=true;
        int k0=0, cnt, v; //mistake: cnt should be defined here, and initialized below
        for (int i=0; i<board.size(); i++) //each row
        {
        for (int j=0; j<board[i].size(); j++) //each col
        {
            if (board[i][j]!='.') continue;
			cnt=0;
            for (int k=1; k<=9; k++)
            {
                if (cand[i][j][k])
                {
                    v=k;
                    cnt++;
                    if (cnt==2)
                    {
                        if (k>k0)
                        {
                            i0=i;
                            j0=j;
							k0=k;
                        }
                        break;
                    }
                }
            }
            if (cnt==0)
            {
                return (-1); //not possible solution
            }
            else if (cnt==1)
            {
                board[i][j]='1'+(v-1); //solution found
				//printf("updated: (%d, %d)=%d\n", i, j, v);
                updateCand(cand, i, j, v);
                updated=true;
            }
            else
            {
                solved=false;
            }
        }//for j
        }//for i
        if (solved)
            return(2);
        if (updated)
            return(1);
        else
            return(0);
    }
    
    bool recSolveSudoku(vector<vector<char> > &board, vector<vector<vector<bool> > > &cand)
    {
        int res, i0, j0;
        while (1)
        {
            res=updateBoard(board, cand, i0, j0);
            if (res==-1) //conflict
                return(false);
            if (res==2) //solved
                return(true);
            if (res==1) //board updated
                continue;

			cout << "updated res=" << res << ", board:\n";
			printSudoku(board);
            //res==0, cannot update, guess and recursive
            assert(board[i0][j0]=='.');
            vector<vector<char> > boardnew;
            vector<vector<vector<bool> > > candnew;
            for (int k=1; k<=9; k++) 
            {
                if (!cand[i0][j0][k]) continue;
				printf("guessing %d at (%d, %d)\n", k, i0, j0);
                boardnew=board;
                candnew=cand;
                boardnew[i0][j0]='1'+(k-1);
                updateCand(candnew, i0, j0, k);
                res=recSolveSudoku(boardnew, candnew);
                if (res==true)
                {
                    board=boardnew;
                    cand=candnew;
                    return(true);
                }
            }
			printf("fail all possible (%d, %d)\n", i0, j0);
			return(false); //mistake: possibly cannot go further
        }//while
    }

    void solveSudoku(vector<vector<char> > &board)
    {
        vector<vector<vector<bool> > > cand;
        
        //initialize cand
        initCand(cand, board);

        //initial update of cand
        for (int i=0; i<board.size(); i++) //each row
        {
            for (int j=0; j<board[i].size(); j++) //each col
            {
                if (board[i][j]!='.')
                {
					//printf("updateCand: (%d, %d), %d\n", i, j, board[i][j]-'1'+1);
                    updateCand(cand, i, j, board[i][j]-'1'+1); //mistake: char is continous in vector!!
					/*for (int k=1; k<=9; k++)
						cout << cand[0][0][k] << ", ";
					cout << endl;*/
                }
            }
        }
		//assert(0);

        //solve
        bool res=recSolveSudoku(board, cand);
        assert(res);
    }
    
	//main test program
	void Test(void)
	{
		/*const char *p[]={"53..7....", "6..195...", ".98....6.",
					     "8...6...3", "4..8.3..1", "7...2...6",
					     ".6....28.", "...419..5", "....8..79"};*/
		/*const char *p[]={"..9748...", "7........", ".2.1.9...",
						 "..7...24.", ".64.1.59.", ".98...3..",
						 "...8.3.2.", "........6", "...2759.."};*/
		const char *p[]={"...2...63", "3....54.1", "..1..398.",
						 ".......9.", "...538...", ".3.......",
						 ".263..5..", "5.37....8", "47...1..."};

		//initialize
		vector<vector<char> > board;
		board.clear();
		for (int i=0; i<9; i++)
		{
			board.push_back(vector<char>(p[i], p[i]+9));
		}

		cout << "problem:" << endl;
        printSudoku(board);
		solveSudoku(board);
		cout << "solution:" << endl;
        printSudoku(board);
	}
};

