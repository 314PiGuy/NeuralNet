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

double sigmoid(double d, bool b)
{
    if (b)
    {
        return d * (1 - d);
    }
    return 1 / (1 + pow(2.718, -d));
}

vector<double> MSE(vector<double> a, vector<double> b)
{
    vector<double> r;
    int s = a.size();
    for (int i = 0; i < s; i++)
    {
        r.push_back(2 * (a[i] - b[i]) / s);
    }
    return r;
}