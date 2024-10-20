#pragma once
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<double> matrixMult(vector<vector<double>> a, vector<double> b);

double sigmoidA(double d);
double sigmoidB(double d);

double reLUA(double d);
double reLUB(double d);

typedef double (*funcPtr)(double);

inline funcPtr sigmoid[] = {sigmoidA, sigmoidB};

inline funcPtr reLU[] = {reLUA, reLUB};

vector<double> MSE(vector<double> a, vector<double> b);
