#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <algorithm>
#include <thread>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}

double mse_loss(const vector<double>& y_true, const vector<double>& y_pred) {
    double loss = 0.0;
    for (size_t i = 0; i < y_true.size(); ++i) {
        loss += pow(y_true[i] - y_pred[i], 2);
    }
    return loss / y_true.size();
}

vector<double> mse_loss_derivative(const vector<double>& y_true, const vector<double>& y_pred) {
    vector<double> derivatives(y_true.size());
    for (size_t i = 0; i < y_true.size(); ++i) {
        derivatives[i] = y_pred[i] - y_true[i];
    }
    return derivatives;
}

void initialize_network(vector<vector<vector<double>>>& weights, vector<vector<double>>& biases, const vector<int>& layer_sizes) {
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> d(0, 0);

    for (size_t i = 0; i < layer_sizes.size() - 1; ++i) {
        vector<vector<double>> layer_weights(layer_sizes[i], vector<double>(layer_sizes[i + 1]));
        vector<double> layer_biases(layer_sizes[i + 1]);

        for (int j = 0; j < layer_sizes[i]; ++j) {
            for (int k = 0; k < layer_sizes[i + 1]; ++k) {
                layer_weights[j][k] = d(gen);
            }
        }

        for (int j = 0; j < layer_sizes[i + 1]; ++j) {
            layer_biases[j] = d(gen);
        }

        weights.push_back(layer_weights);
        biases.push_back(layer_biases);
    }
}

vector<vector<double>> forward_propagation(const vector<double>& input, const vector<vector<vector<double>>>& weights, const vector<vector<double>>& biases) {
    vector<vector<double>> activations;
    activations.push_back(input);

    for (size_t i = 0; i < weights.size(); ++i) {
        vector<double> new_activations(weights[i][0].size(), 0.0);

        for (size_t j = 0; j < weights[i].size(); ++j) {
            for (size_t k = 0; k < weights[i][j].size(); ++k) {
                new_activations[k] += activations.back()[j] * weights[i][j][k];
            }
        }

        for (size_t j = 0; j < new_activations.size(); ++j) {
            new_activations[j] = sigmoid(new_activations[j] + biases[i][j]);
        }

        activations.push_back(new_activations);
    }

    return activations;
}

void backward_propagation(const vector<double>& y_true, vector<vector<vector<double>>>& weights, vector<vector<double>>& biases, const vector<vector<double>>& activations, double learning_rate) {
    vector<vector<double>> deltas;
    vector<double> output_delta = mse_loss_derivative(y_true, activations.back());

    for (size_t i = 0; i < output_delta.size(); ++i) {
        output_delta[i] *= sigmoid_derivative(activations.back()[i]);
    }

    deltas.push_back(output_delta);

    for (int i = weights.size() - 1; i > 0; --i) {
        vector<double> layer_delta(weights[i].size(), 0.0);

        for (size_t j = 0; j < weights[i].size(); ++j) {
            for (size_t k = 0; k < weights[i][j].size(); ++k) {
                layer_delta[j] += deltas.back()[k] * weights[i][j][k];
            }
            layer_delta[j] *= sigmoid_derivative(activations[i][j]);
        }

        deltas.push_back(layer_delta);
    }

    reverse(deltas.begin(), deltas.end());

    for (size_t i = 0; i < weights.size(); ++i) {
        for (size_t j = 0; j < weights[i].size(); ++j) {
            for (size_t k = 0; k < weights[i][j].size(); ++k) {
                weights[i][j][k] -= learning_rate * activations[i][j] * deltas[i][k];
            }
        }

        for (size_t j = 0; j < biases[i].size(); ++j) {
            biases[i][j] -= learning_rate * deltas[i][j];
        }
    }
}

void train(vector<vector<double>>& X, vector<vector<double>>& y, int epochs, double learning_rate, const vector<int>& layer_sizes) {
    vector<vector<vector<double>>> weights;
    vector<vector<double>> biases;

    initialize_network(weights, biases, layer_sizes);

    for (int epoch = 0; epoch < epochs; ++epoch) {
        double loss = 0.0;

        for (size_t i = 0; i < X.size(); ++i) {
            vector<vector<double>> activations = forward_propagation(X[i], weights, biases);
            backward_propagation(y[i], weights, biases, activations, learning_rate);
            loss += mse_loss(y[i], activations.back());
        }

        if (epoch % 100 == 0) {
            cout << "Epoch " << epoch << ", Loss: " << loss / X.size() << endl;
        }
    }

    RenderWindow window(VideoMode(800, 800), "N00000000");

    Image im;
    im.loadFromFile("blank.jpg");

    for (int i = 0; i < 800; i++){
        for (int j = 0; j < 800; j++){
            vector<vector<double>> activations = forward_propagation({i/800.0, j/800.0}, weights, biases);
            if (activations.back()[0] >= 0.5){
                im.setPixel(i, 800-j, Color::Green);
            }
            else{
                im.setPixel(i, 800-j, Color::Red);
            }
        }
    }

    Texture t;
    t.loadFromImage(im);
    RectangleShape r(Vector2f(800, 800));
    r.setTexture(&t);
    window.draw(r);
    window.display();
    this_thread::sleep_for(chrono::seconds(60));  
}

int main() {
    vector<vector<double>> X = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    vector<vector<double>> y = {{0}, {1}, {1}, {0}};  // XOR problem

    vector<int> layer_sizes = {2, 3, 2, 1};  // Input layer, 2 hidden layers, output layer
    int epochs = 10000;
    double learning_rate = 0.1;

    train(X, y, epochs, learning_rate, layer_sizes);



    return 0;
}
