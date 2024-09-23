#pragma once
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<double> matrixMult(vector<vector<double>> a, vector<double> b);

double sigmoid(double d);

vector<double> MSE(vector<double>);