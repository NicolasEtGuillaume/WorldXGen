#include "polynomialfunction.h"

// ---- PolynomialFunction

PolynomialFunction::PolynomialFunction(vector<pair<float, float> *> * coefficients)
{
    this->coefficients = *coefficients;
}

float PolynomialFunction::solve(float x)
{
    float result = 0.f;
    for (pair<float, float> * p : this->coefficients)
    {
        float a = p->first;
        float degree = p->second;
        result += a * powf(x, degree);
    }
    return result;
}

// ---- PolynomialFunctionBuilder

PolynomialFunctionBuilder::PolynomialFunctionBuilder()
{
    this->coefficients = new vector<pair<float, float> *>();
}

PolynomialFunctionBuilder * PolynomialFunctionBuilder::addCoefficient(float value, float degree)
{
    this->coefficients->push_back(new pair<float, float>(value, degree));
    return this;
}

PolynomialFunction * PolynomialFunctionBuilder::build()
{
    return new PolynomialFunction(this->coefficients);
}
