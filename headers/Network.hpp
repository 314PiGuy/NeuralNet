#include <iostream>
#include <random>
#include "Layer.hpp"

using namespace std;

class Network{
    private:
    public:
    vector<Layer> layers;
    Network(int l[], int c);
    // Network(int *l);
    void connect(int inputNeurons);
    void calculate();
    void input(vector<double> v);
    double totalError(vector<double> v);
    void output(vector<double> v);
    void randomize();
    void backPropagate(vector<double> out);
};