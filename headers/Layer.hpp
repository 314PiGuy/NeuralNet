#include <vector>
#include <iostream>
#include "Neuron.hpp"

using namespace std;

class Layer{
    private:
    public:
    int numneurons;
    vector<vector<double>> weights;
    vector<vector<double>> weightChanges;
    vector<vector<double>> propWeights;
    vector<Neuron> neurons;
    vector<Neuron> propNeurons;
    vector<double> biases;
    vector<double> biasChanges;
    vector<double> propBiases;
    void connect(int previous);
    Layer(int n);
};