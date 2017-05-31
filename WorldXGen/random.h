#ifndef RANDOM_H
#define RANDOM_H

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

class Random
{
public:
    /**
     * @brief Generates a floating point number between 0 and 1, following a uniform distribution.
     * @return The randomly generated number.
     */
    static float Random::uniformDistribution();

    /**
     * @brief Generates a floating point number between 0 and 1, following a uniform distribution.
     * @param seed The seed to use for the generation.
     * @return The randomly generated number.
     */
    static float Random::uniformDistribution(unsigned int seed);

    /**
     * @brief Generates a floating point number between the given bounds, following a uniform distribution.
     * @return The randomly generated number.
     */
    static float Random::uniformDistribution(int lowerBound, int upperBound);

    /**
     * @brief Generates a floating point number between the given bounds, following a uniform distribution.
     * @param seed The seed to use for the generation.
     * @return The randomly generated number.
     */
    static float Random::uniformDistribution(unsigned int seed, int lowerBound, int upperBound);

    /**
     * @brief Generates a floating point number, following a normal distribution.
     * @param seed The seed to use for the generation.
     * @param mu The mu parameter.
     * @param sigma The sigma parameter.
     * @return The randomly generated number.
     */
    static float Random::normalDistribution(unsigned int seed, float mu, float sigma);
};

#endif // RANDOM_H
