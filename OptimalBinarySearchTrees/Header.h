#include <iostream>
#include <queue>
#include <string>
#include <iomanip>
#include <map>
#include <sstream>
using namespace std;

// Convert an integer value to string
string intToString(int val) {
	ostringstream ss;
	ss << val;
	return ss.str();
}