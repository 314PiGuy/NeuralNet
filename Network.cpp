#include "headers/Network.hpp"
#include "headers/Helper.hpp"

using namespace std;

Network::Network(vector<Layer> l, double learn)
{
    layers = l;
    learnRate = learn;
}

void Network::connect(int n)
{
    for (int i = 0; i < layers.size(); i++)
    {
        if (i == 0)
            layers[i].connect(n);
        else
            layers[i].connect(layers[i - 1].numneurons);
    }
}

void Network::randomize()
{
    random_device rd;
    std::mt19937 engine(rd());
    for (int l = 0; l < layers.size(); l++)
    {
        for (int r = 0; r < layers[l].weights.size(); r++)
        {
            for (int c = 0; c < layers[l].weights[0].size(); c++)
            {
                layers[l].weights[r][c] = rd();
            }
        }
        for (int r = 0; r < layers[l].biases.size(); r++)
        {
            layers[l].biases[r] = rd();
        }
    }
}

void Network::calculate()
{
    for (int i = 1; i < layers.size(); i++)
    {
        vector<double> prevneurons = layers[i - 1].neurons;
        auto activation = layers[i].activation;
        vector<double> neuronvalues = matrixMult(layers[i].weights, prevneurons);
        for (int n = 0; n < neuronvalues.size(); n++)
        {
            layers[i].neurons[n] = activation(neuronvalues[n] + layers[i].biases[n], false);
        }
    }
}

vector<double> Network::predict(vector<double> in)
{
    layers[0].neurons = in;
    calculate();
    return layers.back().neurons;
}

void Network::backPropagate(vector<double> out, vector<double> (*error)(vector<double>, vector<double>))
{

    vector<double> errors = error(layers.back().neurons, out);

    vector<double> sigmoids(layers.back().neurons.size());

    for (int i = 0; i < sigmoids.size(); i++)
    {
        errors[i] *= layers.back().activation(layers.back().neurons[i], true);
    }

    for (int l = layers.size() - 1; l > 0; l--)
    {
        vector<double> errors2(layers[l - 1].neurons.size(), 0);
        for (int r = 0; r < layers[l].weights.size(); r++)
        {
            for (int c = 0; c < layers[l].weights[0].size(); c++)
            {
                layers[l].propWeights[r][c] = layers[l - 1].neurons[c] * errors[r];
                layers[l].propBiases[r] = errors[r];
                errors2[c] += layers[l].weights[r][c] * errors[r];
            }
        }
        for (int i = 0; i < layers[l - 1].neurons.size(); i++)
        {
            errors2[i] *= layers[l-1].activation(layers[l - 1].neurons[i], true);
        }
        errors = errors2;
    }

    for (int l = layers.size() - 1; l > 0; l--)
    {
        for (int r = 0; r < layers[l].weights.size(); r++)
        {
            for (int c = 0; c < layers[l].weights[0].size(); c++)
            {
                layers[l].weights[r][c] -= layers[l].propWeights[r][c] * learnRate;
                layers[l].biases[r] -= layers[l].propBiases[r] * learnRate;
            }
        }
    }
}

void Network::train(vector<vector<double>> inputs, vector<vector<double>> outputs, vector<double> (*error)(vector<double>, vector<double>), int repititions)
{
    for (int i = 0; i < repititions; i++)
    {
        for (int n = 0; n < inputs.size(); n++)
        {
            layers[0].neurons = inputs[n];
            calculate();
            backPropagate(outputs[n], error);
        }
    }
}
