#include <windows.h>

#include "Bullet.h"
#include "ResourceFactory.h"
#include "Terrain.h"
#include "Enemy.h"
#include "Tank.h"

Bullet::Bullet(const Sprite &_sprite, float2 _position,
               float _orientation, float _speed)
    :Entity(_sprite, _position, _orientation)
{
    velocity = float2(_orientation) * _speed;
  //  radius = .15f;
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
    position += velocity * .05f;
    //position = float2(0, -.2f) * .5f + velocity * .5f;
    Enemy *e = collisionWithE<Enemy>(this);
    if (e!=NULL)
    {
        this->kill();
        e->hit(orientation,velocity);
    }
    float2 coll( Terrain::get().collisionWith('#', position, float2(.5f, .5f)));
    float2 coll2( Terrain::get().collisionWith('H', position, float2(.5f, .5f)));
    if (!coll.isZero() || !coll2.isZero())
    {
        this->kill();
    }

    /*
    if (!Terrain::get().collision('h', position, radius).isZero()
        )
        deleted = true;
        */
}

void Bullet::draw()
{
    sprite.draw(position, orientation, .5f);
}
