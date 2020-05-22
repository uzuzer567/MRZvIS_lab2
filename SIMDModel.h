#include "TwoDimentionalMatrix.h"
#include "TriDimentionalMatrix.h"
#include <time.h>
#include <random>
#include <iostream>
#include <string.h>

class SIMDModel
{
private:
	enum operationName
	{
		ADD, SUBSTRACT, MULTIPLY, MAX, MIN,  MULTIPLICATION_F, MULTIPLICATION_D, MULTIPLY_AB, MAX_FD, SUP_AB, SUP_BA
	};
	class Subprocessor
	{
	private:
		int index;
		double add(double, double);
		double substract(double, double);
		double multiply(double, double);
		double max(double, double);
		double min(double, double);
	public:
		Subprocessor(int);
		double run(operationName, double, double);
	};

	int subprocessorNumber;
	int runTime;
	int additionTime;
	int substractionTime;
	int multiplicationTime;
	int compairingTime;
	int p;
	int q;
	int m;
	TwoDimentionalMatrix* A;
	TwoDimentionalMatrix* B;
	TwoDimentionalMatrix* E;
	TwoDimentionalMatrix* G;
	TriDimentionalMatrix* D;
	TriDimentionalMatrix* F;
	TwoDimentionalMatrix* C;
	vector<SIMDModel::Subprocessor*> subprocessorList;

	void generateTwoDimentionalMatrix(TwoDimentionalMatrix*);
	void switchSubprocessorIndex(int*);
	void updateTime(const operationName);
	TriDimentionalMatrix* processTriDim(const operationName, TwoDimentionalMatrix*, TwoDimentionalMatrix*);
	TriDimentionalMatrix* processTriDim(const operationName, TwoDimentionalMatrix*, const double);
	TriDimentionalMatrix* processTriDim(const operationName, TriDimentionalMatrix*, const double);
	TriDimentionalMatrix* processTriDim(const operationName, TriDimentionalMatrix*, TwoDimentionalMatrix*);
	TriDimentionalMatrix* processTriDim(const operationName, const double, TwoDimentionalMatrix*);
	TriDimentionalMatrix* processTriDim(const operationName, TriDimentionalMatrix*, TriDimentionalMatrix*);
	TwoDimentionalMatrix* processTwoDim(const operationName, TriDimentionalMatrix*);
	TwoDimentionalMatrix* processTwoDim(const operationName, TriDimentionalMatrix*, TriDimentionalMatrix*);
	TwoDimentionalMatrix* processTwoDim(const operationName, TwoDimentionalMatrix*, const double);
	TwoDimentionalMatrix* processTwoDim(const operationName, TwoDimentionalMatrix*, TwoDimentionalMatrix*);
	TwoDimentionalMatrix* processTwoDim(const operationName, const double, TwoDimentionalMatrix*);
	void equalMatrixes(TwoDimentionalMatrix*, TwoDimentionalMatrix*);
	void equalMatrixes(TriDimentionalMatrix*, TriDimentionalMatrix*);
	void calculateDMatrix();
	void calculateFMatrix();
	void calculateCMatrix();
public:
	SIMDModel();
};

