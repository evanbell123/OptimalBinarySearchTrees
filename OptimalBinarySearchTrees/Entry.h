//#include "Header.h"
#include <queue>
#include <iostream>
#include <iomanip>
using namespace std;

class Entry
{
private:
	int minFrequency;
	int minComparisons;
	queue <int> optimalRoots;
public:
	Entry() : minFrequency(0), minComparisons(0) {};
	Entry(int mWeight) : minFrequency(mWeight), minComparisons(0) {};
	Entry(int mWeight, int mComparisons) : minFrequency(mWeight), minComparisons(mComparisons) {};
	Entry(int mWeight, int mComparisons, int opRoot) : minFrequency(mWeight), minComparisons(mComparisons)
	{
		pushOptimalRoot(opRoot);
	};
	Entry(int mWeight, int mComparisons, queue<int> opRoots) : minFrequency(mWeight), minComparisons(mComparisons)
	{
		swap(optimalRoots, opRoots);
	};

	int getMinFrequency() { return minFrequency; };
	int getMinComparisons() { return minComparisons; };
	queue <int> getAllOptimalRoots() { return optimalRoots; };

	void popOptimalRoot()
	{
		if (!optimalRoots.empty())
		{
			optimalRoots.pop();
		}
	}

	int getOptimalRoot()
	{
		return optimalRoots.front();
	}

	void setMinFrequency(int mWeight) { minFrequency = mWeight; };
	void setMinComparisons(int mComparisons) { minComparisons = mComparisons; };
	void setOptimalRoots(queue<int> opRoots) { swap(optimalRoots, opRoots); };


	void pushOptimalRoot(int root) { optimalRoots.push(root); };
	void print(int width)
	{
		queue <int> temp = optimalRoots;
		cout << setw(width) << '|'
			<< "F = " << minFrequency << endl
			<< setw(width) << '|'
			<< "C = " << minComparisons << endl
			<< setw(width) << '|'
			<< "R = ";
		while (!temp.empty())
		{
			cout << temp.front() << " ";
			temp.pop();
		}
		cout << endl;
	};

};
