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
	
	BinaryTree(int lev) : left(NULL), right(NULL), key(-1), freq(-1), level(lev) {}

	BinaryTree(int k, int val, int lev) : left(NULL), right(NULL), key(k), freq(val), level(lev) {}

	void setKey(int k) { key = k; }
	void setFreq(int f) { freq = f; }
	void setLevel(int lev) { level = lev; }

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
	int optimalRoot; // equivalent optimal roots
public:
	Entry() : minFrequency(0), minComparisons(0), optimalRoot(0) {};
	//Entry(int mFrequency) : minFrequency(mFrequency), minComparisons(0) {};
	//Entry(int mFrequency, int mComparisons) : minFrequency(mFrequency), minComparisons(mComparisons) {};
	Entry(int mFrequency, int mComparisons, int opRoot) : minFrequency(mFrequency), minComparisons(mComparisons), optimalRoot(opRoot) {};

	const int getMinFrequency() const { return minFrequency; };
	const int getMinComparisons() const { return minComparisons; };
	const int getOptimalRoot() const { return optimalRoot; };

	/*
	void setMinFrequency(int mFreq) { minFrequency = mFreq; };
	void setMinComparisons(int mComp) { minComparisons = mComp; };
	void setOptimalRoot(int opRoot) { optimalRoot = opRoot; };
	*/

	void print(int width)
	{
		cout << setw(width) << '|'
			<< "F = " << minFrequency << endl
			<< setw(width) << '|'
			<< "C = " << minComparisons << endl
			<< setw(width) << '|'
			<< "R = " << optimalRoot << endl;
	};

};
