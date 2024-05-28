#include "headers/Network.hpp"
#include "headers/Helper.hpp"

using namespace std;

Network::Network(int l[], int c){
    for (int i = 0; i < c; i++){
        Layer L(l[i]);
        layers.push_back(L);
    }

}

void Network::connect(int n){
    for (int i = 0; i < layers.size(); i++){
        if (i == 0) layers[i].connect(n);
        else layers[i].connect(layers[i-1].numneurons);
    }
}

void Network::calculate(){
    for (int i = 1; i < layers.size(); i++){
        vector<double> prevneurons;
        for (Neuron n: layers[i-1].neurons){
            prevneurons.push_back(n.value);
        }
        vector<double> neuronvalues = matrixMult(layers[i].weights, prevneurons);
        for (int n = 0; n < neuronvalues.size(); n++){
            layers[i].neurons[n].value = sigmoid(neuronvalues[n] + layers[i].biases[n]);
        }
    }
}

void Network::input(vector<double> v){
    for (int n = 0; n < v.size(); n++){
        layers[0].neurons[n].value = v[n];
    }
}

double Network::totalError(vector<double> v){
    double e = 0;
    for (int i = 0; i < layers[layers.size()-1].neurons.size(); i++){
        e += layers[layers.size()-1].neurons[i].error(v[i]);
    }

    return e;
}