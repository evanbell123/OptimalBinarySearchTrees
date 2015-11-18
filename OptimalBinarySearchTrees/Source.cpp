#include "OBSTComputationTable.h"
#include "BinaryTreeConstruction.h"

//#include <fstream>
//#include <string>

void displayFrequencies(queue<int> frequencies);

BinaryTree *constructOBST(LookupTable &table, int row, int column);


void main()
{
	string line;
	size_t stringSize;
	int frequency;

	queue<int> frequencies;

	ifstream myfile("SampleData1.txt");
	if (myfile.is_open())
	{
		while (!myfile.eof() && line != "0")
		{
			getline(myfile, line, ','); //get next frequency
			line.erase(0, 1); // remove the space
			frequency = stoi(line, &stringSize);
			if (frequency != 0)
			{
				frequencies.push(frequency); // add to queue
			}
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file";
	}

	OBSTComputationTable table(frequencies);
	table.display();

	int i = 1;
	int j = static_cast<int>(table.getTotalFrequencies());
	LookupTable lookupTable = table.getLookupTable();

	BinaryTree *obst(constructOBST(lookupTable, i, j));

	printPretty(obst, 1, 0, cout);

	system("pause");
}

void displayFrequencies(queue<int> frequencies)
{
	while (!frequencies.empty())
	{
		cout << frequencies.front() << ", ";
		frequencies.pop();
	}
	cout << endl;
}

//row must be initialized to 1
//column must be initialized to the total number of frequencies

BinaryTree *constructOBST(LookupTable &table, int row, int column)
{
	BinaryTree *OBST;
	if (row != column)
	{
		int optimalRoot = table[Key(row, column)].popOptimalRoot();
		//int leftOptimalRoot = table[Key(row, optimalRoot-1)].popOptimalRoot();
		//int rightOptimalRoot = table[Key(optimalRoot+1, column)].popOptimalRoot();
		OBST = new BinaryTree(optimalRoot);
		OBST->left = constructOBST(table, row, optimalRoot - 1);
		OBST->right = constructOBST(table, optimalRoot + 1, column);
	}
	else
	{
		OBST = NULL;
	}
	return OBST;
}
