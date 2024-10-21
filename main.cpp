#include <iostream>
#include <vector>
#include <array>
#include <random>

#include "headers/Network.hpp"
#include "headers/Helper.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "[";
    for (int i = 0; i < v.size(); ++i)
    {
        os << v[i];
        if (i != v.size() - 1)
            os << ", ";
    }
    os << "]";
    return os;
}

Network initialize(Network net)
{
    random_device rd;
    mt19937 gen(rd());
    for (int i = 0; i < net.layers.size(); i++)
    {
        int inputs = net.layers[i].weights[0].size();
        int outputs = net.layers[i].weights.size();
        float dist = sqrt(2 / inputs + outputs);
        // float dist = 1;
        normal_distribution<> d(-1 * dist, dist);
        for (int j = 0; j < net.layers[i].weights.size(); j++)
        {
            for (int k = 0; k < net.layers[i].weights[j].size(); k++)
            {
                net.layers[i].weights[j][k] = d(gen);
            }
        }
    }
    return net;
}

int main()
{

    Network net = Network({Layer(2, reLU), Layer(4, reLU), Layer(2, reLU)}, 0.001);
    net.connect(2);

    net.randomize();

    // for (auto& a : net.layers[0].weights)
    // {
    //     for (auto& b : a)
    //     {
    //         b = 0;
    //     }
    // }

    // vector<vector<double>> in = {{5.7, 2.3}, {3.1, 1.9}, {10.4, 4.7}, {0.8, 6.5}};
    vector<vector<double>> in = {{2, 3}, {0, 4}, {1, 9}, {10, 2}};
    vector<vector<double>> out = {{4, 2}, {1, 7}, {0, 6}, {9, 11}};


    // net.layers[1].weights = {{3, 2}, {4, 5}};
    // net.layers[0].neurons = {0, 0};
    // net.layers[1].biases = {0, 0};
    // net.layers[1].neurons = {0, 0};
    // net.layers[2].weights = {{1.3, -0.217}, {0.62, 2.4}};
    // net.layers[2].biases = {0.12, -3.7};

    // for (Layer l: net.layers){
    //     cout << l.neurons << "\n";
    // }

    net.train(in, out, MSE, 300000);

    for (Layer l : net.layers)
    {
        cout << l.weights << "\n\n";
    }

    for (auto a : in)
    {
        auto r = net.predict(a);
        cout << r << "\n";
    }

    return 0;

    RenderWindow window(VideoMode(800, 800), "N00000000");

    Image im;
    im.loadFromFile("blank.jpg");
    Texture t;

    int count = 0;

    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        // for (int i = 0; i <= 1; i++){
        //     for (int j = 0; j <= 1; j++){
        //         net = train(net, {i/1.0f, j/1.0f}, {((int)(i!=j))/1.0f, 1-((int)(i!=j))/1.0f});
        //     }
        // }
        // if (count = 999){
        //     net.input({1, 1});
        //     net.calculate();
        //     cout << net.totalError({0, 1}) << "\n";
        //     count = 0;
        // }
        for (int i = 0; i < 800; i++)
        {
            for (int j = 0; j < 800; j++)
            {
                net.input({i / 800.0f, j / 800.0f});
                net.calculate();
                if (net.layers.back().neurons[0] >= 0.5)
                {
                    im.setPixel(i, 800 - j, Color::Green);
                }
                else
                {
                    im.setPixel(i, 800 - j, Color::Red);
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