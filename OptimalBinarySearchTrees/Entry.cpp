#include "Header.h";
#include <queue>;

class Entry
{
private:
	int endPointA;
	int	endPointB;
	int minWeight;
	int minComparisons;
	queue <int> optimalRoots;

public:
	Entry::Entry(int a, int b, int mWeight, int mComparisons, queue <int> opRoots)
		:endPointA(a), endPointB(b), minWeight(mWeight), minComparisons(mComparisons), optimalRoots(opRoots) {};
};

