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

    Seed();
    Seed(string seed);
    ~Seed();
};

#endif // SEED_H
