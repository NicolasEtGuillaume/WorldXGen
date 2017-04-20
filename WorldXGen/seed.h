#ifndef SEED_H
#define SEED_H

#define DEFAULT_SEED_SIZE   16

#include <random>
#include <string>

using namespace std;

class Seed
{
public:
    unsigned int * seedValue;

    /**
     * @brief Instantiates a Seed object, randomly generates the seed.
     */
    Seed();

    /**
     * @brief Instantiates a Seed object according to the given seed string.
     * @param seed The seed string to use.
     */
    Seed(string seed);

    /**
     * @brief Destroys the object, frees the memory used for the seed value.
     */
    ~Seed();
};

#endif // SEED_H
