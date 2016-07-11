#include "ComponentManager.h"

void ComponentManager::add(Component *c)
{
    components.push_front(c);
}

void ComponentManager::update()
{
    for (list<Component*>::iterator i = components.begin();
        i != components.end();
        ++i)
        (*i)->update();
    for (list<Component*>::iterator i = components.begin();
        i!=components.end();)
            if ( (*i)->deleted )
            {
                delete *i;
                i = components.erase(i);
            }
            else
                ++i;
}

void ComponentManager::draw()
{
    for (list<Component*>::iterator i = components.begin();
        i != components.end();
        ++i)
        (*i)->draw();
}

void ComponentManager::clear()
{
    for (list<Component*>::iterator i = components.begin();
        i != components.end();
        ++i)
        delete *i;
    components.clear();
}
