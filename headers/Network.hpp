#include <iostream>
#include <random>
#include "Layer.hpp"

using namespace std;

class Network
{
private:
    vector<Layer> layers;
    void backPropagate(vector<double> out, vector<double> (*error)(vector<double>, vector<double>));
    void calculate();
    void connect(int inputNeurons);
    double learnRate;

public:
    Network(vector<Layer>, double learnRate);
    vector<double> predict(vector<double> in);
    void randomize();
    void train(vector<vector<double>> inputs, vector<vector<double>> outputs, vector<double> (*error)(vector<double>, vector<double>), int reps);
};