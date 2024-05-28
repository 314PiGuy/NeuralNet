#include "headers/Network.hpp"
#include "headers/Helper.hpp"

using namespace std;

Network::Network(int l[]){
    for (int i = 0; i < sizeof(l)/sizeof(l[0])+1; i++){
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
            layers[i].neurons[n].value = neuronvalues[n];
        }
    }
}

void Network::input(vector<double> v){
    // cout << layers[1].neurons.size();
    // for (Neuron n: layers[0].neurons){
    //     cout << n.value << "e" << "\n";
    // }
    for (int n = 0; n < v.size(); n++){
        layers[0].neurons[n].value = v[n];
    }
}