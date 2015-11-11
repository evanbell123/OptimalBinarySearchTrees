#include "Header.h"

class Entry
{
private:
	int minWeight;
	int minComparisons;
	queue <int> optimalRoots;
public:
	Entry() : minWeight(0), minComparisons(0) {};
	Entry(int mWeight) : minWeight(mWeight), minComparisons(0) {};

	void setMinWeight(int mWeight) { minWeight = mWeight; };
	void setMinComparisons(int mComparisons) { minComparisons = mComparisons; };
	void addOptimalRoot(int root) { optimalRoots.push(root); };
	void Entry::print()
	{
		queue <int> temp = optimalRoots;

		cout << "Minimum Weight: " << minWeight << endl;
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
/*
void Entry::print()
{
	queue <int> temp = optimalRoots;

	cout << "Minimum Weight: " << minWeight << endl;
	cout << "Minimum Comparisons: " << minComparisons << endl;
	cout << "Optimal Roots: ";
	while (!temp.empty())
	{
		cout << temp.front() << " ";
		temp.pop();
	}
	cout << endl;
}
*/