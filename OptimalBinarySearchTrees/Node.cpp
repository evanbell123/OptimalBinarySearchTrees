
#include "Header.h"

class Node
{
private:
	int frequency;
	int level;
	double standardDeviation;
	Node *left;
	Node *right;
public:
	Node(int freq, int lev)
	{
		frequency = freq;
		level = lev;
	}

	void display()
	{
		cout << "Frequency = " << frequency << endl;
		cout << "Level = " << level << endl;
	}
};