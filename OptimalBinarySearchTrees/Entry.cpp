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

	void setMinFrequency(int mWeight) { minFrequency = mWeight; };
	void setMinComparisons(int mComparisons) { minComparisons = mComparisons; };
	void setOptimalRoots(queue<int> opRoots) { swap(optimalRoots, opRoots); };


	void addOptimalRoot(int root) { optimalRoots.push(root); };
	void Entry::print()
	{
		queue <int> temp = optimalRoots;

		cout << "Minimum Frequency: " << minFrequency << endl;
		cout << "Minimum Comparisons: " << minComparisons << endl;
		cout << "Optimal Roots: ";
		while (!temp.empty())
		{
			cout << temp.front() << " ";
			temp.pop();
		}
		cout << endl;
	};

};
