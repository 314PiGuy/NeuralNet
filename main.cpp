#include <iostream>
#include <vector>
#include <array>

#include "headers/Network.hpp"
#include "headers/Helper.hpp"


using namespace std;



int main(){
    int l[] = {3, 2};
    Network net = Network(l);
    net.connect(2);

    return 0;
}