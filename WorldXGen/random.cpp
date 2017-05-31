#include "random.h"
# define M_PIl          3.141592653589793238462643383279502884L

float Random::uniformDistribution() {
    return ((float) rand()) / RAND_MAX;
}

float Random::uniformDistribution(unsigned int seed)
{
    srand(seed);
    return Random::uniformDistribution();
}

float Random::uniformDistribution(int lowerBound, int upperBound)
{
    return Random::uniformDistribution() * (upperBound - lowerBound) + lowerBound;
}

float Random::uniformDistribution(unsigned int seed, int lowerBound, int upperBound)
{
    return Random::uniformDistribution(seed) * (upperBound - lowerBound) + lowerBound;
}

float Random::normalDistribution(float mu, float sigma)
{
    // Boc-Muller's method. Inspired by FunK92's code (https://openclassrooms.com/forum/sujet/random-gaussien-54777).
    float u1 = Random::uniformDistribution(-1, 1),
        u2 = Random::uniformDistribution(-1, 1),
        y;

    y = powf(-2.f * logf(u1), 0.5f) * cosf(6.f * u2);

    return mu + sigma * y;

}


float Random::normalDistribution(unsigned int seed, float mu, float sigma)
{
    srand(seed);
    return Random::normalDistribution(mu, sigma);
}
