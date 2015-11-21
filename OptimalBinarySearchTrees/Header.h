#include <iostream>
#include <queue>
#include <string>
#include <iomanip>
#include <map>
#include <sstream>
using namespace std;


struct BinaryTree {
	BinaryTree *left, *right;
	int key;
	int freq;
	int level;
	double eOfXSquared; // E[X^2]

	BinaryTree(int k, int val, int lev) : left(NULL), right(NULL), key(k), freq(val), level(lev)
	{
		eOfXSquared = level*level*freq;
	}

	~BinaryTree()
	{
		delete left;
		delete right;
	}
};



// Convert an integer value to string
string intToString(int val) {
	ostringstream ss;
	ss << val;
	return ss.str();
}


class Entry
{
private:
	int minFrequency;
	int minComparisons;
	queue <int> optimalRoots;
public:
	Entry() : minFrequency(0), minComparisons(0) {};
	Entry(int mFrequency) : minFrequency(mFrequency), minComparisons(0) {};
	Entry(int mFrequency, int mComparisons) : minFrequency(mFrequency), minComparisons(mComparisons) {};
	Entry(int mFrequency, int mComparisons, int opRoot) : minFrequency(mFrequency), minComparisons(mComparisons)
	{
		pushOptimalRoot(opRoot);
	};
	Entry(int mWeight, int mComparisons, queue<int> opRoots) : minFrequency(mWeight), minComparisons(mComparisons)
	{
		swap(optimalRoots, opRoots);
	};

	const int getMinFrequency() const { return minFrequency; };
	const int getMinComparisons() const { return minComparisons; };
	queue <int> getAllOptimalRoots() { return optimalRoots; };

	void popOptimalRoot()
	{
		if (!optimalRoots.empty())
		{
			optimalRoots.pop();
		}
	}

	Entry getSelf()
	{
		return *this;
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
