#ifndef GVTRANSFORM_H
#define GVTRANSFORM_H

#include <math.h>


#include <iostream>
using namespace std;

#define PI  3.14159265359

class GVTransform
{
public:
    GVTransform();

    /* Setters */
    void setUnrotatedCornersCorners(int iCenterPointX, int iCenterPointY, int iSideLenght);
    void setAngles(double dTheta, double dPhi);

    /* Computing */
    void computeRotation(double* dScreenRotatedCornerX, double* dScreenRotatedCornerY, double* dRotatedCornerZ);

private:
    void computeSinAndCos();

private:
    /* Angles */
    double m_dTheta;
    double m_dPhi;

    /* Trigo */
    double m_dCosTheta;
    double m_dCosPhi;
    double m_dSinTheta;
    double m_dSinPhi;

    /* Unrotated Corners */
    int m_iUnrotatedCornerX[8];
    int m_iUnrotatedCornerY[8];
    int m_iUnrotatedCornerZ[8];

    /* Dst from middle to corner */
    double dstFromMiddle2Corner;

    /* Image Center Point */
    int m_iCenterPointX;
    int m_iCenterPointY;
};

#endif // GVTRANSFORM_H
