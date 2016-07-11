#include <windows.h>
#include <gl/gl.h>

#include "Sprite.h"

Sprite::Sprite(Texture2D *source, int _frameCount /* =1 */,
               float _fps /* =24.f */)
    :texture(source)
    ,frameCount(_frameCount)
    ,rangeStart(0)
    ,rangeEnd(_frameCount-1)
    ,currentFrame(0.f)
    ,state(PAUSED)
    ,fps(_fps)
    ,lastTime( GetTickCount() )
{
}

void Sprite::draw(float2 position, float orientation, float scale)
{
    texture->bind();
    glPushMatrix();
    glTranslatef(position.x, position.y, 0.f);
    glRotatef(orientation, 0.f,0.f,1.f);
    glScalef(scale, scale, 1.f);
    glBegin(GL_QUADS);
        glTexCoord2f( (int)currentFrame/(float)frameCount, 0.f);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glTexCoord2f( (int)currentFrame/(float)frameCount, .99f);
        glVertex3f(-0.5f,  0.5f, 0.0f);
        glTexCoord2f( (.99f+(int)currentFrame)/(float)frameCount, .99f);
        glVertex3f( 0.5f,  0.5f, 0.0f);
        glTexCoord2f( (.99f+(int)currentFrame)/(float)frameCount, 0.f);
        glVertex3f( 0.5f, -0.5f, 0.0f);
    glEnd();
    glPopMatrix();
}

void Sprite::update()
{
    if (state == PLAYING)
    {
        currentFrame += fps*(GetTickCount()-lastTime)/1000.f;
        if (currentFrame > rangeEnd+1)
            currentFrame = rangeStart;
        lastTime = GetTickCount();
    }
}

void Sprite::play(int start /* =0 */, int end /* =-1 */)
{
    currentFrame = rangeStart = start;
    rangeEnd = end != -1 ? end : frameCount - 1;
    state = PLAYING;
}
