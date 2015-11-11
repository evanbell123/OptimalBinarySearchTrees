
#include "Entry.cpp"
#include <map>

void main()
{
	int frequencies[] = { 6,4,2,6,4 };

	typedef pair<int, int> Key;
	typedef map<Key, Entry> ComputationTable;

	
	ComputationTable table;

	for (int i = 1; i <= 5; i++)
	{
		cout << "( " << i << ", " << i << " )" << endl;
		table.insert(make_pair(Key(i, i), Entry(frequencies[i-1])));
		table[pair<int, int>(i,i)].print();
	}

	system("pause");
}