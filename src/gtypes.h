// ###### gtypes.h ######

#ifndef GQ_TYPES_H
#define GQ_TYPES_H

namespace gQuake
{

// Item type that can be rendered, used for the render queue
class RenderObject
{
public:
    virtual void Render() = 0;
    virtual ~RenderObject() {}
};

typedef struct
{
    float r, g, b, a;
} color;

}

#endif