#ifndef SPRITETEXT_H
#define SPRITETEXT_H

#include "Sprite.h"

#include <string>

using std::string;

class SpriteText
{
    public:
        SpriteText(const Sprite&);
        virtual ~SpriteText();

        virtual void draw(float2, float, float);
        void setPos(float2 p) {pos = p;}
        virtual void draw(float, float);

        virtual void setText(const char *);
        virtual void setText(const char *, int);
        virtual void setText(int,const char *);

        virtual void setColor(float, float, float);
    protected:
        string text;
        Sprite sprite;
        float color[3];
        float2 pos;
    private:
};

#endif // SPRITETEXT_H
