#include "headers/Layer.hpp"


void Layer::connect(int n){
    int rows = numneurons;
    int columns = n;
    vector<double> v;
    for (int c = 0; c < columns; c++){
        v.push_back(0);
    }
    for (int r = 0; r < rows; r++){
        weights.push_back(v);
        weightChanges.push_back(v);
        Neuron ne;
        //also add neurons and biases
        neurons.push_back(ne);
        biases.push_back(0);
        biasChanges.push_back(0);
    }
    // cout << neurons.size() << "\n";
}

Layer::Layer(int n){
    numneurons = n;
}