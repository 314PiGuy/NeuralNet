#pragma once
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<double> matrixMult(vector<vector<double>> a, vector<double> b);

double sigmoid(double d);

vector<vector<double>> matFlip(vector<vector<double>> a);

vector<vector<double>> bigDot(vector<double> a, vector<double> b);

vector<double> dot(vector<double> a, vector<double> b);

double sigmoidThing(double d);