#include "Header.h"

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
		addOptimalRoot(opRoot);
	};
	Entry(int mWeight, int mComparisons, queue<int> opRoots) : minFrequency(mWeight), minComparisons(mComparisons)
	{
		swap(optimalRoots, opRoots);
	};

	int getMinFrequency() { return minFrequency; };
	int getMinComparisons() { return minComparisons; };
	queue <int> getOptimalRoots() { return optimalRoots; };

	//return root at front of queue, then pop
	int popOptimalRoot()
	{
		if (!optimalRoots.empty())
		{
			int root = optimalRoots.front();
			optimalRoots.pop();
			return root;
		}
		else
		{
			return -1;
		}
	}

	void setMinFrequency(int mWeight) { minFrequency = mWeight; };
	void setMinComparisons(int mComparisons) { minComparisons = mComparisons; };
	void setOptimalRoots(queue<int> opRoots) { swap(optimalRoots, opRoots); };


	void addOptimalRoot(int root) { optimalRoots.push(root); };
	void Entry::print(int width)
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
