#include "headers/Helper.hpp"

vector<double> matrixMult(vector<vector<double>> a, vector<double> b)
{
    if (a[0].size() != b.size())
    {
        return {{0}};
    }

    vector<double> v;

    for (int i = 0; i < a.size(); i++)
    {
        v.push_back(0);
    }

    for (int i = 0; i < a.size(); i++)
    {

        for (int k = 0; k < a[0].size(); k++)
        {
            v[i] += a[i][k] * b[k];
        }
    }

    return v;
}

double sigmoidA(double d)
{
    return 1 / (1 + pow(2.718, -d));
}

double sigmoidB(double d)
{
    return d * (1 - d);
}

double reLUA(double d)
{
    if (d > 0)
        return d;
    return 0;
}

double reLUB(double d){
    if (d >= 0) return 1;
    return 0;
}

vector<double> MSE(vector<double> a, vector<double> b)
{
    vector<double> r;
    double s = double(a.size());
    for (int i = 0; i < s; i++)
    {
        r.push_back((2 * (a[i] - b[i])) / s);
    }
    return r;
}