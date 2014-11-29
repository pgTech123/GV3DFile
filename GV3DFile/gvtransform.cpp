#include "gvtransform.h"

GVTransform::GVTransform()
{
    setAngles(0,0);
}

void GVTransform::setAngles(double dTheta, double dPhi)
{
    m_dTheta = dTheta;
    m_dPhi = dPhi;
    computeSinAndCos();
}

void GVTransform::setUnrotatedCornersCorners(int iCenterPointX, int iCenterPointY, int iSideLenght)
{
    m_iCenterPointX = iCenterPointX;
    m_iCenterPointY = iCenterPointY;

    m_iUnrotatedCornerX[0] = -iSideLenght/2;
    m_iUnrotatedCornerY[0] = iSideLenght/2;
    m_iUnrotatedCornerZ[0] = iSideLenght/2;

    m_iUnrotatedCornerX[1] = iSideLenght/2;
    m_iUnrotatedCornerY[1] = iSideLenght/2;
    m_iUnrotatedCornerZ[1] = iSideLenght/2;

    m_iUnrotatedCornerX[2] = iSideLenght/2;
    m_iUnrotatedCornerY[2] = iSideLenght/2;
    m_iUnrotatedCornerZ[2] = -1*(iSideLenght/2);

    m_iUnrotatedCornerX[3] = -iSideLenght/2;
    m_iUnrotatedCornerY[3] = iSideLenght/2;
    m_iUnrotatedCornerZ[3] = -1*(iSideLenght/2);

    m_iUnrotatedCornerX[4] = -iSideLenght/2;
    m_iUnrotatedCornerY[4] = -iSideLenght/2;
    m_iUnrotatedCornerZ[4] = (iSideLenght/2);

    m_iUnrotatedCornerX[5] = iSideLenght/2;
    m_iUnrotatedCornerY[5] = -iSideLenght/2;
    m_iUnrotatedCornerZ[5] = (iSideLenght/2);

    m_iUnrotatedCornerX[6] = iSideLenght/2;
    m_iUnrotatedCornerY[6] = -iSideLenght/2;
    m_iUnrotatedCornerZ[6] = -1*(iSideLenght/2);

    m_iUnrotatedCornerX[7] = -iSideLenght/2;
    m_iUnrotatedCornerY[7] = -iSideLenght/2;
    m_iUnrotatedCornerZ[7] = -1*(iSideLenght/2);
}

void GVTransform::computeRotation(double *dScreenRotatedCornerX, double *dScreenRotatedCornerY, double *dRotatedCornerZ)
{
    for(int i = 0; i < 8; i++)
    {
        dScreenRotatedCornerX[i] = (m_iUnrotatedCornerX[i] * m_dCosTheta) +
                                   m_iCenterPointX;

        dScreenRotatedCornerY[i] = (m_iUnrotatedCornerY[i]*m_dCosPhi) +
                                   m_iCenterPointY;

        /*******************************************************
         * "-1" to respect axis (-1 = far, 1 = close) so must be
         * inverted for sorting
         ******************************************************/
        dRotatedCornerZ[i] = -m_iUnrotatedCornerZ[i]*m_dSinTheta*m_dSinPhi;
    }
}

void GVTransform::computeSinAndCos()
{
    /*Precompute value of sin and cos*/
    m_dCosTheta = cos(m_dTheta);
    m_dSinTheta = sin(m_dTheta+PI/2);
    m_dCosPhi = cos(m_dPhi);
    m_dSinPhi = sin(m_dPhi+PI/2);
}

/*
double GVTransform::computeRotationX(double dRTetha, double dRPhi, double* dScreenRotatedCornerX)
{

    return iX;//iX*cos(dRPhi) + iZ*sin(dRPhi);
}

double GVTransform::computeRotationY(double dRTetha, double dRPhi, double* dScreenRotatedCornerX)
{

    return iY;//iX *sin(dRTetha)*sin(dRPhi) + iY*cos(dRTetha) - iZ*sin(dRTetha)*cos(dRPhi);
}

double GVTransform::computeRotationZ(double dRTetha, double dRPhi, double* dScreenRotatedCornerX)
{
    return -1;//(-iX)*cos(dRTetha)*sin(dRPhi) - iY*sin(dRTetha) + iZ*cos(dRTetha)*cos(dRPhi);//-1 to respec axis convension
}

double GVTransform::computePosXOnScreen(double dRTetha, double dRPhi, double* dScreenRotatedCornerX)
{
    return computeRotationX(iX, iZ, dRPhi)/computeRotationZ(iX, iY, iZ, dRTetha, dRPhi);
}

double GVTransform::computePosYOnScreen(double dRTetha, double dRPhi, double* dScreenRotatedCornerX)
{
    return computeRotationY(iX, iY, iZ, dRTetha, dRPhi)/computeRotationZ(iX, iY, iZ, dRTetha, dRPhi);
}
*/
