#ifndef GVIMAGE_H
#define GVIMAGE_H

#include <iostream>
#include <stdio.h>
#include <fstream>
#include "gvindexcube.h"

#define NUMBER_OF_CHANNELS      3

#define NO_ERRORS               0
#define UNABLE_TO_OPEN_FILE     1
#define INVALID_CUBE_SIZE       2
#define SIZE_NOT_BASE_2         3
#define FILE_CORRUPTED          4

using namespace std;

class GVImage: public GVIndexCube
{
public:
    GVImage();
    GVImage(char* p_cFilename);
    ~GVImage();

    int openFile(char* p_cFilename);

    int getWidth();
    int getHeight();
    unsigned char* getData();

    void setRotation(double dTheta, double dPhi);

    void generateImage();

private:
    int m_iSideLenght;
    int m_iNumberOfLevels;  //1 to n, where 1 => pixel level
    int* m_iArrCubeAtLevel;
    int m_iSizeOfGVImageArray;

    double m_dTheta;
    double m_dPhi;

    int m_iCenterPointX;
    int m_iCenterPointY;

    //(Constant for the duration of the execution)
    int m_iUnrotatedCornerX[8];
    int m_iUnrotatedCornerY[8];
    int m_iUnrotatedCornerZ[8];

    double m_dScreenRotatedCornerX[8];
    double m_dScreenRotatedCornerY[8];
    double m_dDstFromScreenRotated[8];
    unsigned char m_dCornerSortedByDst[8];
};

#endif // GVIMAGE_H
