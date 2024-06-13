#pragma once
#include <vector>
#include <cmath>

using namespace std;

vector<double> matrixMult(vector<vector<double>> a, vector<double> b);

double sigmoid(double d);

double sigmoidDerivative(double d);

vector<vector<double>> matFlip(vector<vector<double>> a);