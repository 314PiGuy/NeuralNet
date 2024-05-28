#include <iostream>
#include <vector>
#include <array>

#include "headers/Network.hpp"
#include "headers/Helper.hpp"


using namespace std;

Network train(Network net){
    for (int n = 0; n < net.layers.size(); n++){
        vector<vector<double>> changes;
        vector<double> v;
        for (int a = 0; a < net.layers[n].weights[0].size(); a++){
            v.push_back(0);
        }
        for (int a = 0; a < net.layers[n].weights.size(); a++){
            changes.push_back(v);
        }
        // for (int r = 0; r < net.layers[n].weights.size(); r++){
        //     for (int c = 0; c < net.layers[n].weights[0].size(); c++){
        //         cout << net.layers[n].weights[r][c] << " ";
        //     }
        //     cout << "\n";
        // }
        for (int r = 0; r < net.layers[n].weights.size(); r++){
            for (int c = 0; c < net.layers[n].weights[0].size(); c++){
                net.layers[n].weights[r][c] += 0.1;
                net.input({1, 1});
                net.calculate();
                double error = net.totalError({0.5, 0.5});
                net.layers[n].weights[r][c] -= 0.1;
                net.input({1, 1});
                net.calculate();
                double error2 = net.totalError({0.5, 0.5});
                double slope = (error-error2)*10;
                changes[r][c] = slope/10;
            }
        }
        for (int r = 0; r < net.layers[n].weights.size(); r++){
            for (int c = 0; c < net.layers[n].weights[0].size(); c++){
                net.layers[n].weights[r][c] -= changes[r][c];
            }
        }
        // cout << "\n";
        // for (int r = 0; r < net.layers[n].weights.size(); r++){
        //     for (int c = 0; c < net.layers[n].weights[0].size(); c++){
        //         cout << net.layers[n].weights[r][c] << " ";
        //     }
        //     cout << "\n";
        // }
        // cout <<"\n\n";
    }

    return net;
}



int main(){
    int l[] = {2, 4, 4, 4, 2};
    Network net = Network(l, 5);
    net.connect(2);
    net.input({1, 1});
    net.calculate();

    cout << net.layers.size() << "\n";
    
    for (Neuron n: net.layers[net.layers.size()-1].neurons){
        cout << n.value << "\n";
    }
    cout << net.totalError({0.5, 0.5})<< "\n\n";

    // for (int n = 0; n < net.layers.size(); n++){
    //     for (int r = 0; r < net.layers[n].weights.size(); r++){
    //         for (int c = 0; c < net.layers[n].weights[0].size(); c++){
    //             cout << net.layers[n].weights[r][c] << " ";
    //         }
    //         cout << "\n";
    //     }
    // }
    // cout << "\n";

    for (int i = 0; i < 10000; i++){
        net = train(net);
    }

    // for (int n = 0; n < net.layers.size(); n++){
    //     for (int r = 0; r < net.layers[n].weights.size(); r++){
    //         for (int c = 0; c < net.layers[n].weights[0].size(); c++){
    //             cout << net.layers[n].weights[r][c] << " ";
    //         }
    //         cout << "\n";
    //     }
    // }

    net.calculate();

    for (Neuron n: net.layers[net.layers.size()-1].neurons){
        cout << n.value << "\n";
    }
    cout << net.totalError({0.5, 0.5})<< "\n\n";
    return 0;
}