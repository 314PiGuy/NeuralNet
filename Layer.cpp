#include "headers/Layer.hpp"
#include "headers/Helper.hpp"

void Layer::connect(int n)
{
    int rows = numneurons;
    int columns = n;
    weights = vector<vector<double>>(rows, vector<double>(columns));
    propWeights = vector<vector<double>>(rows, vector<double>(columns));
}

Layer::Layer(int n, double (*a)(double, bool))
{
    activation = a;
    numneurons = n;
    neurons = vector<double>(n);
    biases = vector<double>(n);
    propBiases = vector<double>(n);
}
