#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class TwoDimentionalMatrix
{
private:
	int x = 1;
	int y = 1;
	vector<vector<double>> matrix;
public:
	TwoDimentionalMatrix(int, int);
	double getElement(int, int);
	int getX();
	int getY();
	void setElement(int, int, double);
	void print();
};

