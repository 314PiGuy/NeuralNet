#include <iostream>
#include <vector>
#include <array>
#include <random>

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
                net.layers[n].weights[r][c] -= slope*10;
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
            net.layers[n].biases[r] -= slope*10;
        }
    }

    return net;
}

Network train(Network net, vector<double> in, vector<double> out){
    // for (int n = 0; n < net.layers.size(); n++){
    //     net.input(in);
    //     net.backPropagate(out);
    //     for (int r = 0; r < net.layers[n].weights.size(); r++){
    //         for (int c = 0; c < net.layers[n].weights[0].size(); c++){
    //             net.layers[n].weights[r][c] -= net.layers[n].propWeights[r][c]*20;
    //         }
    //     }
    //     for (int r = 0; r < net.layers[n].biases.size(); r++){
    //         net.layers[n].biases[r] -= net.layers[n].propBiases[r]*20;
    //     }
    // }
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

    int l[] = {2, 3, 2, 1};
    Network net = Network(l, 4, 0.1);
    net.connect(2);

    net = initialize(net);





  

    for (int i = 0; i < 100000; i++){
        for (int i = 0; i <= 1; i++){
            for (int j = 0; j <= 1; j++){
                net = train(net, {i/1.0f, j/1.0f}, {((int)(i!=j))/1.0f, 1-((int)(i!=j))/1.0f});
            }
        }
    }

    // for (int i = 0; i < 1000; i++){
    //     for (int i = 0; i <= 1; i++){
    //         for (int j = 0; j <= 1; j++){
    //             net = train1(net, {i/1.0f, j/1.0f}, {((int)(i!=j))/1.0f, 1-((int)(i!=j))/1.0f});
    //         }
    //     }
    // }

    // for (int i = 0; i < net.layers.size(); i++){
    //     for (int j = 0; j < net.layers[i].weights.size(); j++){
    //         // for (int k = 0; k < net.layers[i].weights[0].size(); k++){
    //         //     cout << net.layers[i].weights[j][k] << "\n";
    //         // }
    //         cout << net.layers[i].biases[j] << "\n";
    //     }
    // }
    // cout << "\n";
    // for (int i = 0; i < net.layers.size(); i++){
    //     for (int j = 0; j < net.layers[i].weights.size(); j++){
    //         // for (int k = 0; k < net.layers[i].weights[0].size(); k++){
    //         //     cout << net.layers[i].weights[j][k] << "\n";
    //         // }
    //         cout << net.layers[i].biases[j] << "\n";
    //     }
    // }

    // double L = 0.0;
    // for (int c = 0; c < 100000; c++){
    //     double loss = 0.0;
    //     for (int i = 0; i <= 1; i++){
    //         for (int j = 0; j <= 1; j++){
    //             net = train(net, {i/1.0f, j/1.0f}, {((int)(i!=j))/1.0f, 1-((int)(i!=j))/1.0f});
    //             loss += net.totalError({((int)(i!=j))/1.0f, 1-((int)(i!=j))/1.0f});
    //         }
    //     }
    //     L = loss;
    // }

    // cout << L << endl;

    // return 0;

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
                if (net.layers.back().neurons[0].value >= 0.5){
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