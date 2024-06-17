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
        Neuron ne;
        //also add neurons and biases
        neurons.push_back(ne);
        biases.push_back(0);
    }
    propWeights = weights;
    propBiases = biases;
}

Layer::Layer(int n){
    numneurons = n;
}

void Layer::multNeurons(vector<vector<double>> n){
    vector<double> v(neurons.size());
    for (int i = 0; i < v.size(); i++){
        v[i] = neurons[i].value;
    }
    vector<double> v2 = matrixMult(n, v);
    for (int i = 0; i < v2.size(); i++){
        neurons[i].value = v2[i];
    }
}

vector<double> Layer::returnValues(){
    vector<double> v;
    for (Neuron n: neurons){
        v.push_back(n.value);
    }
    return v;
}

void Layer::setNeurons(vector<double> v){
    for (int i = 0; i < v.size(); i++){
        neurons[i].value = v[i];
    }
}