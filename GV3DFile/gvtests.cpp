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

bool runTestMultiply3x3Matrix()
{
    double dMat1[3][3] = {{1,0,0}, {0,1,0},{0,0,1}};
    double dMat2[3][1] = {1,2,3};
    double dMatResult[3][1];
    /*GVMatrix mat1(3, 3, dMat1);
    GVMatrix mat2(3, 3, dMat2);
    GVMatrix matResult(3, 3);

    mat1.multiply(mat2, matResult);
    double **dMatResult = matResult.getData();
    */
    GVTransform transformGV;

    //transformGV.multiply3x3_by_1x3Matrix(dMat1, dMat2,dMatResult);

    /*Print*/
    for(int i = 0; i < 3; i++)
    {
        cout<< dMatResult[i][0]  << endl;
    }
}
