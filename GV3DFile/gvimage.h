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
    unsigned char* m_ucArrTransparencyMap;

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








/*
class GVImage
{
public:
    GVImage();
    GVImage(char*);

    void openFile(char*);
    void generateImage(unsigned char pixels[], int width, int height);

    // TRANSFORM
    //TO GVIMAGE void rotateInitialCube();   //Creates struct storing rotation

private:
    //File Content
    int m_cubeWidth;
    int m_cubeHeight;
    int m_cubeDepth;

    int m_indexWidth;
    int m_indexHeight;
    int m_indexDepth;

    int m_nonEmpty8x8x8Cube;

    unsigned long *m_8x8x8CubeIndexArray;
    bool *m_8x8x8InternalBoolIndex;
    //TODO: Change int to char(when binary)
    unsigned int *m_pixelsData;
};
*/
#endif // GVIMAGE_H
