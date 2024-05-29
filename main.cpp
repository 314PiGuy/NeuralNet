#include <iostream>
#include <vector>
#include <array>

#include "headers/Network.hpp"
#include "headers/Helper.hpp"


using namespace std;

Network train(Network net, vector<double> in, vector<double> out){
    for (int n = 0; n < net.layers.size(); n++){
        // vector<vector<double>> changes;
        // vector<double> v;
        // for (int a = 0; a < net.layers[n].weights[0].size(); a++){
        //     v.push_back(0);
        // }
        // for (int a = 0; a < net.layers[n].weights.size(); a++){
        //     changes.push_back(v);
        // }
        for (int r = 0; r < net.layers[n].weights.size(); r++){
            for (int c = 0; c < net.layers[n].weights[0].size(); c++){
                net.layers[n].weights[r][c] += 0.1;
                net.input(in);
                net.calculate();
                double error = net.totalError(out);
                net.layers[n].weights[r][c] -= 0.1;
                net.input(in);
                net.calculate();
                double error2 = net.totalError(out);
                double slope = (error-error2)*10;
                net.layers[n].weightChanges[r][c] = slope;
            }
        }
    }
    for (int n = 0; n < net.layers.size(); n++){
        for (int r = 0; r < net.layers[n].weights.size(); r++){
            for (int c = 0; c < net.layers[n].weights[0].size(); c++){
                net.layers[n].weights[r][c] -= net.layers[n].weightChanges[r][c];
            }
        }
    }

    return net;
}



int main(){
    int l[] = {2, 4, 4, 4, 1};
    Network net = Network(l, 5);
    net.connect(2);
    net.randomize();

    for (Layer l: net.layers){
        for (vector<double> r: l.weights){
            for (double d: r){
                cout << d << " ";
            }
        }
    }
    cout << "\n";

    for (int n = 0; n < 25; n++){
        for (int i = 0; i <= 1; i++){
            for (int j = 0; j <= 1; j++){
                train(net, {i/1.0, j/1.0}, {((int)(i!=j))/1.0});
            }
        }
    }

    while (1){
        int a;
        int b;
        cout << "First num ";
        cin >> a;
        cout << "\n";
        cout << "Second num ";
        cin >> b;
        cout << "\n";
        net.input({a/1.0, b/1.0});
        cout << net.layers[net.layers.size()-1].neurons.size() << "\n";
        for (int l = 0; l < net.layers.size(); l++){
            for (int n = 0; n < net.layers[l].neurons.size(); n++){
                cout << net.layers[l].neurons[n].value << "\n";
            }
        }
        cout << "\n";
        net.calculate();
        net.output({((int)(a!=b))/1.0});
        cout << "\n";
    }

    return 0;
}