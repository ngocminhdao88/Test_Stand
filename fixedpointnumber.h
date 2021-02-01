#ifndef FIXEDPOINTNUMBER_H
#define FIXEDPOINTNUMBER_H


class FixedPointNumber
{
public:
    FixedPointNumber(int base);

    int toFixedPointNumber(double number);
    double fromFixedPointNumber(int number);

private:
    int m_base = 1;
};

#endif // FIXEDPOINTNUMBER_H
