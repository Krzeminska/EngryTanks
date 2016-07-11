#include <windows.h>

#include "Enemy.h"

#include "ResourceFactory.h"
#include "Terrain.h"
#include "Bullet.h"
#include "Entity.h"
#include "Tank.h"

Enemy::Enemy(const Sprite &_sprite, float2 _position,
             float _orientation)//, Entity *_target)
             :Tank(_sprite, _position, _orientation)
             ,strike(false)
             ,movingDir(-1)
             ,finded(false)
            //    ,target(_target)
{

}


void Enemy::update()
{
    if(strike)
    {
        timeOut = ::GetTickCount()/1000;
        x = true;
        strike = false;
    }
    if(x)
    {

        velocity = float2(.04f, -.2f);
        position += velocity;
        float2 coll( Terrain::get().collisionWithNot('H', position, float2(.5f, .5f)));
        if (!coll.isZero())
        {
            position+=coll;
        }
        float2 coll2( Terrain::get().collisionWithNot('#', position, float2(.5f, .5f)));
        if (!coll2.isZero())
        {
            position+=coll2;
            velocity = 0;
            if((::GetTickCount()/1000) - timeOut > 5) {
                x = false;
                this->kill();

            }

        }
        Entity *e = collisionWithE<Tank>(this);
        if (e != NULL)
            position += collisionSeparate(e, position, velocity, orientation);
        sprite.resume();
        //if (coll2.x!=0) movingDir =- movingDir;
        sprite.update();
    }



}
