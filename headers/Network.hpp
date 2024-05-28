#include "Layer.hpp"

using namespace std;

class Network{
    private:
    vector<Layer> layers;
    public:
    Network(int l[]);
    void connect(int inputNeurons);
    vector<double> calculate();
};