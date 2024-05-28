#include "headers/Network.hpp"

Network::Network(int l[]){
    for (int i = 0; i < sizeof(l)/sizeof(int); i++){
        Layer L(l[i]);
        layers.push_back(L);
    }
}

void Network::connect(int n){

    for (int i = 0; i < layers.size(); i++){
        Layer l = layers[i];
        if (i == 0) l.connect(n);
        else l.connect(layers[i-1].numneurons);
    }
}

vector<double> Network::calculate(){
    
}