
#include "Header.h"
#include <ctime>

typedef vector<vector<Entry>> LookupTable;

class OBSTComputationTable
{
private:
	LookupTable table;
	BinaryTree *obst; //optimal binary search tree
	unsigned int totalFrequencies;
	unsigned int sumOfFrequencies;
	double averageTime;
	clock_t start;

	void clearQueue(queue<int>& q)
	{
		queue<int> empty;
		swap(q, empty);
	}

	double computeAverageTime()
	{
		Entry lastEntry = table[0][totalFrequencies];
		return lastEntry.getMinComparisons() / double(lastEntry.getMinFrequency());
	}

	void computeLookupTable(vector<int> *freqVector)
	{
		initializeLookupTable(freqVector);

		unsigned int diagonal, row, i;
		unsigned int freq, comparisons, minComparisons, root;

		for (diagonal = 2; diagonal <= totalFrequencies; ++diagonal)
		{
			for (row = 0; row <= totalFrequencies - diagonal; ++row)
			{
				Entry E1 = table[row + 1][diagonal - 1];
				freq = table[row][1].getMinFrequency() + E1.getMinFrequency();
				minComparisons = table[row][0].getMinComparisons() + E1.getMinComparisons();
				root = row + 1;


				for (i = 2; i <= diagonal; ++i)
				{
					comparisons = table[row][i - 1].getMinComparisons() + table[row + i][diagonal - i].getMinComparisons();
					if (comparisons < minComparisons)
					{
						root = row + i;
						minComparisons = comparisons;
					}


				}
				minComparisons += freq;
				table[row].push_back(Entry(freq, minComparisons, root));
			}

			timeMarker("Computed diagonal # " + intToString(diagonal));
		}

	}

	void initializeLookupTable(vector<int> *freq)
	{
		//vector<Entry> newRow;
		unsigned int row, frequency;

		for (row = 0; row < totalFrequencies; ++row)
		{
			frequency = freq->at(row);
			//keep track of sum of frequencies
			sumOfFrequencies += frequency;

			vector<Entry> newRow;

			//initialize first diagonal
			newRow.emplace_back(Entry());

			//initialize second diagonal
			newRow.emplace_back(Entry(frequency, frequency, row + 1));

			table.push_back(newRow);
		}
		vector<Entry> lastRow;
		lastRow.emplace_back(Entry());
		table.push_back(lastRow);

	}

	BinaryTree *constructOBSTWrapper()
	{
		int width = 15;
		cout << setw(width) << "Row" << setw(width) << "Column" << setw(width) << "Root" << endl;
		return constructOBST(0, totalFrequencies, 1);
	}

	//row must be initialized to 0
	//column must be initialized to the total number of frequencies
	//level must be initialized to 1
	BinaryTree *constructOBST(int  row, int column, int level)
	{
		cout << setw(15) << row << setw(15) << column;
		int i = row + 1;
		int j = column + row;
		BinaryTree *root = new BinaryTree(level);
		if (column != 0 && j <= totalFrequencies)
		{
			Entry *entry = &table[row][column];
			int optimalRoot = entry->getOptimalRoot();
			int freq = entry->getMinFrequency();

			root->setFreq(freq);
			root->setKey(optimalRoot);

			cout << setw(15) << optimalRoot << endl;

			i = row + 1;
			j = column + row;
			
			
			root->left = constructOBST(row, abs(optimalRoot - i), level + 1);
			if (optimalRoot == j)
			{

				//root->left = constructOBST(row, column - 1, level + 1);
				root->right = new BinaryTree(level + 1);
			}
			else if (optimalRoot == i)
			{
				//root->left = new BinaryTree(level + 1);
				root->right = constructOBST(row + 1, column, level + 1);
			}
			else
			{
				//root->left = constructOBST(row, abs(optimalRoot - row - 1), level + 1);
				if (row > column)
				{
					root->right = constructOBST(optimalRoot, abs(optimalRoot - i), level + 1);
				}
				else
				{
					root->right = constructOBST(optimalRoot, abs(optimalRoot - j), level + 1);
				}
			}
			
			cout << endl;

		}

		return root;
	}
public:
	OBSTComputationTable(vector<int> *frequencies)
	{
		start = clock();
		totalFrequencies = static_cast<int>(frequencies->size());
		sumOfFrequencies = 0;
		computeLookupTable(frequencies);
		averageTime = computeAverageTime();
		obst = constructOBSTWrapper();
	}

	~OBSTComputationTable()
	{
		delete obst;
	}

	BinaryTree *getOBST()
	{
		return obst;
	}

	double getAverageTime()
	{
		return averageTime;
	}

	int getSumOfFrequencies()
	{
		return sumOfFrequencies;
	}

	int getTotalFrequencies()
	{
		return totalFrequencies;
	}

	LookupTable getLookupTable()
	{
		return table;
	}

	void displayTable()
	{
		unsigned int row, column;
		unsigned int width = 10;
		for (row = 0; row <= totalFrequencies; ++row)
		{
			for (column = 0; column < table[row].size(); ++column)
			{
				cout << setw(width) << "( " << row << ", " << column << " )" << endl;
				table[row][column].print(10);
			}
		}
	}

	void displayNodeInfoWrapper()
	{
		int width = 15;
		cout << setw(width) << "Key" << setw(width) << "Freq" << setw(width) << "Level" << setw(width) << endl;

		displayNodeInfo(obst, width);
	}

	void displayNodeInfo(BinaryTree *root, int width)
	{
		if (root->key != -1)
		{
			cout << root->key << setw(width) << root->freq << setw(width) << root->level << setw(width) << endl;
			displayNodeInfo(root->left, width);
			displayNodeInfo(root->right, width);
		}
	}

	void timeMarker(string message)
	{
		cout << (clock() - start) / (double)CLOCKS_PER_SEC << setw(30) << setiosflags(ios::right) << message << endl;
	}

};