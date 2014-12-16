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


    dstFromMiddle2Corner = sqrt((iSideLenght/2)*(iSideLenght/2)*3);
    dstFromMiddle2CornerV2 = sqrt((iSideLenght/2)*(iSideLenght/2)*2);
}

void GVTransform::setDistanceFromCamera(double dDstFromCam)
{
    m_dDstFromCam = dDstFromCam;
}

void GVTransform::computeRotation(double *dScreenRotatedCornerX, double *dScreenRotatedCornerY, double *dRotatedCornerZ)
{
    double test[8];
    /*TODO: Faire la trigo comme du monde et corriger les erreurs */
    test[0] = dstFromMiddle2Corner * cos(m_dPhi+(1*PI/4));
    test[1] = dstFromMiddle2Corner * cos(m_dPhi+(1*PI/4));
    test[2] = dstFromMiddle2Corner * cos(m_dPhi+(3*PI/4));
    test[3] = dstFromMiddle2Corner * cos(m_dPhi+(3*PI/4));
    test[4] = dstFromMiddle2Corner * cos(m_dPhi+(7*PI/4));
    test[5] = dstFromMiddle2Corner * cos(m_dPhi+(7*PI/4));
    test[6] = dstFromMiddle2Corner * cos(m_dPhi+(5*PI/4));
    test[7] = dstFromMiddle2Corner * cos(m_dPhi+(5*PI/4));
    /* Rotation Theta */
    dScreenRotatedCornerX[0] = ( cos(m_dTheta+1*PI/4) * dstFromMiddle2CornerV2) + m_iCenterPointX;
    dScreenRotatedCornerX[1] = ( cos(m_dTheta+3*PI/4) * dstFromMiddle2CornerV2) + m_iCenterPointX;
    dScreenRotatedCornerX[2] = ( cos(m_dTheta+5*PI/4) * dstFromMiddle2CornerV2) + m_iCenterPointX;
    dScreenRotatedCornerX[3] = ( cos(m_dTheta+7*PI/4) * dstFromMiddle2CornerV2) + m_iCenterPointX;
    dScreenRotatedCornerX[4] = ( cos(m_dTheta+1*PI/4) * dstFromMiddle2CornerV2) + m_iCenterPointX;
    dScreenRotatedCornerX[5] = ( cos(m_dTheta+3*PI/4) * dstFromMiddle2CornerV2) + m_iCenterPointX;
    dScreenRotatedCornerX[6] = ( cos(m_dTheta+5*PI/4) * dstFromMiddle2CornerV2) + m_iCenterPointX;
    dScreenRotatedCornerX[7] = ( cos(m_dTheta+7*PI/4) * dstFromMiddle2CornerV2) + m_iCenterPointX;

    /* Rotation Phi */
    dScreenRotatedCornerY[0] = dstFromMiddle2CornerV2*sin(m_dPhi+(1*PI/4)) + m_iCenterPointY;
    dScreenRotatedCornerY[1] = dstFromMiddle2CornerV2*sin(m_dPhi+(1*PI/4)) + m_iCenterPointY;
    dScreenRotatedCornerY[2] = dstFromMiddle2CornerV2*sin(m_dPhi+(3*PI/4)) + m_iCenterPointY;
    dScreenRotatedCornerY[3] = dstFromMiddle2CornerV2*sin(m_dPhi+(3*PI/4)) + m_iCenterPointY;
    dScreenRotatedCornerY[4] = dstFromMiddle2CornerV2*sin(m_dPhi+(7*PI/4)) + m_iCenterPointY;
    dScreenRotatedCornerY[5] = dstFromMiddle2CornerV2*sin(m_dPhi+(7*PI/4)) + m_iCenterPointY;
    dScreenRotatedCornerY[6] = dstFromMiddle2CornerV2*sin(m_dPhi+(5*PI/4)) + m_iCenterPointY;
    dScreenRotatedCornerY[7] = dstFromMiddle2CornerV2*sin(m_dPhi+(5*PI/4)) + m_iCenterPointY;

    /*TODO CORRECTLY*/
    for(int i = 0; i < 8; i++)
    {
        /* Distance from viewer */
        dRotatedCornerZ[i] = -dstFromMiddle2Corner*sin(m_dTheta+(i*PI/2))*sin(m_dPhi+((i-1)*PI/2));
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
