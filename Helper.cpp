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