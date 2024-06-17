#include <iostream>
#include <vector>
#include <array>

#include "headers/Network.hpp"
#include "headers/Helper.hpp"
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;




Network train1(Network net, vector<double> in, vector<double> out){
    for (int n = 0; n < net.layers.size(); n++){
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
                net.layers[n].weights[r][c] -= slope*20;
            }
        }
        for (int r = 0; r < net.layers[n].biases.size(); r++){
            net.layers[n].biases[r] += 0.1;
            net.input(in);
            net.calculate();
            double error = net.totalError(out);
            net.layers[n].biases[r] -= 0.1;
            net.input(in);
            net.calculate();
            double error2 = net.totalError(out);
            double slope = (error-error2)*10;
            net.layers[n].biases[r] -= slope*20;
        }
    }

    return net;
}

Network train(Network net, vector<double> in, vector<double> out){
    net.input(in);
    net.calculate();
    net.backPropagate(out);
    for (int n = 0; n < net.layers.size(); n++){
        for (int r = 0; r < net.layers[n].biases.size(); r++){
            net.layers[n].biases[r] += 0.1;
            net.input(in);
            net.calculate();
            double error = net.totalError(out);
            net.layers[n].biases[r] -= 0.1;
            net.input(in);
            net.calculate();
            double error2 = net.totalError(out);
            double slope = (error-error2)*10;
            net.layers[n].biases[r] -= slope*20;
        }
    }
    return net;
}







int main(){

    RenderWindow window(VideoMode(800, 800), "N00000000");

    int l[] = {2, 3, 2};
    Network net = Network(l, 3, 50);
    net.connect(2);


    int L = 2;

  

    for (int i = 0; i < 1000; i++){
        for (int i = 0; i <= 1; i++){
            for (int j = 0; j <= 1; j++){
                net = train(net, {i/1.0f, j/1.0f}, {((int)(i!=j))/1.0f, 1-((int)(i!=j))/1.0f});
            }
        }
    }

    for (int i = 0; i < net.layers.size(); i++){
        for (int j = 0; j < net.layers[i].weights.size(); j++){
            net.layers[i].biases[j] += 0.1;
            net.input({1, 0});
            net.calculate();
            double error = net.totalError({1, 0});
            net.layers[i].biases[j] -= 0.1;
            net.input({1, 0});
            net.calculate();
            double error2 = net.totalError({1, 0});
            double slope = (error-error2)*10;
            cout << slope << "\n";
        }
    }
    cout << "\n";

    net.backPropagate({1, 0});

    for (int i = 0; i < net.layers.size(); i++){
        for (int j = 0; j < net.layers[i].weights.size(); j++){
            cout << net.layers[i].propBiases[j] << "\n";
        }
    }




    return 0;

    Image im;
    im.loadFromFile("blank.jpg");


    Texture t;
    t.loadFromImage(im);
    RectangleShape r(Vector2f(800, 800));
    r.setTexture(&t);
    window.draw(r);
    window.display();


    
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
        for (int i = 0; i < 800; i++){
            for (int j = 0; j < 800; j++){
                net.input({i/800.0f, j/800.0f});
                net.calculate();
                if (net.layers[net.layers.size()-1].neurons[0].value >= net.layers[net.layers.size()-1].neurons[1].value){
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
    }
    return 0;
}