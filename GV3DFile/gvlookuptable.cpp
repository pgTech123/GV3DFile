#include "gvlookuptable.h"

gvLookUpTable::gvLookUpTable()
{
    createCosTable(DEFAULT_ARRAY_SIZE);
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
    //TODO: FILL ARRAY
    m_iArrSize = iSize;
}
