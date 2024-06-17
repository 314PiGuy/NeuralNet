#include <iostream>
#include <random>
#include "Layer.hpp"

using namespace std;

class Network{
    private:
    public:
    double learnRate;
    vector<Layer> layers;
    Network(int l[], int c, double f);
    // Network(int *l);
    void connect(int inputNeurons);
    void calculate();
    void input(vector<double> v);
    double totalError(vector<double> v);
    void output(vector<double> v);
    void randomize();
    void backPropagate(vector<double> out);
};