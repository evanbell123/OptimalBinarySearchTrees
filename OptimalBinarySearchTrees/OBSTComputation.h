
#include "Header.h"
#include <ctime>

typedef vector<vector<Entry>> LookupTable;

class OBSTComputation
{
private:
	LookupTable table;
	BinaryTree *obst; //optimal binary search tree
	size_t totalFrequencies;
	vector<int> *freqVector;
	unsigned int sumOfFrequencies;
	unsigned int totalNodes; //used to double check correct construction of tree
	double averageCase;
	double eOfXSquared;
	double standardDeviation;
	clock_t begin;
	double timeTaken; // time in seconds taken to complete

	double computeAverageCase()
	{
		Entry lastEntry = table[0][totalFrequencies];
		return lastEntry.getMinComparisons() / double(lastEntry.getMinFrequency());
	}

	void computeLookupTable()
	{
		initializeLookupTable();

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

	void initializeLookupTable()
	{
		unsigned int row, frequency;

		for (row = 0; row < totalFrequencies; ++row) // n
		{
			frequency = freqVector->at(row);
			sumOfFrequencies += frequency; //keep track of sum of frequencies
			vector<Entry> newRow;
			newRow.emplace_back(Entry()); //initialize first diagonal
			newRow.emplace_back(Entry(frequency, frequency, row + 1)); //initialize second diagonal
			table.push_back(newRow);
		}
		vector<Entry> lastRow;
		lastRow.emplace_back(Entry());
		table.push_back(lastRow);
	}

	BinaryTree *constructOBSTWrapper()
	{
		return constructOBST(0, static_cast<int>(totalFrequencies), 1);
	}

	//row must be initialized to 0
	//column must be initialized to the total number of frequencies
	//level must be initialized to 1
	BinaryTree *constructOBST(int  row, int column, int level)
	{
		BinaryTree *root = new BinaryTree(level);
		int i = row + 1; //minimum optimal root
		int j = column + row; // maximum optimal root
		if (column != 0 && j <= totalFrequencies)
		{
			Entry *entry = &table[row][column];
			int optimalRoot = entry->getOptimalRoot();
			int freq = entry->getMinFrequency();

			root->setFreq(freq);
			root->setKey(optimalRoot);

			totalNodes++;

			eOfXSquared += ((level*level*freqVector->at(optimalRoot - 1)) / double(sumOfFrequencies));

			root->left = constructOBST(row, abs(optimalRoot - i), level + 1);
			
			if (optimalRoot == j)
			{
				root->right = new BinaryTree(level + 1);
			}
			else if (optimalRoot == i)
			{
				root->right = constructOBST(row + 1, column - 1, level + 1);
			}
			else
			{
				root->right = constructOBST(optimalRoot, abs(optimalRoot - j), level + 1);
			}
		}
		return root;
	}
public:
	OBSTComputation(vector<int> *frequencies)
	{
		begin = clock();
		freqVector = frequencies;
		totalFrequencies = frequencies->size();
		totalNodes = 0;
		sumOfFrequencies = 0;
		eOfXSquared = 0;

		computeLookupTable();
		averageCase = computeAverageCase();
		obst = constructOBSTWrapper();

		standardDeviation = sqrt(eOfXSquared - (averageCase*averageCase));
		timeTaken = (clock() - begin) / (double)CLOCKS_PER_SEC;
	}

	~OBSTComputation()
	{
		delete obst;
		delete freqVector;
	}

	BinaryTree *getOBST()
	{
		return obst;
	}

	unsigned int getTotalNodes()
	{
		return totalNodes;
	}

	double getTimeTaken()
	{
		return timeTaken;
	}

	double getAverageTime()
	{
		return averageCase;
	}

	double getStandardDeviation()
	{
		return standardDeviation;
	}

	double getEOfXSquared()
	{
		return eOfXSquared;
	}

	unsigned int getSumOfFrequencies()
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
		cout << (clock() - begin) / (double)CLOCKS_PER_SEC << setw(30) << setiosflags(ios::right) << message << endl;
	}

};