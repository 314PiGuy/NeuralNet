#include "headers/Network.hpp"
#include "headers/Helper.hpp"

using namespace std;

Network::Network(int l[], int c, double learn){
    for (int i = 0; i < c; i++){
        Layer L(l[i]);
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



void Network::backPropagate(vector<double> out){
    calculate();
    

    vector<double> errors(layers.back().neurons.size());

    for (int i = 0; i < errors.size(); i++){
        errors[i] = 2*(layers.back().neurons[i].value-out[i])/layers.back().returnValues().size();
    }

    vector<double> sigmoids(layers.back().neurons.size());
    for (int i = 0; i < sigmoids.size(); i++){
        errors[i] *= sigmoidThing(layers.back().neurons[i].value);
    }


    for (int l = layers.size()-1; l > 0; l--){
        vector<double> errors2(layers[l-1].neurons.size(), 0);
        for (int r = 0; r < layers[l].weights.size(); r++){
            for (int c = 0; c < layers[l].weights[0].size(); c++){
                layers[l].propWeights[r][c] = layers[l-1].neurons[c].value * errors[r];
                layers[l].propBiases[r] = errors[r];
                errors2[c] += layers[l].weights[r][c] * errors[r];
            }
        }
        for (int i = 0; i < layers[l-1].returnValues().size(); i++){
            errors2[i] *= sigmoidThing(layers[l-1].returnValues()[i]);
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

// void Network::backPropagate(vector<double> out){
//     calculate();
    

//     vector<double> errors(layers.back().neurons.size());

//     for (int i = 0; i < errors.size(); i++){
//         errors[i] = 2*(layers.back().neurons[i].value-out[i])/layers.back().returnValues().size();
//     }

//     vector<double> sigmoids(layers.back().neurons.size());
//     for (int i = 0; i < sigmoids.size(); i++){
//         errors[i] *= sigmoidThing(layers.back().neurons[i].value);
//     }


//     for (int l = layers.size()-1; l > 0; l--){
//         vector<double> errors2(layers[l-1].neurons.size(), 0);
//         for (int r = 0; r < layers[l].weights.size(); r++){
//             for (int c = 0; c < layers[l].weights[0].size(); c++){
//                 layers[l].weights[r][c] -= layers[l-1].neurons[c].value * errors[r] * learnRate;
//                 errors2[c] += layers[l].weights[r][c] * errors[r];
//             }
//         }
//         for (int i = 0; i < layers[l-1].returnValues().size(); i++){
//             errors2[i] *= sigmoidThing(layers[l-1].returnValues()[i]);
//         }
//         errors = errors2;
//     }

//     //e
//     calculate();

//     errors = vector<double>(layers.back().neurons.size());

//     for (int i = 0; i < errors.size(); i++){
//         errors[i] = 2*(layers.back().neurons[i].value-out[i])/layers.back().returnValues().size();
//     }

//     sigmoids = vector<double>(layers.back().neurons.size());
//     for (int i = 0; i < sigmoids.size(); i++){
//         errors[i] *= sigmoidThing(layers.back().neurons[i].value);
//     }


//     for (int l = layers.size()-1; l > 0; l--){
//         vector<double> errors2(layers[l-1].neurons.size(), 0);
//         for (int r = 0; r < layers[l].weights.size(); r++){
//             for (int c = 0; c < layers[l].weights[0].size(); c++){
//                 layers[l].biases[r] -= errors[r] * learnRate;
//                 errors2[c] += layers[l].weights[r][c] * errors[r];
//             }
//         }
//         for (int i = 0; i < layers[l-1].returnValues().size(); i++){
//             errors2[i] *= sigmoidThing(layers[l-1].returnValues()[i]);
//         }
//         errors = errors2;
//     }

// }
