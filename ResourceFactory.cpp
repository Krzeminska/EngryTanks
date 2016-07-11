#include <iostream>

using std::cout;
using std::endl;

#include "ResourceFactory.h"

ResourceFactory::ResourceFactory()
{
    cout<<"ResourceFactory::ResourceFactory()"<<endl;
}

ResourceFactory::~ResourceFactory()
{
    for (map<const char*, Texture2D *>::iterator i = textures.begin();
        i != textures.end();
        ++i)
        {
            delete (i->second);
        }
    cout<<"ResourceFactory::~ResourceFactory()"<<endl;
}

Texture2D *ResourceFactory::load(const char *fname)
{
    Texture2D *t = get().textures[fname];
    if (t == NULL)
        t = get().textures[fname] = new Texture2D(fname);
    return t;
}
