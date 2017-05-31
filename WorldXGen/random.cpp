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

float Random::normalDistribution(unsigned int seed)
{
    float u1, u2;
    srand(seed);
    u1 = Random::uniformDistribution();
    u2 = Random::uniformDistribution();
    return (float) (sqrt(-2 * log(u1)) * cos(2 * M_PIl * u2));

}
