#include "Header.h";
#include "Entry.cpp";

int main()
{
	vector<vector<int> > buff;

	for (int i = 0; i < 10; i++)
	{
		vector<int> temp; // create an array, don't work directly on buff yet.
		for (int j = 0; j < 10; j++)
			temp.push_back(i);

		buff.push_back(temp); // Store the array in the buffer
	}

	for (int i = 0; i < buff.size(); ++i)
	{
		for (int j = 0; j < buff[i].size(); ++j)
			cout << buff[i][j];
		cout << endl;
	}

	return 0;
}