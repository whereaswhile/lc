#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <time.h>
#include "./solution/MergeSortedArray.h"
using namespace std;

int main(void)
{
	Solution s;
	time_t t1, t2;

	cout << "testing..." << endl;
	time(&t1);
	s.Test();
	time(&t2);
	double t=difftime(t2, t1);
	cout << t << " seconds elasped." << endl;
}

