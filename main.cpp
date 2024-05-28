#include <iostream>
#include <vector>
#include <array>

#include "headers/Network.hpp"
#include "headers/Helper.hpp"


using namespace std;



int main(){
    int l[] = {2, 3, 2};
    Network net = Network(l);
    net.connect(2);
    net.input({1, 1});
    net.calculate();
    for (Neuron n: net.layers[2].neurons){
        cout << n.value << "\n";
    }
    return 0;
}