#include "headers/Network.hpp"
#include "headers/Helper.hpp"

using namespace std;

Network::Network(vector<Layer> l, double learn){
    for (Layer L: l){
        layers.push_back(L);
    }
    learnRate = learn;

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
        for (double n: layers[i-1].neurons){
            prevneurons.push_back(n);
        }
        vector<double> neuronvalues = matrixMult(layers[i].weights, prevneurons);
        for (int n = 0; n < neuronvalues.size(); n++){
            layers[i].neurons[n] = layers[i].activation[0](neuronvalues[n] + layers[i].biases[n]);
        }
    }
}

void Network::input(vector<double> v){
    for (int n = 0; n < v.size(); n++){
        layers[0].neurons[n] = v[n];
    }
}



void Network::randomize(){
    random_device rd;
    mt19937 gen(rd());
    for (int i = 0; i < layers.size(); i++){
        int inputs = layers[i].weights[0].size();
        int outputs = layers[i].weights.size();
        float dist = sqrt(2/inputs+outputs);
        normal_distribution<> d(-1*dist, dist);
        for (int j = 0; j < layers[i].weights.size(); j++){
            for (int k = 0; k < layers[i].weights[j].size(); k++){
                layers[i].weights[j][k] = d(gen);
            }
        }
    }
}



void Network::backPropagate(vector<double> out){
    calculate();
    

    vector<double> errors(layers.back().neurons.size());

    for (int i = 0; i < errors.size(); i++){
        errors[i] = 2*(layers.back().neurons[i]-out[i])/layers.back().neurons.size();
    }

    vector<double> sigmoids(layers.back().neurons.size());
    for (int i = 0; i < sigmoids.size(); i++){
        errors[i] *= layers.back().activation[1](layers.back().neurons[i]);
    }


    for (int l = layers.size()-1; l > 0; l--){
        vector<double> errors2(layers[l-1].neurons.size(), 0);
        for (int r = 0; r < layers[l].weights.size(); r++){
            for (int c = 0; c < layers[l].weights[0].size(); c++){
                layers[l].propWeights[r][c] = layers[l-1].neurons[c] * errors[r];
                layers[l].propBiases[r] = errors[r];
                errors2[c] += layers[l].weights[r][c] * errors[r];
            }
        }
        for (int i = 0; i < layers[l-1].neurons.size(); i++){
            errors2[i] *= layers[l-1].activation[1](layers[l-1].neurons[i]);
        }
        errors = errors2;
    }

    for (int l = layers.size()-1; l > 0; l--){
        for (int r = 0; r < layers[l].weights.size(); r++){
            for (int c = 0; c < layers[l].weights[0].size(); c++){
                layers[l].weights[r][c] -= layers[l].propWeights[r][c] * learnRate;
                layers[l].biases[r] -= layers[l].propBiases[r] * learnRate;

            }
        }
    }
}

void Network::train(vector<vector<double>> in, vector<vector<double>> out, int epochs){
    int s = in.size();
    for (int i = 0; i < epochs; i++){
        for (int n = 0; n < s; n++){
            input(in[n]);
            backPropagate(out[n]);
        }
    }
}

