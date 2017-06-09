#ifndef POLYNOMIALFUNCTION_H
#define POLYNOMIALFUNCTION_H

#include <math.h>
#include <vector>
#include <utility>

using namespace std;

class PolynomialFunction
{
private:
    vector<pair<float, float> *> coefficients;

public:
    PolynomialFunction(vector<pair<float, float> *> * coefficients);
    float solve(float x);
};

class PolynomialFunctionBuilder
{
private:
    vector<pair<float, float> *> * coefficients;

public:
    PolynomialFunctionBuilder();
    PolynomialFunctionBuilder * addCoefficient(float value, float degree);
    PolynomialFunction * build();
};

#endif // POLYNOMIALFUNCTION_H
