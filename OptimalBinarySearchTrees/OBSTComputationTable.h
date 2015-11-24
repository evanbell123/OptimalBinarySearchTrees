
#include "Header.h"
#include <ctime>

//typedef pair<int, int> Key;
//typedef map<Key, Entry> LookupTable;
typedef vector<vector<Entry>> LookupTable;

class OBSTComputationTable
{
private:
	LookupTable table;
	BinaryTree *obst; //optimal binary search tree
	int totalFrequencies;
	int sumOfFrequencies;
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
		return lastEntry.getMinComparisons() / lastEntry.getMinFrequency();
	}

	void computeLookupTable(vector<int> *freqVector)
	{
		initializeLookupTable(freqVector);

		int diagonal, row, i;
		int freq, comparisons, minComparisons;
		queue<int> roots;

		for (diagonal = 2; diagonal <= totalFrequencies; ++diagonal)
		{
			for (row = 0; row <= totalFrequencies - diagonal; ++row)
			{
				Entry E1 = table[row + 1][diagonal - 1];
				freq = table[row][1].getMinFrequency() + E1.getMinFrequency();
				minComparisons = table[row][0].getMinComparisons() + E1.getMinComparisons();
				roots.push(row + 1);


				for (i = 2; i <= diagonal; ++i)
				{
					comparisons = table[row][i - 1].getMinComparisons() + table[row + i][diagonal - i].getMinComparisons();
					if (comparisons == minComparisons)
					{
						roots.push(row + i);
					}
					if (comparisons < minComparisons)
					{
						clearQueue(roots);
						roots.push(row + i);
						minComparisons = comparisons;
					}


				}
				minComparisons += freq;
				table[row].push_back(Entry(freq, minComparisons, roots));
				clearQueue(roots);
			}

			timeMarker("Computed diagonal # " + intToString(diagonal));
		}

	}

	void initializeLookupTable(vector<int> *freq)
	{
		//vector<Entry> newRow;
		int row, frequency;

		for (row = 0; row < totalFrequencies; ++row)
		{
			frequency = freq->at(row);
			//keep track of sum of frequencies
			sumOfFrequencies += frequency;

			vector<Entry> newRow;

			//initialize first diagonal
			newRow.emplace_back(Entry(0, 0, 0));

			//initialize second diagonal
			newRow.emplace_back(Entry(frequency, frequency, row + 1));

			table.push_back(newRow);
		}
		vector<Entry> lastRow;
		lastRow.emplace_back(Entry(0, 0, 0));
		table.push_back(lastRow);

	}

	//row must be initialized to 0
	//column must be initialized to the total number of frequencies
	//level must be initialized to 1
	BinaryTree *constructOBST(int  row, int column, int level)
	{
		int optimalRoot = table[row][column].getOptimalRoot();
		int freq = table[row][column].getMinFrequency();
		BinaryTree *OBST = new BinaryTree(optimalRoot, freq, level);

		if (column != 1) 
		{
			OBST->left = constructOBST(row, abs(optimalRoot - row - 1), level + 1);
			OBST->right = constructOBST(optimalRoot, abs(optimalRoot - column), level + 1);
		}

		return OBST;
	}
public:
	OBSTComputationTable(vector<int> *frequencies)
	{
		start = clock();
		totalFrequencies = static_cast<int>(frequencies->size());
		sumOfFrequencies = 0;
		computeLookupTable(frequencies);
		averageTime = computeAverageTime();
		obst = constructOBST(0, static_cast<int>(totalFrequencies), 1);
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

	size_t getTotalFrequencies()
	{
		return totalFrequencies;
	}

	LookupTable getLookupTable()
	{
		return table;
	}

	void displayTable()
	{
		int row, column;
		int width = 10;
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
		cout << setw(width) << "Key" << setw(width) << "Freq" << setw(width) << "Level" << setw(width) << "E[X^2]" << setw(width) << endl;

		displayNodeInfo(obst, width);
	}

	void displayNodeInfo(BinaryTree *root, int width)
	{
		int key = root->key;
		if (key > -1)
		{
			cout << root->key << setw(width) << root->freq << setw(width) << root->level << setw(width) << root->eOfXSquared << setw(width) << endl;
			displayNodeInfo(root->left, width);
			displayNodeInfo(root->right, width);
		}
	}

	void timeMarker(string message)
	{
		cout << (clock() - start) / (double)CLOCKS_PER_SEC << setw(30) << setiosflags(ios::right) << message << endl;
	}

};