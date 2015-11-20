#include "OBSTComputationTable.h"
//#include "BinaryTreePrint.h"

void displayFrequencies(queue<int> frequencies);

BinaryTree *constructOBST(LookupTable &table, int row, int column, int level);
double computeStandardDeviationWrapper(BinaryTree *root, int totalFreq);
double computeStandardDeviation(BinaryTree *root);

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
	/*
	int totalFrequencies = static_cast<int>(table->getTotalFrequencies());
	LookupTable lookupTable = table->getLookupTable();
	*/

	BinaryTree *obst1 = table->getOBST();

	printPretty(obst1, 1, 0, cout);

	int worstCase = maxHeight(obst1);
	
	cout << "Sum of frequencies = " << table->getSumOfFrequencies() << endl;

	cout << "Best Case: 1" << endl;
	cout << "Average Case: " << table->getAverageTime() << endl;
	cout << "Worst Case: " << worstCase << endl << endl;

	//double stdDev = computeStandardDeviationWrapper(obst1, totalFrequencies);

	//cout << "Standard Deviation = " << stdDev << endl;



	table->displayNodeInfoWrapper();



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



double computeStandardDeviationWrapper(BinaryTree *root, int totalFreq)
{
	return computeStandardDeviation(root);

}

double computeStandardDeviation(BinaryTree *root)
{
	if (root != NULL)
	{
		return computeStandardDeviation(root->left) + computeStandardDeviation(root->right) + root->eOfX;
	}
	else
	{
		return 0;
	}
	
}