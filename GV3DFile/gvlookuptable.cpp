#include "gvlookuptable.h"

gvLookUpTable::gvLookUpTable()
{
    createCosTable(DEFAULT_ARRAY_SIZE);
}

gvLookUpTable::gvLookUpTable(int iSize)
{
    createCosTable(iSize);
}

gvLookUpTable::~gvLookUpTable()
{
    delete [] m_dArrCosLookUpTable;
    m_iArrSize = 0;
}

void gvLookUpTable::changeSizeLookupTableCos(int iNewSize)
{
    delete [] m_dArrCosLookUpTable;
    m_iArrSize = 0;
    createCosTable(iNewSize);
}

void gvLookUpTable::createCosTable(int iSize)
{
    if(iSize > 0)
    {
        m_iArrSize = iSize+1;
        m_dFactor = (2*PI)/(m_iArrSize-1);
        m_dArrCosLookUpTable = new double[m_iArrSize+1];

        for(int i = 0; i <= m_iArrSize; i++)
        {
            m_dArrCosLookUpTable[i] = cos(i*m_dFactor);
        }
    }
}

double gvLookUpTable::getCos(double dValue)
{
    while(dValue > 2*PI)
    {
        dValue -= 2*PI;
    }
    while(dValue < 0)
    {
        dValue += 2*PI;
    }
    return m_dArrCosLookUpTable[(int)(dValue / m_dFactor)];
}
