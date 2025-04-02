#ifndef FLAGZOMBIE_H
#define FLAGZOMBIE_H

#include "zombie.h"
#include "plant.h"

class FlagZombie : public Zombie
{
public:
    FlagZombie();
    void advance(int phase) override;
};

#endif
