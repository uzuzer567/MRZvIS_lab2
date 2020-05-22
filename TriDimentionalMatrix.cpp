#include "pch.h"
#include "TriDimentionalMatrix.h"

TriDimentionalMatrix::TriDimentionalMatrix(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	matrix.resize(x, vector<vector<double>>(y, vector<double>(z, 0)));
}

double TriDimentionalMatrix::getElement(int x, int y, int z)
{
	return matrix[x][y][z];
}

int TriDimentionalMatrix::getX()
{
	return x;
}

int TriDimentionalMatrix::getY()
{
	return y;
}

int TriDimentionalMatrix::getZ()
{
	return z;
}

void TriDimentionalMatrix::setElement(int x, int y, int z, double value)
{
	matrix[x][y][z] = value;
}

void TriDimentionalMatrix::print()
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			for (int k = 0; k < z; k++)
			{
				cout << fixed << setprecision(3) << "[" << i << "][" << j << "][" << k << "] == " << getElement(i, j, k) << ";     \t";
				if (k % 3 == 0)
				{
					cout << endl;
				}
			}
		}
		cout << endl;
	}
}
