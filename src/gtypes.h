#ifndef GQ_TYPES_H
#define GQ_TYPES_H

#include <stdio.h>

namespace gQuake
{

// Item type that can be rendered, used for the render queue

class Serialize
{

public:
    Serialize();
    virtual void Store(const char* filepath) = 0;
    
    // no idea how this code execution will work, we will see
    template <class gq_Class>
    static gq_Class* Load(const char* filepath);

};


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


class Matrix
{

public:

    Matrix(int rows, int columns)
    {
        m_rows = rows;
        m_columns = columns;
    }

private:
    int m_rows, m_columns;

};

}

#endif