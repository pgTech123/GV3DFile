#include "gvtests.h"


void runTestSort()
{
    //TEST SORT INDEX
    double arrTest[8] = {-28,1,6.9,3,4,5,7,-6.2};
    unsigned char indexTest[8];

    sort(arrTest, indexTest);

    cout << "Array Sort Test" << endl;
    for(int i = 0 ; i < 8; i++)
    {
        cout << (int)indexTest[i] << endl;
    }

    cout << "END TESTS" << endl;
}

void runTestLookupTable()
{
    //TEST LOOK UP TABLE
    double valuesToTest[15] = {0, PI, 2*PI, 3*PI, 4*PI, 100*PI, 50, 6, 3.26, 59, 2, 15, 7, 9, 56};


    cout << "TEST LOOKUP TABLE" << endl << endl;

    cout << "PRECISION Default" << endl << endl;
    gvLookUpTable lookupTable;
    cout << "WANTED         RECEIVED" << endl;
    for(int i = 0; i < 15; i++)
    {
        cout << cos(valuesToTest[i]) << "       " << lookupTable.getCos(valuesToTest[i]) << endl;
    }


    cout << "-------------------------------------" << endl;
    cout << "PRECISION 5000" << endl << endl;
    gvLookUpTable lookupTable2(5000);
    cout << "WANTED         RECEIVED" << endl;
    for(int i = 0; i < 15; i++)
    {
        cout << cos(valuesToTest[i]) << "       " << lookupTable2.getCos(valuesToTest[i]) << endl;
    }


    cout << "-------------------------------------" << endl;
    cout << "PRECISION DYNAMIC 50" << endl << endl;
    lookupTable2.changeSizeLookupTableCos(50);
    cout << "WANTED         RECEIVED" << endl;
    for(int i = 0; i < 15; i++)
    {
        cout << cos(valuesToTest[i]) << "       " << lookupTable2.getCos(valuesToTest[i]) << endl;
    }

    cout << "END TESTS" << endl;
}
