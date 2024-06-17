#include <vector>
#include <iostream>
#include "Neuron.hpp"

using namespace std;

class Layer{
    private:
    public:
    int numneurons;
    vector<vector<double>> weights;
    vector<vector<double>> propWeights;
    vector<Neuron> neurons;
    vector<double> biases;
    vector<double> propBiases;
    void connect(int previous);
    void multNeurons(vector<vector<double>> n);
    Layer(int n);
    vector<double> returnValues();
    void setNeurons(vector<double>);
};