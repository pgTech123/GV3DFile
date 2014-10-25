#ifndef GVLOOKUPTABLE_H
#define GVLOOKUPTABLE_H

#define DEFAULT_ARRAY_SIZE  720;

class gvLookUpTable
{
public:
    gvLookUpTable();
    ~gvLookUpTable();

    void changeSizeLookupTableCos(int iNewSize);
    //TODO: Access Lookup table

private:
    void createCosTable(int iSize);

    double *m_dArrCosLookUpTable;
    int m_iArrSize;
};

#endif // GVLOOKUPTABLE_H
