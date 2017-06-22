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

    /**
     * @brief Instanciate a polynomial function with its coefficients (pairs : <coef, degree>).
     * @param The function's coefficients.
     */
    PolynomialFunction(vector<pair<float, float> *> * coefficients);

    /**
     * @brief Solves the polynomial function with a x value (f(x) = y).
     * @param x The x value to use.
     * @return The result of the function
     */
    float solve(float x);
};

class PolynomialFunctionBuilder
{
private:
    vector<pair<float, float> *> * coefficients;

public:
    PolynomialFunctionBuilder();

    /**
     * @brief Adds a coefficient (vx^d ; v = value, d = degree).
     * @param value The coefficient.
     * @param degree The degree.
     * @return Itself, the same PolynomialFunctionBuilder instance (Factory pattern).
     */
    PolynomialFunctionBuilder * addCoefficient(float value, float degree);

    /**
     * @brief Instanciates the PolynomialFunction object with the coefficients and degrees previously set.
     * @return The PolynomialFunction instance.
     */
    PolynomialFunction * build();
};

#endif // POLYNOMIALFUNCTION_H
