#include <iostream>
#include <vector>
#include <array>

#include "headers/Network.hpp"
#include "headers/Helper.hpp"


using namespace std;

Network train(Network net, vector<double> in, vector<double> out){
    for (int n = 0; n < net.layers.size(); n++){
        vector<vector<double>> changes;
        vector<double> v;
        for (int a = 0; a < net.layers[n].weights[0].size(); a++){
            v.push_back(0);
        }
        for (int a = 0; a < net.layers[n].weights.size(); a++){
            changes.push_back(v);
        }
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
                changes[r][c] = slope/15;
            }
        }
        for (int r = 0; r < net.layers[n].weights.size(); r++){
            for (int c = 0; c < net.layers[n].weights[0].size(); c++){
                net.layers[n].weights[r][c] -= changes[r][c];
            }
        }
    }

    return net;
}



int main(){
    int l[] = {2, 10, 10, 2};
    Network net = Network(l, 4);
    net.connect(2);

    net.input({6, 6});
    net.calculate();
    cout << net.totalError({1, 0})<< "\n\n";

    for (double i = 1; i <= 100; i++){
        for (double j = 1; j <= 100; j++){
            vector<double> v;
            (fmod(i+j, 2)==0) ? v = {1.0, 0.0}: v={0.0, 1.0};
            for (int n = 0; n < 25; n++){
                net = train(net, {i, j}, v);
            }
        }
    }

    net.input({5, 5});
    net.calculate();
    cout << net.totalError({1, 0})<< "\n\n";

    net.input({7, 92});
    net.calculate();
    cout << net.totalError({1, 0})<< "\n\n";

    net.input({18, 6});
    net.calculate();
    cout << net.totalError({1, 0})<< "\n\n";

    net.input({12, 14});
    net.calculate();
    cout << net.totalError({1, 0})<< "\n\n";

    net.input({51, 56});
    net.calculate();
    cout << net.totalError({1, 0})<< "\n\n";
    return 0;
}