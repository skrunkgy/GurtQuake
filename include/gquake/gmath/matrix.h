#pragma once

#include <gquake/gquake.h>

namespace gQuake
{

template <class T, int rows, int columns>
class Matrix
{

    union
    {
        struct
        {
            T m_00;
            T m_01;
            T m_02;
            T m_03;
            T m_10;
            T m_11;
            T m_12;
            T m_13;
            T m_20;
            T m_21;
            T m_22;
            T m_23;
            T m_30;
            T m_31;
            T m_32;
            T m_33;
        };
        T m_data[16];
        
    };

};

}