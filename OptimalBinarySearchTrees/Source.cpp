#include "Entry.cpp"
#include <map>
#include <fstream>
#include <sstream>
#include <stack>


typedef pair<int, int> Key;
typedef map<Key, Entry> LookupTable;

void clearQueue(queue<int>& q);
void computeLookupTable(LookupTable& table, queue<int>& freq);
void initializeLookupTable(LookupTable& table, queue<int>& freq, size_t totalFreq);
void displayLookupTable(LookupTable& table, size_t totalFreq);

void displayFrequencies(queue<int> frequencies);

void main()
{
	LookupTable table;



	string line;
	size_t stringSize;

	queue<int> frequencies;

	ifstream myfile("SampleData1.txt");
	if (myfile.is_open())
	{
		while (!myfile.eof() && line != "0")
		{
			//frequencyLists.push(new vector<int>);
			getline(myfile, line, ','); //get next frequency
			line.erase(0, 1); // remove the space
			if (line != "0")
			{
				frequencies.push(stoi(line, &stringSize)); // add to queue
			}
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file";
	}

	size_t totalFrequencies = frequencies.size();

	displayFrequencies(frequencies);

	computeLookupTable(table, frequencies);

	displayLookupTable(table, totalFrequencies);



	system("pause");
}

void clearQueue(queue<int> &q)
{
	queue<int> empty;
	swap(q, empty);
}

void computeLookupTable(LookupTable& table, queue<int>& freq)
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
		}
	}


}

void initializeLookupTable(LookupTable& table, queue<int>& freq, size_t totalFreq)
{
	//initialize first diagonal
	for (int i = 1, j = 0; i <= totalFreq + 1, j <= totalFreq; ++i, ++j)
	{
		table.insert(make_pair(Key(i, j), Entry(0, 0)));
	}

	int nextFreq;
	//initialize second diagonal
	for (int i = 1; i <= totalFreq; ++i)
	{
		nextFreq = freq.front();
		freq.pop();
		table.insert(make_pair(Key(i, i), Entry(nextFreq, nextFreq, i)));
	}
}

void displayLookupTable(LookupTable& table, size_t totalFreq)
{
	int width = 10;
	int row, column;
	cout << '|';
	for (row = 1; row <= totalFreq; ++row)
	{
		for (column = row; column <= totalFreq; ++column)
		{
			cout << "( " << row << ", " << column << " )" << setw(width+2) << "|";
		}
		cout << endl;
		cout << '|' << setw(2*row*width) << '|';
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