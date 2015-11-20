#include "OBSTComputationTable.h"
#include "BinaryTreePrint.h"

void displayFrequencies(queue<int> frequencies);

BinaryTree *constructOBST(LookupTable &table, int row, int column, int level, double stdDev);
void displayNodeInfo(BinaryTree *root);
double computeStandardDeviationWrapper(BinaryTree *root, int totalNodes);
double computeStandardDeviation(BinaryTree *root);


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

	double stdDev = 0;

	BinaryTree *obst1 = constructOBST(lookupTable, 1, totalFrequencies, 1, stdDev);

	stdDev /= totalFrequencies;

	
	
	printPretty(obst1, 1, 0, cout);

	cout << "Standard Deviation: " << stdDev << endl;

	int worstCase = maxHeight(obst1);

	cout << "Best Case: 1" << endl;
	cout << "Average Case: " << table->getAverageTime() << endl;
	cout << "Worst Case: " << worstCase << endl;

	displayNodeInfo(obst1);



	system("pause");
}



double computeStandardDeviationWrapper(BinaryTree *root, int totalFrequencies)
{
	double calculation = computeStandardDeviation(root);

	return calculation / totalFrequencies;
}

double computeStandardDeviation(BinaryTree *root)
{
	return 0;
}


void displayNodeInfo(BinaryTree *root)
{
	int key = root->key;
	if (key > -1)
	{
		cout << key << "   " << root->data << "   " << root->level << endl;
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
BinaryTree *constructOBST(LookupTable &table, int  row, int column, int level, double stdDev)
{
	int optimalRoot = table[Key(row, column)].getOptimalRoot();
	int freq = table[Key(row, column)].getMinFrequency();

	

	BinaryTree *OBST = new BinaryTree(optimalRoot, freq, level);

	if (freq <= 0)
	{
		return OBST;
	}

	if (level <= 1)
	{
		stdDev += freq;
	}
	else
	{
		stdDev += (level*(level - 1)*freq);
	}

	if (row <= column)
	{
		OBST->left = constructOBST(table, row, optimalRoot - 1, level+1, stdDev);
		OBST->right = constructOBST(table, optimalRoot + 1, column, level+1, stdDev);	
	}
	return OBST;
}

