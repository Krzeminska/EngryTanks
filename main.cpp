#include <windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <gl/glut.h>

#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ostringstream;

#include "Sprite.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "ComponentManager.h"
#include "ResourceFactory.h"
#include "Terrain.h"
#include "SpriteText.h"

int screenWidth = 800, screenHeight = 600;

enum GameState
{
    PLAY, GAMEOVER, YOUWON, LEVELSTART, LEVELFINISHED, TIMEEND
} gameState = LEVELSTART;

Sprite *gameOver;
Sprite *youWon;

void Winning()
{
	Beep(300, 400);
	Beep(350, 200);
	Beep(400, 200);
	Beep(450, 200);
	Beep(500, 200);
    Beep(550, 200);
	Beep(600, 200);
	Beep(650, 200);
	Beep(700, 200);
}
void Winning2()
{
	Beep(560, 500); //e
	Beep(610, 375); //fis
	Beep(560, 125); //e
	Beep(525, 500); //cis
	Beep(525, 500);

    Beep(525, 375); //cis
	Beep(475, 125); //h
	Beep(525, 375);
	Beep(550, 125); //d
	Beep(525, 1000); //cis

	Beep(550, 500);
	Beep(475, 375);
	Beep(600, 125);
	Beep(525, 1000);

	Beep(425, 500); //a
	Beep(350, 375); //fis
	Beep(475, 125); //h
	Beep(310, 1000); //e
	exit(0);
}
void Smutek()
{
    Beep(700, 200);
	Beep(650, 200);
	Beep(600, 200);
    Beep(550, 200);
	Beep(500, 200);
	Beep(450, 200);
	Beep(400, 200);
	Beep(350, 200);
	Beep(300, 400);
}

SpriteText *levelStart;
SpriteText *time;
SpriteText *amunicja;
SpriteText *przeterminowanie;
SpriteText *agony[3];

int timeOut = ::GetTickCount()+3000;
int timeOut2;
int currentLevel = 1;
const int maxLevel = 2;
int music = -1;

void end(void)
{
    cout<<"Game terminated"<<endl;
}

void renderScene(void) {
    glClearColor(.5f, .5f, .5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.f, 0.f, -1.f);
    glPushMatrix();
        Terrain::get().draw();
        ComponentManager::get().draw();
    glPopMatrix();
    switch (gameState)
    {
    case PLAY:
        time->draw(float2(-10.f,7.f), 0, .8f);
        amunicja->draw(float2(-10.f,-7.f), 0, .8f);
        agony[0]->draw(0, .8f);
        agony[1]->draw(0, .8f);
        agony[2]->draw(0, .8f);
        break;
    case GAMEOVER:
        gameOver->draw(float2(0,0), 0.f, 16.f);
        break;
    case YOUWON:
        youWon->draw(float2(0,0), 0.f, 16.f);
        break;
    case LEVELSTART:
        levelStart->draw(float2(-9.f,0.f), 0, 2.5f);
        break;
    case TIMEEND:
        przeterminowanie->draw(float2(-9.f,0.f), 0, 1.2f);
        break;
    }
    glutSwapBuffers();
}

void keyb(unsigned char k, int, int)
{
    switch (k)
    {
    case 27:
        cout<<"Shutdown by Escape"<<endl;
        exit(EXIT_SUCCESS);
    }
    Player *p;
    ComponentManager::get().find<Player>();
    p = ComponentManager::get().next<Player>();
    if (p!=NULL)
        p->keyb(k, true);
}

void keybUp(unsigned char k, int, int)
{
    Player *p;
    ComponentManager::get().find<Player>();
    p = ComponentManager::get().next<Player>();
    if (p!=NULL)
        p->keyb(k, false);
}


void resize(int wid, int hei)
{
    screenWidth = wid;
    //screenHeight = hei ? hei : 1;
    screenHeight = hei;
    glViewport(0, 0, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const float scale = 8.f; //9.5f+
    glOrtho(-scale*(float)wid/(float)hei*.98f, scale*(float)wid/(float)hei*.98f, -scale, scale, .1f, 10.f);
    glMatrixMode(GL_MODELVIEW);
}

void idle()
{
    switch (gameState)
    {
    case PLAY:
        {
            ComponentManager::get().update();
            ComponentManager::get().find<Player>();
            Player *p = ComponentManager::get().next<Player>();
            if ( p==NULL )
            {
                gameState = GAMEOVER;
                timeOut = ::GetTickCount() + 4000;

            }
            //wygrana
            else if (ComponentManager::get().count<Enemy>()==0)
            {
                gameState = LEVELFINISHED;
                //timeOut = ::GetTickCount() + 4000;
            }
            //przegrana:
            else if (p->looser())
            {
                ComponentManager::get().find<Bullet>();
                Bullet *b = ComponentManager::get().next<Bullet>();
                if ( b==NULL )
                {
                    gameState = GAMEOVER;
                    //timeOut = ::GetTickCount() + 4000;

                }
            }
            ComponentManager::get().find<Enemy>();
            Enemy *e = ComponentManager::get().next<Enemy>();
            for(int i=0;i<3;i++)
            {
                if(e!=NULL && e->time()!=0) {
                    agony[i]->setPos((e->printPos()-float2(12.f,3.f)));
                    agony[i]->setText(e->time(),"s");
                    e->finded = true;
                }
                e = ComponentManager::get().next<Enemy>();
            }
            amunicja->setText("Amunicja: ",p->stan());
            timeOut2 = 60 - ((::GetTickCount() - timeOut)/1000);
            if(timeOut2 > 0)
                time->setText("Pozostaly czas: ",timeOut2);
            else if(timeOut2 == 0){
                gameState = TIMEEND;
                //timeOut = ::GetTickCount() + 3000;
            }
        }
        break;
    case GAMEOVER:
        if (::GetTickCount() > timeOut)
        {
            Smutek();
            exit(0);
        }
        break;
    case LEVELFINISHED:
        ++currentLevel;
        if (currentLevel>maxLevel)
        {
            gameState = YOUWON;
            //timeOut = ::GetTickCount() + 4000;
            currentLevel = 1;
            levelStart->setText("Level ", currentLevel);
        }
        else
        {
            Winning();
            ComponentManager::get().clear();
            Player *p;
            ComponentManager::get().find<Player>();
            p = ComponentManager::get().next<Player>();
            if (p!=NULL)
                Terrain::get().setViewPos(p->getPosition());
            gameState = LEVELSTART;
            ostringstream o;
            o<<"assets//level"<<currentLevel<<".txt";
            Terrain::get().create(o.str().c_str());
            levelStart->setText("Level ", currentLevel);
            timeOut = ::GetTickCount() + 3000;

        }
        break;
    case YOUWON:
        if (::GetTickCount() > timeOut)
        {
            Winning2();
            end();
        }
        break;
    case LEVELSTART:
        if (GetTickCount() > timeOut)
        {
            ComponentManager::get().find<Player>();
            Player *p = ComponentManager::get().next<Player>();
            if (p!=NULL)
            {
                Terrain::get().setViewPos(p->getPosition());
                gameState = PLAY;
            }
        }
        break;
    case TIMEEND:
        if (::GetTickCount() > timeOut) {
            gameState = GAMEOVER;
            Smutek();
        }
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(64, 64);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("GLUT w CodeBlocks");
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyb);
	glutReshapeFunc(resize);
	glutIdleFunc(idle);
	glutKeyboardUpFunc(keybUp);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    Terrain::get().create("assets//level1.txt");
    Terrain::get().setViewSize(float2(21,8));

    gameOver = new Sprite(ResourceFactory::get().load("assets//gameover.bmp"));
    youWon = new Sprite(ResourceFactory::get().load("assets//youwon.bmp"));

    levelStart = new SpriteText(Sprite(ResourceFactory::get().load("assets//font.bmp"), 128));
    levelStart->setText("Level ", currentLevel);

    przeterminowanie = new SpriteText(Sprite(ResourceFactory::get().load("assets//font.bmp"), 128));
    przeterminowanie->setText("Zabraklo czasu...");

    time = new SpriteText(Sprite(ResourceFactory::get().load("assets//font.bmp"), 128));
    time->setText(" ", 0);
    time->setColor(1,0,0);

    amunicja = new SpriteText(Sprite(ResourceFactory::get().load("assets//font.bmp"), 128));
    amunicja->setText(" ", 0);
    amunicja->setColor(0,1,0);

    for(int i=0;i<3;i++)
    {
        agony[i] = new SpriteText(Sprite(ResourceFactory::get().load("assets//font.bmp"), 128));
        agony[i]->setText(" ");
        agony[i]->setColor(1,1,1);
    }


    atexit(end);

    cout<<"Game started"<<endl;
	glutMainLoop();
}
