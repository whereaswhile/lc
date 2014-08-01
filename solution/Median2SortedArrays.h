/*
 * note: hard core, use binary search in two sorted array
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

class Solution {
public:
	void printArray(int A[], int m)
	{
		for (int i=0; i<m; i++)
			cout << A[i] << ", ";
		cout << endl;
	}

    double findMedianSortedArray(int A[], int m)
    {
        assert(m>0);
        if (m%2==1)
		{
            return (A[m/2]);
		}
        else
		{
            return ((A[m/2-1]+A[m/2])/2.0);
		}
    }
    
    int *cutSortedArray(int *A, int &m, bool cutMax, bool cutMin, int cutLength)
    {
        bool inc=(A[m-1]>A[0]);
        bool cutHead=(inc && cutMin) || (!inc && cutMax);
        bool cutTail=(inc && cutMax) || (!inc && cutMin);
        if (cutHead && cutTail)
        {
            A=A+cutLength;
            m=m-2*cutLength;
        }
        else if (cutHead)
        {
            A=A+cutLength;
            m=m-cutLength;
        }
        else if (cutTail)
        {
            m=m-cutLength;
        }
        return (A);
    }

    double findNthLargest(int A[], int m, int i)
    {
        assert(i>=0 && i<m);
        bool inc=(A[m-1]>A[0]);
        if (inc)
            return (A[m-1-i]);
        else
            return (A[i]);
    }
    
    double findNthSmallest(int A[], int m, int i)
    {
        return(findNthLargest(A, m, m-1-i));
    }

    double findMedianSortedArraysSlow(int A[], int m, int B[], int n)
    {
        assert(m>0 || n>0);
        if (m==0)
            return (findMedianSortedArray(B, n));
        if (n==0)
            return (findMedianSortedArray(A, m));

        int *At=A, *Bt=B;
        int mt=m, nt=n; //current elements in the arrays
        double Amed, Bmed; //mistake: median cannot be int!
        int Emin=0, Emax=0; //count of eliminated elements
        bool bCutAmin, bCutAmax, bCutBmin, bCutBmax;
		int cutA, cutB;
        
        while (1)
        {
            Amed=findMedianSortedArray(At, mt);
            Bmed=findMedianSortedArray(Bt, nt);
			cout << "med=" << Amed << ", " << Bmed << endl;
            if (Amed==Bmed && Emin==Emax)
                return (Amed);

            //both nt and mt positive    
            bCutAmax=(Amed>=Bmed)&&(Emax<=Emin);
            bCutBmax=(Bmed>=Amed)&&(Emax<=Emin);
            bCutAmin=(Amed<=Bmed)&&(Emin<=Emax);
            bCutBmin=(Bmed<=Amed)&&(Emin<=Emax);
			cutA=mt/2; //mistake: keep cut length, since mt changes
			cutB=nt/2;
            At=cutSortedArray(At, mt, bCutAmax, bCutAmin, cutA);
            Bt=cutSortedArray(Bt, nt, bCutBmax, bCutBmin, cutB);
            assert(mt>0 && nt>0); //will not cut to zero-length
            Emin+=int(bCutAmin)*cutA+int(bCutBmin)*cutB;
            Emax+=int(bCutAmax)*cutA+int(bCutBmax)*cutB;
			assert(Emax+Emin+mt+nt==m+n);

			if (1) //debug
			{
				cout << "==========\n";
				printArray(At, mt);
				printArray(Bt, nt);
			}

            if (nt==1 && mt==1)
            {
                if (Emin==Emax)
                    return ((*At+*Bt)/2.0);
                else if (Emin==Emax-1)
                    return (max(*At, *Bt));
                else if (Emin-1==Emax)
                    return (min(*At, *Bt));
                else
                    return (-0.101); //error
            }

            if (mt==1 || nt==1)
            {
                int m1=(mt==1) ? *At : *Bt;
                int m2=(mt==1) ? findMedianSortedArray(Bt, nt) : findMedianSortedArray(At, mt);
                int *St=(mt==1) ? Bt : At;
                int lt=max(mt, nt);
                if (m1>m2 && Emax<Emin)
                {
                    if (findNthLargest(St, lt, Emin-Emax-1) <= m1)
                    {
                        St=cutSortedArray(St, lt, 1, 0, Emin-Emax-1);
                        return(findMedianSortedArray(St, lt));
                    }
                    else
                    {
                        St=cutSortedArray(St, lt, 1, 0, Emin-Emax);
                        if (nt==1)
                        {
                            At=St; mt=lt; 
                        }
                        else
                        {
                            Bt=St; nt=lt;
                        }
                        continue;
                    }
                }
                if (m1<m2 && Emax>Emin)
                {
					cout << "E: " << Emax << ", " << Emin << endl;
					cout << "m: " << m1 << ", " << m2 << endl;
					printArray(St, lt);
                    if (findNthSmallest(St, lt, Emax-Emin-1) >= m1)
                    {
                        St=cutSortedArray(St, lt, 0, 1, Emax-Emin-1);
                        return(findMedianSortedArray(St, lt));
                    }
                    else
                    {
                        St=cutSortedArray(St, lt, 0, 1, Emax-Emin);
                        if (nt==1)
                        {
                            At=St; mt=lt; 
                        }
                        else
                        {
                            Bt=St; nt=lt;
                        }
                        continue;
                    }
                }
            }
        }//end while
    }

/*****************************************************************************************/

    void findRankIdx(const int A[], int m, const int B[], int n, int h, int &i, int &m1, int &m2)
    {
        int is=max(0, h-m), ie=min(n-1, h);
        while (1)
        {
            if (ie<is)
            {
                i=-1; //not found
                break;
            }
            i=(is+ie)/2; //binary search
            if(h-i<m && B[i]>A[h-i]) //too big
            {
                ie=i-1;
                continue;
            }
            if(i<h && B[i]<A[h-i-1]) //too small
            {
                is=i+1;
                continue;
            }
            //found
            m1=B[i];
            m2=min(A[0], B[0]); //m2 is the immediate preceding element to m1
            if (i<h)
                m2=max(m2, A[h-i-1]);
            if (i>0)
                m2=max(m2, B[i-1]);
            break; //mistake: don't forget break here!
        }//end while
    }
    
    double findMedianSortedArrays(int A[], int m, int B[], int n)
    {
        assert(m>0 || n>0);
        if (m==0)
            return (findMedianSortedArray(B, n));
        if (n==0)
            return (findMedianSortedArray(A, m));

        //both are non-empty arrays
        int h=(m+n)/2;
        int i=-1, m1, m2;
        findRankIdx(A, m, B, n, h, i, m1, m2);
        if(i==-1) //not found in B
        {
            findRankIdx(B, n, A, m, h, i, m1, m2);
        }
        assert(i>=0);
        if ((m+n)%2==1)
            return m1;
        else
            return (m1+m2)/2.0;
    }

	//main test program
	void Test(void)
	{
		int A[]={1, 5};
		int B[]={2, 3, 4, 6};
		int m=sizeof(A)/sizeof(int), n=sizeof(B)/sizeof(int);

		printArray(A, m);
		printArray(B, n);

	    double med=findMedianSortedArrays(A, m, B, n);
		cout << "median=" << med << endl;
	}
};

