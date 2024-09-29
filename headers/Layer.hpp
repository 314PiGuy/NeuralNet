#pragma once
#include <vector>
#include <iostream>
#include "Helper.hpp"

using namespace std;

class Layer{
    private:
    public:
    int numneurons;
    vector<vector<double>> weights;
    vector<vector<double>> propWeights;
    vector<double> neurons;
    vector<double> biases;
    vector<double> propBiases;
    funcPtr *activation;
    void connect(int previous);
    Layer(int n, funcPtr *a);
    void setNeurons(vector<double>);
};