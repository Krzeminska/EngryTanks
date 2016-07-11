#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet : public Entity
{
    public:
        Bullet(const Sprite &, float2, float, float);
        virtual ~Bullet();

        void update();
        void draw();

    protected:
    private:
};

#endif // BULLET_H
