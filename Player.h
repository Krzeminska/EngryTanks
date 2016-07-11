#ifndef PLAYER_H
#define PLAYER_H

#include "Tank.h"

class Player : public Tank
{
    public:
        bool animacja;
        Player(const Sprite &, float2, float);
        virtual ~Player() {}

        virtual void update();

        bool looser() { if(amunicja == 0) return true; return false;}
        int stan() {return amunicja;}

        void keyb(unsigned char, bool);
    protected:
        bool left, right;
        bool firePressed;
        int amunicja;
    private:
};

#endif // PLAYER_H
