
#include "Entry.h"
#include <map>


//#include <string>

typedef pair<int, int> Key;
typedef map<Key, Entry> LookupTable;

class OBSTComputationTable
{
private:
	LookupTable table;
	size_t totalFrequencies;
	double averageTime;
	void clearQueue(queue<int>& q)
	{
		queue<int> empty;
		swap(q, empty);
	}

	double computeAverageTime()
	{
		Entry lastEntry = table[Key(1, static_cast<int>(totalFrequencies))];
		return lastEntry.getMinComparisons() / double(lastEntry.getMinFrequency());
	}

	void computeLookupTable(queue<int>& freq)
	{
		size_t totalFrequencies = freq.size();

		initializeLookupTable(freq);

		// iterators for keeping track of which two entries are being compared
		int nextDiagonal, row, column, i;

		//variables to keep track of minimum values
		int frequency, minFrequency, comparisons, minComparisons;
		queue<int> roots;

		for (nextDiagonal = 2; nextDiagonal <= totalFrequencies; ++nextDiagonal)
		{
			for (column = nextDiagonal, row = 1; column <= totalFrequencies; ++column, ++row)
			{
				//compute first possible frequency for this entry
				minFrequency = table[Key(row + 1, column)].getMinFrequency() + table[Key(row, row)].getMinFrequency();

				//compute the remaining frequencies to determine the minimum frequency for each remaining entry in the diagonal
				for (i = row + 1; i <= column - 1; ++i)
				{
					frequency = table[Key(i + 1, column)].getMinFrequency() + table[Key(row, i)].getMinFrequency();

					if (frequency < minFrequency)
					{
						minFrequency = frequency;
					}
				}
				table[Key(row, column)].setMinFrequency(minFrequency);

				minComparisons = table[Key(row + 1, column)].getMinComparisons() + table[Key(row, row - 1)].getMinComparisons();


				roots.push(row);

				//compute min comparisons
				for (i = row + 1; i <= column; ++i)
				{
					comparisons = table[Key(i + 1, column)].getMinComparisons() + table[Key(row, i - 1)].getMinComparisons();

					if (comparisons == minComparisons)
					{
						roots.push(i);
					}

					if (comparisons < minComparisons)
					{
						clearQueue(roots);
						roots.push(i);
						minComparisons = comparisons;
					}
				}

				minComparisons += table[Key(row, column)].getMinFrequency();

				table[Key(row, column)].setMinComparisons(minComparisons);

				table[Key(row, column)].setOptimalRoots(roots);
				clearQueue(roots);
			}
		}
	}

	void initializeLookupTable(queue<int>& freq)
	{
		//initialize first diagonal
		for (int i = 1, j = 0; i <= totalFrequencies + 1, j <= totalFrequencies; ++i, ++j)
		{
			table.insert(make_pair(Key(i, j), Entry(0, 0)));
		}

		int nextFreq;
		//initialize second diagonal
		for (int i = 1; i <= totalFrequencies; ++i)
		{
			nextFreq = freq.front();
			freq.pop();
			table.insert(make_pair(Key(i, i), Entry(nextFreq, nextFreq, i)));
		}
	}
public:
	OBSTComputationTable(queue<int> frequencies)
	{
		totalFrequencies = frequencies.size();
		computeLookupTable(frequencies);
		averageTime = computeAverageTime();
	}

	size_t getTotalFrequencies()
	{
		return totalFrequencies;
	}

	LookupTable getLookupTable()
	{
		return table;
	}

	void display()
	{
		int width = 15;
		int row, column, nextDiagonal;

		for (nextDiagonal = 1; nextDiagonal <= totalFrequencies; ++nextDiagonal)
		{
			for (row = 1, column = nextDiagonal; column <= totalFrequencies; ++column, ++row)
			{
				cout << setw(width*column) << "|"
					<< "( " << row << ", " << column << " )" << endl;
				table[Key(row, column)].print(width * column);
			}
		}
		cout << endl << "Average Time Complexity = " << setprecision(3) << averageTime << endl;
	}


};