#include "OBSTComputation.h"
#include <fstream>
#include <cstring>
#include <math.h>


vector<int> *readFrequencies(string fileName);

void displayOBSTInfo(OBSTComputation *obstComp);
void displayFrequencies(vector<int> *frequencies);
void displayQueue(queue<int> q);

queue<int> levelOrderTraversalWrapper(BinaryTree *root, int maxElements);
void levelOrderTraversal(BinaryTree *root, queue<int> &traversal, int level);

/*
The following functions are used to print a binary tree.
I didn't write printPretty, printBracnches, printNodes, printLeaves, or maxHeight
I used this code for fun.
http://articles.leetcode.com/2010/09/how-to-pretty-print-binary-tree.html
*/
void printPretty(BinaryTree *root, int level, int indentSpace, ostream& out); //printPretty(obst, 1, 0, cout);
// Print the arm branches (eg, /    \ ) on a line
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<BinaryTree*>& nodesQueue, ostream& out);
// Print the branches and node (eg, ___10___ )
void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<BinaryTree*>& nodesQueue, ostream& out);
// Print the leaves only (just for the bottom row)
void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<BinaryTree*>& nodesQueue, ostream& out);

int maxHeight(BinaryTree *p);

void main()
{

	//vector<vector<int>*> *datasets;
	//vector<int> *frequencies;

	//datasets = new vector<vector<int>*>;
	//frequencies = new vector<int>;

	vector<OBSTComputation*> *obstComputationVector;
	//OBSTComputation *obstComputation;

	obstComputationVector = new vector<OBSTComputation*>;

	string fileName = "dataset";
	string fileExt = ".txt";
	string fullFileName;

	for (int i = 0; i < 6; i++)
	{
		fullFileName = fileName + intToString(i+1) + fileExt;
		//obstComputation = new OBSTComputation(readFrequencies(fullFileName));
		obstComputationVector->push_back(new OBSTComputation(readFrequencies(fullFileName)));
	}

	//delete obstComputation;

	for (int i = 0; i < 6; i++)
	{
		cout << fileName + intToString(i + 1) + fileExt << endl;
		displayOBSTInfo(obstComputationVector->at(i));
		cout << endl;

		delete obstComputationVector->at(i);
	}

	delete obstComputationVector;

	system("pause");


}

void displayOBSTInfo(OBSTComputation *obstComp)
{
	BinaryTree *obst = obstComp->getOBST();
	double timeTaken = obstComp->getTimeTaken();
	double averageCase = obstComp->getAverageTime();
	int worstCase = maxHeight(obst) - 1;
	double stdDev = obstComp->getStandardDeviation();
	double eOfXSquared = obstComp->getEOfXSquared();
	queue<int> inorderTraversal = levelOrderTraversalWrapper(obst, 7);

	cout << "Level Order Traversal: ";
	displayQueue(inorderTraversal);
	cout << "Program completed in " << timeTaken << " seconds" << endl
		<< "Total Frequencies: " << obstComp->getTotalFrequencies() << endl
		<< "Best Case: 1" << endl
		<< "Average Case: " << setprecision(3) << averageCase << endl
		<< "Worst Case: " << worstCase << endl
		<< "E[X^2] = " << eOfXSquared << endl
		<< "Standard Deviation: " << stdDev << endl
		<< "Sum of Frequencies: " << obstComp->getSumOfFrequencies() << endl;
}

vector<int> *readFrequencies(string fileName)
{
	ifstream inFile(fileName); //the first character in the file must be a space
	string line;
	size_t stringSize;
	vector<int> *freqVector = new vector<int>;
	int frequency;
	if (inFile.is_open())
	{
		while (!inFile.eof() && line != "0")
		{
			getline(inFile, line, ','); //get next frequency
			line.erase(0, 1); // remove the space
			frequency = stoi(line, &stringSize);
			if (freqVector != 0)
			{
				freqVector->push_back(frequency); // add to queue
			}
		}
		inFile.close();
	}
	else
	{
		cout << "Unable to open file";
	}
	return freqVector;
}

void displayFrequencies(vector<int> *frequencies)
{
	for (int i = 0; i < frequencies->size(); i++)
	{
		cout << frequencies->at(i) << ", ";
	}
	cout << endl;
}

void displayQueue(queue<int> q)
{
	while (!q.empty())
	{
		cout << q.front() << ", ";
		q.pop();
	}
	cout << endl;
}

queue<int> levelOrderTraversalWrapper(BinaryTree *root, int maxElements)
{
	queue<int> traversal;
	int level = 1;
	while (traversal.size() < maxElements)
	{
		levelOrderTraversal(root, traversal, level);
		level++;
	}
	return traversal;
}

void levelOrderTraversal(BinaryTree *root, queue<int> &traversal, int level)
{
	if (root == NULL)
	{
		return;
	}
	if (level == 1)
	{
		traversal.push(root->key);
	}
	else
	{
		levelOrderTraversal(root->left, traversal, level - 1);
		levelOrderTraversal(root->right, traversal, level - 1);
	}
}


// Find the maximum height of the binary tree
int maxHeight(BinaryTree *p) {
	if (!p) return 0;
	int leftHeight = maxHeight(p->left);
	int rightHeight = maxHeight(p->right);
	return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}


// Print the arm branches (eg, /    \ ) on a line
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<BinaryTree*>& nodesQueue, ostream& out) {
	deque<BinaryTree*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel / 2; i++) {
		out << ((i == 0) ? setw(startLen - 1) : setw(nodeSpaceLen - 2)) << "" << ((*iter++) ? "/" : " ");
		out << setw(2 * branchLen + 2) << "" << ((*iter++) ? "\\" : " ");
	}
	out << endl;
}

// Print the branches and node (eg, ___10___ )
void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<BinaryTree*>& nodesQueue, ostream& out) {
	deque<BinaryTree*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel; i++, iter++) {
		out << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left) ? setfill('_') : setfill(' '));
		out << setw(branchLen + 2) << ((*iter) ? intToString((*iter)->key) : "");
		out << ((*iter && (*iter)->right) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
	}
	out << endl;
}

// Print the leaves only (just for the bottom row)
void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<BinaryTree*>& nodesQueue, ostream& out) {
	deque<BinaryTree*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel; i++, iter++) {
		out << ((i == 0) ? setw(indentSpace + 2) : setw(2 * level + 2)) << ((*iter) ? intToString((*iter)->key) : "");
	}
	out << endl;
}

// Pretty formatting of a binary tree to the output stream
// @ param
// level  Control how wide you want the tree to sparse (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes)
// indentSpace  Change this to add some indent space to the left (eg, indentSpace of 0 means the lowest level of the left node will stick to the left margin)
void printPretty(BinaryTree *root, int level, int indentSpace, ostream& out) {
	int h = maxHeight(root);
	int nodesInThisLevel = 1;

	int branchLen = 2 * ((int)pow(2.0, h) - 1) - (3 - level)*(int)pow(2.0, h - 1);  // eq of the length of branch for each node of each level
	int nodeSpaceLen = 2 + (level + 1)*(int)pow(2.0, h);  // distance between left neighbor node's right arm and right neighbor node's left arm
	int startLen = branchLen + (3 - level) + indentSpace;  // starting space to the first node to print of each level (for the left most node of each level only)

	deque<BinaryTree*> nodesQueue;
	nodesQueue.push_back(root);
	for (int r = 1; r < h; r++) {
		printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
		branchLen = branchLen / 2 - 1;
		nodeSpaceLen = nodeSpaceLen / 2 + 1;
		startLen = branchLen + (3 - level) + indentSpace;
		printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);

		for (int i = 0; i < nodesInThisLevel; i++) {
			BinaryTree *currNode = nodesQueue.front();
			nodesQueue.pop_front();
			if (currNode) {
				nodesQueue.push_back(currNode->left);
				nodesQueue.push_back(currNode->right);
			}
			else {
				nodesQueue.push_back(NULL);
				nodesQueue.push_back(NULL);
			}
		}
		nodesInThisLevel *= 2;
	}
	printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
	printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue, out);
}