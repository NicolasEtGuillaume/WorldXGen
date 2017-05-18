#include "seed.h"

Seed::Seed()
{
    this->seedValue = (unsigned int *) malloc(sizeof(unsigned int) * DEFAULT_SEED_SIZE);

    default_random_engine randomGenerator;
    uniform_int_distribution<int> distribution(0, 9);

    // Generates an integer for each index.
    for (unsigned int i = 0; i < DEFAULT_SEED_SIZE; ++i)
    {
        this->seedValue[i] = distribution(randomGenerator);
    }
}

Seed::Seed(string seed)
{
    this->seedValue = (unsigned int *) malloc(sizeof(unsigned int) * DEFAULT_SEED_SIZE);

    unsigned int i;

    // Initializes all indexes with 0.
    for (i = 0; i < DEFAULT_SEED_SIZE; ++i)
    {
        this->seedValue[i] = 0;
    }

    // Adds the values of all letters.
    for (i = 0; i < seed.length(); ++i)
    {
        unsigned char c = seed.at(i);
        this->seedValue[i % 16] += (unsigned int) c;
    }
}

unsigned int Seed::getValue()
{
    unsigned int r = 0;

    for (unsigned int i = 0; i < DEFAULT_SEED_SIZE; ++i)
    {
        unsigned int tempVal = this->seedValue[i];
        unsigned int n = 0;
        do {
            tempVal /= 10;
            ++n;
        } while (tempVal > 0);

        r += r * ((unsigned int) pow(10, n)) + this->seedValue[i];
    }

    return r;
}

Seed::~Seed()
{
    free(this->seedValue);
}
