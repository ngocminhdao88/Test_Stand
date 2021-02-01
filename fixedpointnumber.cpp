#include "fixedpointnumber.h"

FixedPointNumber::FixedPointNumber(int base)
{
    if(base != m_base && base > 0) {
        m_base = base;
    }
}

int FixedPointNumber::toFixedPointNumber(double number)
{
    return (int)(number * m_base);
}

double FixedPointNumber::fromFixedPointNumber(int number)
{
    return (double)(number / m_base);
}
