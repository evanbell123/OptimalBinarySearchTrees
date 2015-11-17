
#include "OBSTComputationTable.cpp"

#include <fstream>

void displayFrequencies(queue<int> frequencies);

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