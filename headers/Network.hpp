#pragma once
#include <iostream>
#include <random>
#include "Layer.hpp"

using namespace std;

class Network
{
private:
public:
    double learnRate;
    vector<Layer> layers;
    Network(vector<Layer> l, double f);
    void connect(int inputNeurons);
    void calculate();
    void input(vector<double> v);
    void randomize();
    void backPropagate(vector<double> out, vector<double> (*error)(vector<double> a, vector<double> b));
    void train(vector<vector<double>> in, vector<vector<double>> out, vector<double> (*error)(vector<double> a, vector<double> b), int e);
    vector<double> predict(vector<double> in);
};