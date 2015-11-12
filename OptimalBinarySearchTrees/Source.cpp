
#include "Entry.cpp"
#include <map>

typedef pair<int, int> Key;
typedef map<Key, Entry> ComputationTable;

void initializeComputationTable(ComputationTable& table, int freq[]);

void main()
{
	int freq[] = { 6,4,2,6,4 };

	ComputationTable table;

	initializeComputationTable(table, freq);

	int nextDiagonal, row, column, i; // iterators
	int frequency, minFrequency, comparisons, minComparisons;

	for (nextDiagonal = 2; nextDiagonal <= 5; ++nextDiagonal)
	{
		//cout << "Next Diagonal" << endl << endl;
		for (column = nextDiagonal, row = 1; column <= 5; ++column, ++row)
		{
			cout << "( " << row << ", " << column << " )" << endl;

			/*
			cout << "( " << row + 1 << ", " << column << " )"
				<< "( " << row << ", " << row << " )" << endl << endl;
				*/

				//compute first possible frequency for this entry
			minFrequency = table[Key(row + 1, column)].getMinFrequency() + table[Key(row, row)].getMinFrequency();

			//compute the remaining frequencies to determine the minimum frequency for each remaining entry in the diagonal
			for (i = row + 1; i <= column - 1; ++i)
			{
				/*
				cout << "( " << i + 1 << ", " << column << " )"
					<< "( " << row << ", " << i << " )" << endl;
					*/
				frequency = table[Key(i + 1, column)].getMinFrequency() + table[Key(row, i)].getMinFrequency();

				if (frequency < minFrequency)
				{
					minFrequency = frequency;
				}
			}
			table[Key(row, column)].setMinFrequency(minFrequency);

			cout << "( " << row + 1 << ", " << column << " )"
				<< "( " << row << ", " << row - 1 << " )" << endl;
			minComparisons = table[Key(row + 1, column)].getMinComparisons() + table[Key(row, row - 1)].getMinComparisons();
			//compute min comparisons
			for (i = row + 1; i <= column; ++i)
			{
				cout << "( " << i + 1 << ", " << column << " )"
					<< "( " << row << ", " << i - 1 << " )" << endl;
				comparisons = table[Key(i + 1, column)].getMinComparisons() + table[Key(row, i - 1)].getMinComparisons();
				if (comparisons < minComparisons)
				{
					minComparisons = comparisons;
				}
			}

			minComparisons += table[Key(row, column)].getMinFrequency();

			table[Key(row, column)].setMinComparisons(minComparisons);

			table[Key(row, column)].print();
			cout << endl;
		}
		//cout << endl;
	}




	system("pause");
}

void initializeComputationTable(ComputationTable& table, int freq[])
{
	//initialize first diagonal
	for (int i = 1, j = 0; i <= 6, j <= 5; ++i, ++j)
	{
		//cout << "( " << i << ", " << j << " )" << endl;
		table.insert(make_pair(Key(i, j), Entry(0, 0)));
		//table[Key(i, j)].print();
	}

	//initialize second diagonal
	for (int i = 1; i <= 5; ++i)
	{
		//cout << "( " << i << ", " << i << " )" << endl;
		table.insert(make_pair(Key(i, i), Entry(freq[i - 1], freq[i - 1], i)));
		//table[Key(i, i)].print();
	}
}