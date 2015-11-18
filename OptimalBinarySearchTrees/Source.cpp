
#include "OBSTComputationTable.cpp"
#include "Node.cpp"

#include <fstream>

void displayFrequencies(queue<int> frequencies);

Node *constructOBST(LookupTable &table, int row, int column);

void main()
{
	string line;
	size_t stringSize;
	int frequency;

	queue<int> frequencies;

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
				frequencies.push(frequency); // add to queue
			}
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file";
	}

	OBSTComputationTable table(frequencies);
	table.display();

	int i = 1;
	int j = static_cast<int>(table.getTotalFrequencies());
	LookupTable lookupTable = table.getLookupTable();

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

//row must be initialized to 1
//column must be initialized to the total number of frequencies
Node *constructOBST(LookupTable &table, int row, int column)
{
	if (row != column)
	{
		return constructOBST(table, row - 1, column);
	}
}