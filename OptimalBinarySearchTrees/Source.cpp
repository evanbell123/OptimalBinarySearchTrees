#include "OBSTComputationTable.h"
#include "BinaryTreeConstruction.h"

void displayFrequencies(queue<int> frequencies);

BinaryTree *constructOBST(LookupTable &table, int row, int column);
BinaryTree *constructOBSTEquivalent(LookupTable &table, int row, int column);
//vector<BinaryTree*> *constructAllOBST(LookupTable &table, int row, int column);


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

	int row = 1;
	int column = static_cast<int>(table.getTotalFrequencies());
	LookupTable lookupTable = table.getLookupTable();
	/*
	queue<int> test = lookupTable[Key(row, column)].getAllOptimalRoots();
	if (!test.empty())
	{
		test.pop();
	}

	lookupTable[Key(row, column)].setOptimalRoots(test);

	lookupTable[Key(row, column)].print(20);
	*/
	

	queue<int> test = lookupTable[Key(row, column)].getAllOptimalRoots();

	if (!test.empty())
	{
		lookupTable[Key(row, column)].popOptimalRoot();
	}

	lookupTable[Key(row, column)].print(20);

	BinaryTree *obst1 = constructOBST(lookupTable, row, column);
	
	printPretty(obst1, 1, 0, cout);


	//table.display();

	

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
	int optimalRoot = table[Key(row, column)].getOptimalRoot();

	BinaryTree *OBST = new BinaryTree(optimalRoot);
	if (row <= column)
	{
		OBST->left = constructOBST(table, row, optimalRoot - 1);
		OBST->right = constructOBST(table, optimalRoot + 1, column);	
	}
	return OBST;
}

/*
vector<BinaryTree*> *constructAllOBST(LookupTable &table, int row, int column)
{
	vector<BinaryTree*> OBSTs;

	OBSTs.push_back(constructOBST(table, row, column));

	return OBSTs;
}
*/
