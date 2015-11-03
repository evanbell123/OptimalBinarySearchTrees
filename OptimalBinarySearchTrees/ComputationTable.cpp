#include "Header.h";
#include "Entry.cpp";


class ComputationTable
{
private:
	vector<vector<Entry>> computationTable;
	map<int, int> numberFrequencyPairs;
	int dimension;
public:

	ComputationTable(map<int, int> numFreqPairs)
	{
		dimension = numFreqPairs.size() + 1;
		numberFrequencyPairs = numFreqPairs;
		setComputationTable();
	}

	//initialize the first two diagonals
	//first diagaonal = gaps
	//second diagonal = num frequency pairs
	void setComputationTable();
};

