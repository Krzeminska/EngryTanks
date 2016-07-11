#ifndef SPRITE_H
#define SPRITE_H

#include "float2.h"

#include "Texture2D.h"

class Sprite
{
    public:
        Sprite(Texture2D *source, int = 1, float = 24.f);
        ~Sprite() {}

        void update();

        void draw(float2 position,
            float orientation = 0.f,
            float scale = 1.f);

        void play(int =0, int =-1);
        void pause() { state = PAUSED; }
        void resume() { state = PLAYING; }

    protected:
        Texture2D *texture;
        int frameCount, rangeStart, rangeEnd;
        float currentFrame;
        enum { PAUSED, PLAYING } state;
        float fps;
        unsigned int lastTime;
    private:
};

#endif // SPRITE_H
