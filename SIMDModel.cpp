#include "pch.h"
#include "SIMDModel.h"
#include <string>
#include <iostream>

using namespace std;

SIMDModel::Subprocessor::Subprocessor(int index)
{
	this->index = index;
}

double SIMDModel::Subprocessor::add(double operand1, double operand2)
{
	return operand1 + operand2;
}

double SIMDModel::Subprocessor::substract(double operand1, double operand2)
{
	return operand1 - operand2;
}

double SIMDModel::Subprocessor::multiply(double operand1, double operand2)
{
	return operand1 * operand2;
}

double SIMDModel::Subprocessor::max(double operand1, double operand2)
{
	return operand1 >= operand2 ? operand1 : operand2;
}

double SIMDModel::Subprocessor::min(double operand1, double operand2)
{
	return operand1 <= operand2 ? operand1 : operand2;
}

double SIMDModel::Subprocessor::run(const SIMDModel::operationName operation, double operand1, double operand2)
{
	double result = 0;

	switch (operation)
	{
	case ADD:
		result = add(operand1, operand2);
		break;
	case SUBSTRACT:
		result = substract(operand1, operand2);
		break;
	case MULTIPLY:
		result = multiply(operand1, operand2);
		break;
	case MAX:
		result = max(operand1, operand2);
	case MIN:
		result = min(operand1, operand2);
		break;
	}

	return result;
}

void SIMDModel::generateTwoDimentionalMatrix(TwoDimentionalMatrix* matrix)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < matrix->getX(); i++)
	{
		for (int j = 0; j < matrix->getY(); j++)
		{
			matrix->setElement(i, j, (double)rand() / RAND_MAX * 2 - 1);
		}
	}
}

void SIMDModel::switchSubprocessorIndex(int *index)
{
	if (*index < subprocessorNumber - 1)
	{
		(*index)++;
	}
	else
	{
		*index = 0;
	}
}

void SIMDModel::updateTime(operationName operation)
{
	switch (operation)
	{
	case ADD:
		runTime += additionTime;
		break;
	case SUBSTRACT:
		runTime += substractionTime;
		break;
	case MULTIPLY:
		runTime += multiplicationTime;
		break;
	case MAX:
		runTime += compairingTime;
		break;
	case MIN:
		runTime += compairingTime;
		break;
	default:
		break;
	}
}

TriDimentionalMatrix* SIMDModel::processTriDim(const operationName operation, TwoDimentionalMatrix* matrix1, TwoDimentionalMatrix* matrix2)
{
	int subprocessorIndex = 0;
	double buffer;
	TriDimentionalMatrix* resultMatrix = new TriDimentionalMatrix(p, q, m);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			for (int k = 0; k < m; k++)
			{
				switch (operation)
				{
				case MULTIPLY_AB:
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(MULTIPLY, matrix1->getElement(i, k), matrix2->getElement(k, j)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(MULTIPLY);
					break;
				case SUP_AB:
					buffer = subprocessorList[subprocessorIndex]->run(MULTIPLY, 1 - matrix1->getElement(i, k), 1);
					updateTime(MULTIPLY);
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(MIN, buffer, matrix2->getElement(k, j)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(MIN);
					break;
				case SUP_BA:
					buffer = subprocessorList[subprocessorIndex]->run(MULTIPLY, 1 - matrix1->getElement(k, j), 1);
					updateTime(MULTIPLY);
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(MIN, buffer, matrix2->getElement(i, k)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(MIN);
					break;
				default:
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(operation, matrix1->getElement(i, k), matrix2->getElement(k, j)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(operation);
					break;
				}
			}
		}
	}

	return resultMatrix;
}

TriDimentionalMatrix* SIMDModel::processTriDim(const operationName operation, TwoDimentionalMatrix* matrix, const double digit)
{
	int subprocessorIndex = 0;
	TriDimentionalMatrix* resultMatrix = new TriDimentionalMatrix(p, q, m);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			for (int k = 0; k < m; k++)
			{
				switch (operation)
				{
				default:
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(operation, matrix->getElement(0, k), digit));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(operation);
					break;
				}
			}
		}
	}

	return resultMatrix;
}

TriDimentionalMatrix* SIMDModel::processTriDim(const operationName operation, TriDimentionalMatrix* matrix, const double digit)
{
	int subprocessorIndex = 0;
	TriDimentionalMatrix* resultMatrix = new TriDimentionalMatrix(p, q, m);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			for (int k = 0; k < m; k++)
			{
				switch (operation)
				{
				default:
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(operation, matrix->getElement(i, j, k), digit));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(operation);
					break;
				}
			}
		}
	}
	return resultMatrix;
}

TriDimentionalMatrix* SIMDModel::processTriDim(const operationName operation, TriDimentionalMatrix* matrix1, TwoDimentionalMatrix* matrix2)
{
	int subprocessorIndex = 0;
	TriDimentionalMatrix* resultMatrix = new TriDimentionalMatrix(p, q, m);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			for (int k = 0; k < m; k++)
			{
				switch (operation)
				{
				default:
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(operation, matrix1->getElement(i, j, k), matrix2->getElement(0, k)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(operation);
					break;
				}
			}
		}
	}

	return resultMatrix;
}

TriDimentionalMatrix* SIMDModel::processTriDim(const operationName operation, const double digit, TwoDimentionalMatrix* matrix)
{
	int subprocessorIndex = 0;
	TriDimentionalMatrix* resultMatrix = new TriDimentionalMatrix(p, q, m);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			for (int k = 0; k < m; k++)
			{
				switch (operation)
				{
				default:
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(operation, digit, matrix->getElement(0, k)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(operation);
					break;
				}
			}
		}
	}

	return resultMatrix;
}

TriDimentionalMatrix* SIMDModel::processTriDim(const operationName operation, TriDimentionalMatrix* matrix1, TriDimentionalMatrix* matrix2)
{
	int subprocessorIndex = 0;
	TriDimentionalMatrix* resultMatrix = new TriDimentionalMatrix(p, q, m);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			for (int k = 0; k < m; k++)
			{
				switch (operation)
				{
				default:
					resultMatrix->setElement(i, j, k,
						subprocessorList[subprocessorIndex]->run(operation, matrix1->getElement(i, j, k), matrix2->getElement(i, j, k)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(operation);
					break;
				}
			}
		}
	}

	return resultMatrix;
}

TwoDimentionalMatrix* SIMDModel::processTwoDim(const operationName operation, TriDimentionalMatrix* matrix)
{
	int subprocessorIndex = 0;
	TwoDimentionalMatrix* resultMatrix = new TwoDimentionalMatrix(p, q);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			switch (operation)
			{
			case MULTIPLICATION_F:
				for (int k = 0; k < m; k++)
				{
					resultMatrix->setElement(i, j, subprocessorList[subprocessorIndex]->run(MULTIPLY, resultMatrix->getElement(i, j), matrix->getElement(i, j, k)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(MULTIPLY);
				}
				break;

			case MULTIPLICATION_D:
				for (int k = 0; k < m; k++)
				{
					resultMatrix->setElement(i, j, subprocessorList[subprocessorIndex]->run(MULTIPLY, resultMatrix->getElement(i, j), 1 - matrix->getElement(i, j, k)));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(MULTIPLY);
				}

				resultMatrix->setElement(i, j, 1 - resultMatrix->getElement(i, j));
				updateTime(SUBSTRACT);
				break;
			}
		}
	}

	return resultMatrix;
}

TwoDimentionalMatrix* SIMDModel::processTwoDim(const operationName operation, TriDimentionalMatrix* matrix1, TriDimentionalMatrix* matrix2)
{
	int subprocessorIndex = 0;
	TwoDimentionalMatrix* resultMatrix = new TwoDimentionalMatrix(p, q);
	TwoDimentionalMatrix* buffer1 = new TwoDimentionalMatrix(p, q);
	TwoDimentionalMatrix* buffer2 = new TwoDimentionalMatrix(p, q);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			switch (operation)
			{
			case MAX_FD:
				for (int k = 0; k < m; k++)
				{
					buffer1 = processTwoDim(MULTIPLICATION_F, F);
					buffer2 = processTwoDim(MULTIPLICATION_D, D);
					resultMatrix->setElement(i, j,
						subprocessorList[subprocessorIndex]->run(MAX, buffer1->getElement(i, j) + buffer2->getElement(i, j) - 1, 0));
					switchSubprocessorIndex(&subprocessorIndex);
					updateTime(MAX);
				}
				break;
			}
		}
	}

	return resultMatrix;
}

TwoDimentionalMatrix* SIMDModel::processTwoDim(const operationName operation, TwoDimentionalMatrix* matrix, const double digit)
{
	int subprocessorIndex = 0;
	TwoDimentionalMatrix* resultMatrix = new TwoDimentionalMatrix(p, q);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			switch (operation)
			{
			default:
				resultMatrix->setElement(i, j,
					subprocessorList[subprocessorIndex]->run(operation, matrix->getElement(i, j), digit));
				switchSubprocessorIndex(&subprocessorIndex);
				updateTime(operation);
				break;
			}
		}
	}

	return resultMatrix;
}

TwoDimentionalMatrix* SIMDModel::processTwoDim(const operationName operation, TwoDimentionalMatrix* matrix1, TwoDimentionalMatrix* matrix2)
{
	int subprocessorIndex = 0;
	TwoDimentionalMatrix* resultMatrix = new TwoDimentionalMatrix(p, q);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			switch (operation)
			{
			default:
				resultMatrix->setElement(i, j,
					subprocessorList[subprocessorIndex]->run(operation, matrix1->getElement(i, j), matrix2->getElement(i, j)));
				switchSubprocessorIndex(&subprocessorIndex);
				updateTime(operation);
				break;
			}
		}
	}

	return resultMatrix;
}

TwoDimentionalMatrix* SIMDModel::processTwoDim(const operationName operation, const double digit, TwoDimentionalMatrix* matrix)
{
	int subprocessorIndex = 0;
	TwoDimentionalMatrix* resultMatrix = new TwoDimentionalMatrix(p, q);

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			switch (operation)
			{
			default:
				resultMatrix->setElement(i, j,
					subprocessorList[subprocessorIndex]->run(operation, digit, matrix->getElement(i, j)));
				switchSubprocessorIndex(&subprocessorIndex);
				updateTime(operation);
				break;
			}
		}
	}

	return resultMatrix;
}

void SIMDModel::equalMatrixes(TwoDimentionalMatrix* matrix1, TwoDimentionalMatrix* matrix2)
{
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			matrix1->setElement(i, j, matrix2->getElement(i, j));
		}
	}
}

void SIMDModel::equalMatrixes(TriDimentionalMatrix* matrix1, TriDimentionalMatrix* matrix2)
{
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			for (int k = 0; k < m; k++)
			{
				matrix1->setElement(i, j, k, matrix2->getElement(i, j, k));

			}
		}
	}
}

void SIMDModel::calculateDMatrix()
{
	D = processTriDim(MULTIPLY_AB, A, B);
}

void SIMDModel::calculateFMatrix()
{
	vector<TriDimentionalMatrix*> buffer(3, new TriDimentionalMatrix(p, q, m));

	buffer[1] = processTriDim(SUP_AB, A, B);
	buffer[2] = processTriDim(MULTIPLY, E, 2);
	buffer[2] = processTriDim(SUBSTRACT, buffer[2], 1);
	buffer[1] = processTriDim(MULTIPLY, buffer[1], buffer[2]);
	buffer[1] = processTriDim(MULTIPLY, buffer[1], E);
	equalMatrixes(buffer[0], buffer[1]);

	buffer[1] = processTriDim(SUP_BA, B, A);
	buffer[2] = processTriDim(SUP_AB, A, B);
	buffer[2] = processTriDim(MULTIPLY, buffer[2], 4);
	buffer[2] = processTriDim(SUBSTRACT, buffer[2], 2);
	buffer[2] = processTriDim(MULTIPLY, buffer[2], E);
	buffer[2] = processTriDim(ADD, buffer[2], 1);
	buffer[1] = processTriDim(MULTIPLY, buffer[1], buffer[2]);
	buffer[2] = processTriDim(SUBSTRACT, 1, E);
	buffer[1] = processTriDim(MULTIPLY, buffer[1], buffer[2]);
	buffer[0] = processTriDim(ADD, buffer[0], buffer[1]);

	F = buffer[0];
}

void SIMDModel::calculateCMatrix()
{
	vector<TwoDimentionalMatrix*> buffer(4, new TwoDimentionalMatrix(p, q));

	buffer[1] = processTwoDim(MULTIPLICATION_F, F);
	buffer[2] = processTwoDim(MULTIPLY, G, 3);
	buffer[2] = processTwoDim(SUBSTRACT, buffer[2], 2);
	buffer[1] = processTwoDim(MULTIPLY, buffer[1], buffer[2]);
	buffer[1] = processTwoDim(MULTIPLY, buffer[1], G);
	equalMatrixes(buffer[0], buffer[1]);

	buffer[1] = processTwoDim(MULTIPLICATION_D, D);
	buffer[2] = processTwoDim(MAX_FD, F, D);
	buffer[2] = processTwoDim(MULTIPLY, buffer[2], 4);
	buffer[3] = processTwoDim(MULTIPLICATION_D, D);
	buffer[3] = processTwoDim(MULTIPLY, buffer[3], 3);
	buffer[2] = processTwoDim(SUBSTRACT, buffer[2], buffer[3]);
	buffer[2] = processTwoDim(MULTIPLY, buffer[2], G);
	buffer[1] = processTwoDim(ADD, buffer[1], buffer[2]);
	buffer[2] = processTwoDim(SUBSTRACT, 1, G);
	buffer[1] = processTwoDim(MULTIPLY, buffer[1], buffer[2]);
	buffer[0] = processTwoDim(ADD, buffer[0], buffer[1]);

	C = buffer[0];
}

SIMDModel::SIMDModel()
{
	cout << "Input subprocessor number: ";
	cin >> subprocessorNumber;
	subprocessorList.resize(subprocessorNumber);
	for (int i = 0; i < subprocessorNumber; i++)
	{
		subprocessorList[i] = new Subprocessor(i);
	}
	cout << "Input addition time: ";
	cin >> additionTime;
	cout << "Input substraction time: ";
	cin >> substractionTime;
	cout << "Input multiplication time: ";
	cin >> multiplicationTime;
	cout << "Input compairing time: ";
	cin >> compairingTime;
	cout << "Input p: ";
	cin >> p;
	cout << "Input q: ";
	cin >> q;
	cout << "Input m: ";
	cin >> m;

	A = new TwoDimentionalMatrix(p, m);
	generateTwoDimentionalMatrix(A);
	B = new TwoDimentionalMatrix(m, q);
	generateTwoDimentionalMatrix(B);
	E = new TwoDimentionalMatrix(1, m);
	generateTwoDimentionalMatrix(E);
	G = new TwoDimentionalMatrix(p, q);
	generateTwoDimentionalMatrix(G);

	cout << "Do you want to print initial matrixes(A, B, E, G)?(y -- yes) ";
	string inputString;
	cin >> inputString;
	if (inputString == "y")
	{
		cout << "matrix A:\n";
		A->print();
		cout << "matrix B:\n";
		B->print();
		cout << "matrix E:\n";
		E->print();
		cout << "matrix G:\n";
		G->print();
	}

	calculateDMatrix();
	
	cout << "Do you want to print D matrix?(y -- yes) ";
	cin >> inputString;
	if (inputString == "y")
	{
		cout << "matrix D:\n";
		D->print();
	}

	calculateFMatrix();
	cout << "Do you want to print F matrix?(y -- yes) ";
	cin >> inputString;
	if (inputString == "y")
	{
		cout << "matrix F:\n";
		F->print();
	}

	calculateCMatrix();
	cout << "Do you want to print C matrix?(y -- yes) ";
	cin >> inputString;
	if (inputString == "y")
	{
		cout << "matrix C:\n";
		C->print();
	}
}
