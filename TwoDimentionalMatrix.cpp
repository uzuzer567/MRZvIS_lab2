#include "pch.h"
#include "TwoDimentionalMatrix.h"

TwoDimentionalMatrix::TwoDimentionalMatrix(int x, int y)
{
	this->x = x;
	this->y = y;
	matrix.resize(x, vector<double>(y, 0));
}

double TwoDimentionalMatrix::getElement(int x, int y)
{
	return matrix[x][y];
}

int TwoDimentionalMatrix::getX()
{
	return x;
}

int TwoDimentionalMatrix::getY()
{
	return y;
}

void TwoDimentionalMatrix::setElement(int x, int y, double value)
{
	matrix[x][y] = value;
}

void TwoDimentionalMatrix::print()
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			cout << fixed << setprecision(3) << "[" << i << "][" << j << "] == " << getElement(i, j) << ";   \t";
		}
		cout << endl;
	}
}
