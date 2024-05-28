#include "headers/Layer.hpp"


void Layer::connect(int n){
    int rows = numneurons;
    int columns = n;
    vector<double> v;
    for (int c = 0; c < columns; c++){
        v.push_back(2);
    }
    for (int r = 0; r < rows; r++){
        weights.push_back(v);
        Neuron ne;
        //also add neurons
        neurons.push_back(ne);
    }
    // cout << neurons.size() << "\n";
}

Layer::Layer(int n){
    numneurons = n;
}