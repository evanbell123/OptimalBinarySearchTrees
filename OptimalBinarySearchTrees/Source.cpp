#include "OBSTComputationTable.h"
#include "BinaryTreePrint.h"

void displayFrequencies(queue<int> frequencies);

BinaryTree *constructOBST(LookupTable &table, int row, int column, int level);
void displayNodeInfo(BinaryTree *root);

void main()
{
	string line;
	size_t stringSize;
	int frequency;

	queue<int> *frequencies = new queue<int>;

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
				frequencies->push(frequency); // add to queue
			}
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file";
	}

	OBSTComputationTable *table = new OBSTComputationTable(frequencies);
	//table.display();

	int totalFrequencies = static_cast<int>(table->getTotalFrequencies());
	LookupTable lookupTable = table->getLookupTable();

	BinaryTree *obst1 = constructOBST(lookupTable, 1, totalFrequencies, 1);

	printPretty(obst1, 1, 0, cout);

	int worstCase = maxHeight(obst1);

	cout << "Sum of frequencies = " << table->getSumOfFrequencies() << endl;

	cout << "Best Case: 1" << endl;
	cout << "Average Case: " << table->getAverageTime() << endl;
	cout << "Worst Case: " << worstCase << endl;

	displayNodeInfo(obst1);



	system("pause");
}


void displayNodeInfo(BinaryTree *root)
{
	int key = root->key;
	if (key > -1)
	{
		cout << key << "   " << root->freq << "   " << root->level << endl;
		displayNodeInfo(root->left);
		displayNodeInfo(root->right);
	}
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
//level must be initialized to 1
BinaryTree *constructOBST(LookupTable &table, int  row, int column, int level)
{
	int optimalRoot = table[Key(row, column)].getOptimalRoot();
	int freq = table[Key(row, column)].getMinFrequency();
	BinaryTree *OBST = new BinaryTree(optimalRoot, freq, level);

	if (row <= column)
	{
		OBST->left = constructOBST(table, row, optimalRoot - 1, level+1);
		OBST->right = constructOBST(table, optimalRoot + 1, column, level+1);	
	}
	return OBST;
}

