#ifndef GVTESTS_H
#define GVTESTS_H

#include <iostream>
#include <math.h>

#include "gvbinaryfunctions.h"
#include "gvlookuptable.h"
#include "gvtransform.h"
#include "gvmatrix.h"

using namespace std;

//UNITARY TESTS
void runTestSort();
void runTestLookupTable();
void runTestLookupTable(gvLookUpTable* tbl);

/* Return : True = Pass; False = Fail */
bool runTestMultiply3x3Matrix();


#endif // GVTESTS_H
