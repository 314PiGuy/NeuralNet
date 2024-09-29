#include "headers/Layer.hpp"
#include "headers/Helper.hpp"

void Layer::connect(int n){
    int rows = numneurons;
    int columns = n;
    vector<double> v;
    for (int c = 0; c < columns; c++){
        v.push_back(0);
    }
    for (int r = 0; r < rows; r++){
        weights.push_back(v);
        //also add neurons and biases
        neurons.push_back(0);
        biases.push_back(0);
    }
    propWeights = weights;
    propBiases = biases;
}

Layer::Layer(int n, funcPtr *a){
    activation = a;
    numneurons = n;
}



void Layer::setNeurons(vector<double> v){
    for (int i = 0; i < v.size(); i++){
        neurons[i] = v[i];
    }
}