#include <vector>
#include <iostream>

using namespace std;

class Layer
{
private:
public:
    double (*activation)(double, bool);
    int numneurons;
    vector<vector<double>> weights;
    vector<vector<double>> propWeights;
    vector<double> neurons;
    vector<double> biases;
    vector<double> propBiases;
    void connect(int previous);
    Layer(int neurons, double (*activation)(double, bool));
};