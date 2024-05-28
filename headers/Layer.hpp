#include <vector>
#include <iostream>
#include "Neuron.hpp"

using namespace std;

class Layer{
    private:
    public:
    int numneurons;
    vector<vector<double>> weights;
    vector<Neuron> neurons;
    vector<double> biases;
    void connect(int previous);
    Layer(int n);
};