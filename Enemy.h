#ifndef ENEMY_H
#define ENEMY_H

#include "Tank.h"

class Enemy : public Tank
{
public:
    Enemy(const Sprite &, float2, float);//, Entity *);
    virtual ~Enemy() {}

    bool finded;

    virtual void update();
    void hit(float o,float2 v) { orientation=o; velocity=v; strike=true; }
    int time() {if(x) return (5 - ((::GetTickCount()/1000) - timeOut)); return 0;}
    float2 printPos() {return position;}
protected:
    bool strike, x;
    int movingDir;
    int timeOut;
private:
};

#endif // ENEMY_H
