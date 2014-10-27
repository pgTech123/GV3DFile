#ifndef GVLOOKUPTABLE_H
#define GVLOOKUPTABLE_H

#include <iostream>
#include <math.h>

#define DEFAULT_ARRAY_SIZE  720
#define PI  3.14159265359

using namespace std;

class gvLookUpTable
{
public:
    gvLookUpTable();
    gvLookUpTable(int iSize);
    ~gvLookUpTable();

    void changeSizeLookupTableCos(int iNewSize);
    double getCos(double dValue);

private:
    void createCosTable(int iSize);

    double *m_dArrCosLookUpTable;
    int m_iArrSize;
    double m_dFactor;
};

#endif // GVLOOKUPTABLE_H
