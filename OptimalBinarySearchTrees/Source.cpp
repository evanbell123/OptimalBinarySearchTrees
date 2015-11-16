#include "Entry.cpp"
#include <map>


typedef pair<int, int> Key;
typedef map<Key, Entry> LookupTable;

void clearQueue(queue<int>& q);

void computeLookupTable(LookupTable& table, vector<int> freq);
void initializeLookupTable(LookupTable& table, vector<int> freq, size_t totalFreq);
void displayLookupTable(LookupTable& table, size_t totalFreq);

void main()
{
	vector<int> freq1 = { 6,4,2,6,4 };
	vector<int> freq2 = { 19,15,11,20,13,15 };

	LookupTable table;

	computeLookupTable(table, freq1);

	displayLookupTable(table, freq1.size());

	system("pause");
}

void clearQueue(queue<int> &q)
{
	queue<int> empty;
	swap(q, empty);
}

void computeLookupTable(LookupTable& table, vector<int> freq)
{
	size_t totalFrequencies = freq.size();

	initializeLookupTable(table, freq, totalFrequencies);

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

			//cout << "( " << row << ", " << column << " )" << endl;
			//table[Key(row, column)].print();

		}
		//cout << endl;
	}


}

void initializeLookupTable(LookupTable& table, vector<int> freq, size_t totalFreq)
{
	//initialize first diagonal
	for (int i = 1, j = 0; i <= totalFreq + 1, j <= totalFreq; ++i, ++j)
	{
		table.insert(make_pair(Key(i, j), Entry(0, 0)));
	}

	//initialize second diagonal
	for (int i = 1; i <= totalFreq; ++i)
	{
		table.insert(make_pair(Key(i, i), Entry(freq[i - 1], freq[i - 1], i)));
	}
}

void displayLookupTable(LookupTable& table, size_t totalFreq)
{
	int width = 15;
	int row, column, nextDiagonal;

	for (nextDiagonal = 1; nextDiagonal <= totalFreq; ++nextDiagonal)
	{
		for (row = 1, column = nextDiagonal; column <= totalFreq; ++column, ++row)
		{
			cout << setw(width*column)
				<< "|( " << row << ", " << column << " )" << endl;
			table[Key(row, column)].print(width * column);
		}
		//cout << endl;
	}
}