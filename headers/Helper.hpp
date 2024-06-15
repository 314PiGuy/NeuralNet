#pragma once
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<double> matrixMult(vector<vector<double>> a, vector<double> b);

double sigmoid(double d);

double sigmoidDerivative(double d);

vector<vector<double>> matFlip(vector<vector<double>> a);

vector<vector<double>> bigDot(vector<double> a, vector<double> b);

double unSigmoid(double d);

vector<double> dot(vector<double> a, vector<double> b);