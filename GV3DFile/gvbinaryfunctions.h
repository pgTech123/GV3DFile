#ifndef GVBINARYFUNCTIONS_H
#define GVBINARYFUNCTIONS_H

#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

int numberHighBits(unsigned char ucNumber);
int numberHighBits(int ucNumber);

bool isBase2(int iNumber);

int firstHighBit(int iNumber);

bool isBitHigh(unsigned char iNumber, unsigned char iBit);

double computeRotationX(int iX, int iZ, double dRPhi);
double computeRotationY(int iX, int iY, int iZ, double dRTetha, double dRPhi);
double computeRotationZ(int iX, int iY, int iZ, double dRTetha, double dRPhi);

double computePosXOnScreen(int iX, int iY, int iZ, double dRTetha, double dRPhi);
double computePosYOnScreen(int iX, int iY, int iZ, double dRTetha, double dRPhi);

void sort(double dUnsortedArray[8], unsigned char uc_IndexSorted[8]);

#endif // GVBINARYFUNCTIONS_H
