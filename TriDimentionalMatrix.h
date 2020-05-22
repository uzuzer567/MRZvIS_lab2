#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class TriDimentionalMatrix
{
private:
	int x = 1;
	int y = 1;
	int z = 1;
	vector<vector<vector<double>>> matrix;
public:
	TriDimentionalMatrix(int, int, int);
	double getElement(int, int, int);
	int getX();
	int getY();
	int getZ();
	void setElement(int, int, int, double);
	void print();
};

