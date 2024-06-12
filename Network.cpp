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
        for (int r = 0; r < layers[l].biases.size(); r++){
            layers[l].biases[r] = rd();
        }
    }
}

void Network::propogate(int l, int r, int c){
    for (int L = 0; L < layers.size(); L++){
        layers[L].propWeights = layers[L].weights;
    }
    for (int n = 0; n < layers[l].propWeights.size(); n++){
        for (int n2 = 0; n2 < layers[l].propWeights[0].size(); n2++){
            layers[l].propWeights[n][n2] = 0;
        }
    }
    layers[l].propWeights[r][c] = 1;

    for (int i = 0; i < layers.size(); i++){
        layers[i].propNeurons = layers[i].neurons;
    }
}

double Network::propogationCalculation(vector<double> in, vector<double> out){
    for (int n = 0; n <in.size(); n++){
        layers[0].neurons[n].value = in[n];
    }
    for (int i = 1; i < layers.size(); i++){
        vector<double> prevneurons;
        for (Neuron n: layers[i-1].propNeurons){
            prevneurons.push_back(n.value);
        }
        vector<double> neuronvalues = matrixMult(layers[i].propWeights, prevneurons);
        for (int n = 0; n < neuronvalues.size(); n++){
            // layers[i].propNeurons[n].value = neuronvalues[n]*sigmoidDerivative( );
        }
    }

    double totalDerivative = 0;

    vector<Neuron> outNeurons = layers[layers.size()-1].neurons;
    vector<Neuron> outPropNeurons = layers[layers.size()-1].propNeurons;

    // for (Neuron n: outPropNeurons){
    //     cout << n.value << "\n";
    // }

    cout << "Final top neuron:" << outPropNeurons[0].value << "\n";

    for (int i = 0; i < out.size(); i++){
        totalDerivative += 2*(outNeurons[i].value-out[i])*outPropNeurons[i].value;
    }

    return totalDerivative;
}

void Network::calculateNoBound(){
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

void Network::backPropogate(vector<double> out){
    for (int L = 0; L < layers.size(); L++){
        layers[L].propWeights = layers[L].weights;
    }
    calculate();
    for (int n = 0; n < layers[layers.size()-1].neurons.size(); n++){
        layers[layers.size()-1].neurons[n].value = 1;
    }
    for (int l = layers.size()-1; l > 0; l--){
        for (int r = 0; r < layers[l].weights.size(); r++){
            for (int c = 0; c < layers[l].weights[0].size(); c++){
                layers[l].propWeights[r][c] = layers[l-1].neurons[c].value * sigmoidDerivative(layers[l-1].neurons[c].value * layers[l].propWeights[r][c] + layers[l].biases[r]) * layers[l].neurons[r].value;
                // layers[l-1].neurons[c].value *= layers[l].propWeights[r][c];
                layers[l-1].neurons[c].value += layers[l].weights[r][c] * sigmoidDerivative(layers[l-1].neurons[c].value * layers[l].propWeights[r][c] + layers[l].biases[r]);
            }
        }
    }
}