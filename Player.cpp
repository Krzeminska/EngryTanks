#include <windows.h>
#include <gl/gl.h>
#include "Player.h"
#include "Terrain.h"
#include "ResourceFactory.h"
#include "Bullet.h"
#include <math.h>

Player::Player(const Sprite &_sprite, float2 _position,
           float _orientation)
    :Tank(_sprite, _position, _orientation)
    ,left(false)
    ,right(false)
    ,firePressed(false)
    ,animacja(false)
    ,amunicja(5)
{
}

void Player::keyb(unsigned char k, bool down)
{
    switch (k)
    {
    case 'a':
        left = down; break;
    case 'd':
        right = down; break;
    case ' ':
        if (down)
        {
            if (!firePressed && amunicja > 0)
            {
                    ComponentManager::get().add(new Bullet(Sprite(ResourceFactory::get().load("assets\\bullet.bmp")),position + float2(orientation * .8f),orientation,2.f));
                    amunicja--;
                firePressed = true;
            }
        }
        else
            firePressed = false;
        break;
    }
}

void Player::update()
{
    bool isMoving = false;
    if (left && orientation < 90)
    {
        orientation += 1.5f;
        isMoving = true;
    }
    if (right && orientation > 0)
    {
        orientation -= 1.5f;
        isMoving = true;
    }
    if (isMoving) sprite.resume();
    else sprite.pause();
    sprite.update();
}
