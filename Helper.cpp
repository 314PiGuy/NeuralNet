#include "headers/Helper.hpp"

vector<double> matrixMult(vector<vector<double>> a, vector<double> b){
    if (a[0].size() != b.size()){
        return {{0}};
    }

    vector<double> v;


    for (int i = 0; i < a.size(); i++){
        v.push_back(0);
    }


    for (int i = 0; i < a.size(); i++){
        
        for (int k = 0; k < a[0].size(); k++){
            v[i] += a[i][k]*b[k];
        }
    }

    return v;
}

double sigmoid(double d){
    return 1/(1+pow(2.718, -d));
}

double sigmoidDerivative(double d){
    double top = pow(2.718, -d);
    double bottom = (1+pow(2.718, -d))*(1+pow(2.718, -d));
    return top/bottom;
}
vector<vector<double>> matFlip(vector<vector<double>> a){
    vector<double> v;
    vector<vector<double>> a2;
    for (int i = 0; i < a.size(); i++){
        v.push_back(0);
    }
    for (int i = 0; i < a[0].size(); i++){
        a2.push_back(v);
    }
    for (int r = 0; r < a.size(); r++){
        for (int c = 0; c < a[0].size(); c++){
            a2[c][r] = a[r][c];
        }
    }
    return a2;
}