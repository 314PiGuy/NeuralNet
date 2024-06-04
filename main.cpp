#include <iostream>
#include <vector>
#include <array>

#include "headers/Network.hpp"
#include "headers/Helper.hpp"
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

Network train(Network net, vector<double> in, vector<double> out){
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
                net.layers[n].weightChanges[r][c] = slope*25;
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
            net.layers[n].biasChanges[r] = slope*25;
        }
    }
    for (int n = 0; n < net.layers.size(); n++){
        for (int r = 0; r < net.layers[n].weights.size(); r++){
            for (int c = 0; c < net.layers[n].weights[0].size(); c++){
                // cout << net.layers[n].weightChanges[r][c] << "\n";
                net.layers[n].weights[r][c] -= net.layers[n].weightChanges[r][c];
            }
        }
    }
    for (int n = 0; n < net.layers.size(); n++){
        for (int r = 0; r < net.layers[n].biases.size(); r++){
            net.layers[n].biases[r] -= net.layers[n].biasChanges[r];
        }
    }

    return net;
}

Network train1(Network net, vector<double> in, vector<double> out){
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
                net.input(in);
                net.calculate();
                double error = net.totalError(out);
                net.layers[n].weights[r][c] -= 0.1;
                net.input(in);
                net.calculate();
                double error2 = net.totalError(out);
                double slope = (error-error2)*10;
                net.layers[n].weights[r][c] -= slope*10;
                changes[r][c] = slope*10;
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
        // for (int r = 0; r < net.layers[n].weights.size(); r++){
        //     for (int c = 0; c < net.layers[n].weights[0].size(); c++){
        //         net.layers[n].weights[r][c] -= changes[r][c];
        //     }
        // }
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

    RenderWindow window(VideoMode(800, 800), "N00000000");

    int l[] = {2, 3, 2};
    Network net = Network(l, 3);
    net.connect(2);
    // net.randomize();



    net.input({0, 0});
    net.calculate();
    net.output({0, 1});

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
                net = train(net, {i/1.0, j/1.0}, {((int)(i!=j))/1.0, 1-((int)(i!=j))/1.0});
            }
        }
        for (int i = 0; i < 800; i++){
            for (int j = 0; j < 800; j++){
                net.input({i/800.0, j/800.0});
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