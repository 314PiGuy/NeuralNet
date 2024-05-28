#include <iostream>
#include "Layer.hpp"

using namespace std;

class Network{
    private:
    public:
    vector<Layer> layers;
    Network(int l[], int c);
    void connect(int inputNeurons);
    void calculate();
    void input(vector<double> v);
    double totalError(vector<double> v);
};