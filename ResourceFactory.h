#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include <map>

using std::map;

#include "Texture2D.h"

class ResourceFactory
{
public:
    static ResourceFactory &get(void)
    {
        static ResourceFactory instance;
        return instance;
    }

    Texture2D *load(const char *);
    virtual ~ResourceFactory();
protected:
    map<const char*, Texture2D *> textures;
private:
    ResourceFactory();
    ResourceFactory(const ResourceFactory& other);
    ResourceFactory& operator=(const ResourceFactory& other);
};

#endif // RESOURCEFACTORY_H
