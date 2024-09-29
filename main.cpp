#include <iostream>
#include <vector>
#include <array>
#include <random>

#include "headers/Network.hpp"
#include "headers/Helper.hpp"
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;




Network train(Network net, vector<double> in, vector<double> out){
    net.input(in);
    net.backPropagate(out);
    return net;
}

Network initialize(Network net){
    random_device rd;
    mt19937 gen(rd());
    for (int i = 0; i < net.layers.size(); i++){
        int inputs = net.layers[i].weights[0].size();
        int outputs = net.layers[i].weights.size();
        float dist = sqrt(2/inputs+outputs);
        // float dist = 1;
        normal_distribution<> d(-1*dist, dist);
        for (int j = 0; j < net.layers[i].weights.size(); j++){
            for (int k = 0; k < net.layers[i].weights[j].size(); k++){
                net.layers[i].weights[j][k] = d(gen);
            }
        }
    }
    return net;
}







int main(){

    RenderWindow window(VideoMode(800, 800), "N00000000");

    Network net = Network({Layer(2, sigmoid), Layer(3, sigmoid), Layer(2, sigmoid), Layer(1, sigmoid)}, 0.1);
    net.connect(2);

    net.randomize();

    vector<vector<double>> in = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    vector<vector<double>> out = {{0}, {1}, {1}, {0}};

    net.train(in, out, 1000000);
  

    // for (int i = 0; i < 100000; i++){
    //     for (int i = 0; i <= 1; i++){
    //         for (int j = 0; j <= 1; j++){
    //             net = train(net, {i/1.0f, j/1.0f}, {((int)(i!=j))/1.0f, 1-((int)(i!=j))/1.0f});
    //         }
    //     }
    // }


    Image im;
    im.loadFromFile("blank.jpg");
    Texture t;

    int count = 0;
    
    while (window.isOpen())
    {
        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed){
                window.close();
            }

        }

        window.clear();

        for (int i = 0; i <= 1; i++){
            for (int j = 0; j <= 1; j++){
                net = train(net, {i/1.0f, j/1.0f}, {((int)(i!=j))/1.0f, 1-((int)(i!=j))/1.0f});
            }
        }
        // if (count = 999){
        //     net.input({1, 1});
        //     net.calculate();
        //     cout << net.totalError({0, 1}) << "\n";
        //     count = 0;
        // }
        for (int i = 0; i < 800; i++){
            for (int j = 0; j < 800; j++){
                net.input({i/800.0f, j/800.0f});
                net.calculate();
                if (net.layers.back().neurons[0] >= 0.5){
                    im.setPixel(i, 800-j, Color::Green);
                }
                else{
                    im.setPixel(i, 800-j, Color::Red);
                }
            }
        }
        t.loadFromImage(im);
        RectangleShape r(Vector2f(800, 800));
        r.setTexture(&t);
        window.draw(r);
        window.display();
        count++;
    }
    return 0;
}