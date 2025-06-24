#ifndef GQ_TYPES_H
#define GQ_TYPES_H

#include <stdio.h>

namespace gQuake
{

    
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

    Matrix(int rows, int columns) : m_rows(rows), m_columns(columns) {}

private:
    int m_rows, m_columns;

};

}

#endif