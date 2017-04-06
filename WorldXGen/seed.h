#ifndef SEED_H
#define SEED_H

#include <string>

using namespace std;

class Seed
{
public:
    string fixedPart;
    string randomPart;

    Seed();
    Seed(string seed);
};

#endif // SEED_H
