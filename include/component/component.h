#ifndef COMPONENT_H
#define COMPONENT_H

#include <cstdint>
#include <SDL3/SDL.h>


class Component {
public:
    virtual void render() = 0;
    virtual void update() = 0;
    virtual ~Component() = default;
};


#endif