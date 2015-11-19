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

	BinaryTree *obst1 = constructOBST(lookupTable, i, j);
	BinaryTree *obst2 = constructOBST(lookupTable, i, j);
	printPretty(obst1, 1, 0, cout);
	printPretty(obst2, 1, 0, cout);

	/*
	BinaryTree *root = new BinaryTree(2);
	root->left = new BinaryTree(1);
	root->right = new BinaryTree(4);
	root->right->left = new BinaryTree(3);
	root->right->right = new BinaryTree(5);

	printPretty(root, 1, 0, cout);
	*/

	

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
	int optimalRoot = table[Key(row, column)].popOptimalRoot();
	BinaryTree *OBST = new BinaryTree(optimalRoot);;
	if (row != column)
	{
		OBST = new BinaryTree(optimalRoot);
		OBST->left = constructOBST(table, row, optimalRoot - 1);
		OBST->right = constructOBST(table, optimalRoot + 1, column);
	}
	return OBST;
}
