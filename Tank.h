#ifndef TANK_H
#define TANK_H

#include "Entity.h"

class Tank : public Entity
{
    public:
        Tank(const Sprite &, float2, float);
        virtual ~Tank() {}
    protected:
    private:
};

#endif // TANK_H
