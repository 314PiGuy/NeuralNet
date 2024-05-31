#include "headers/Network.hpp"
#include "headers/Helper.hpp"

using namespace std;

Network::Network(int l[], int c){
    for (int i = 0; i < c; i++){
        Layer L(l[i]);
        layers.push_back(L);
    }

}

// Network::Network(int *l){
//     for (int i = 0; i < sizeof(l)/sizeof(l[0])+1; i++){
//         Layer L(l[i]);
//         layers.push_back(L);
//     }
// }

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

    return e/layers[layers.size()-1].neurons.size();
}

void Network::output(vector<double> v){
    for (Neuron n: layers[layers.size()-1].neurons){
        cout << n.value << "\n";
    }
    cout << "\n";
    cout << totalError(v) << "\n";
}

void Network::randomize(){
    random_device rd;
    std::mt19937 engine(rd());
    for (int l = 0; l < layers.size(); l++){
        for (int r = 0; r < layers[l].weights.size(); r++){
            for (int c = 0; c < layers[l].weights[0].size(); c++){
                layers[l].weights[r][c] = rd();
            }
        }
        for (int r = 0; r < layers[l].biasChanges.size(); r++){
            layers[l].biasChanges[r] = rd();
        }
    }
}