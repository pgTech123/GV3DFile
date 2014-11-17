/*************************************************************************
 * Project:     GV3D File
 *
 * File Name:   GVImage.h
 *
 * Author:      Pascal Gendron
 *
 * Version:     0.0.1
 * ************************************************************************/

#ifndef GVIMAGE_H
#define GVIMAGE_H

#include <iostream>
#include <stdio.h>
#include <fstream>
#include "gvindexcube.h"

/* RGB Image */
#define NUMBER_OF_CHANNELS      3

/* Error Definition */
#define NO_ERRORS               0
#define UNABLE_TO_OPEN_FILE     1
#define INVALID_CUBE_SIZE       2
#define SIZE_NOT_BASE_2         3
#define FILE_CORRUPTED          4

using namespace std;

/*************************************************************************
 * GVImage Class:
 *
 * The purpose of this class is to represent the 3D Image. It is used by
 * the user to make actions on the image. It is also used to abstract the
 * building blocs of the image and to make the rendering process transparent
 * for the user.
 *************************************************************************/

class GVImage: public GVIndexCube
{
public:
    GVImage();
    GVImage(const char* p_cFilename);
    ~GVImage();

    int openFile(const char* p_cFilename);

    int getWidth();
    int getHeight();
    unsigned char* getData();

    void setRotation(double dTheta, double dPhi);

    void generateImage();

private:
    void initializeImage();
    void deleteCurrentImage();

    /* File Functions */
    int readImageFile(fstream *file);
    int verifyImageSideLenght(int iSideLenght);
    void setImageProperties();
    void setImageCenterPoint();
    void setUnrotatedCorners();
    void setNumberOfLevels();

    void readNumOfMaps(fstream *file);
    int readCubes(fstream *file);
    int readPixelCubes(fstream *file);
    int readIndexCubes(fstream *file);
    int readMap(fstream *file, unsigned char* ucMap, int* iNumOfPix);

private:
    bool m_bImageStored;

    /* Cube Rotation */
    double m_dTheta;
    double m_dPhi;

    gvLookUpTable *m_pLookupTable;

    int m_iSideLenght;
    int m_iNumberOfLevels;  //1 to n, where 1 => pixel level
    int* m_iArrCubeAtLevel;
    int m_iNumberOfCubes;


    int m_iCenterPointX;
    int m_iCenterPointY;


    int m_iUnrotatedCornerX[8];     /* Constant for the duration of the execution */
    int m_iUnrotatedCornerY[8];     /* Constant for the duration of the execution */
    int m_iUnrotatedCornerZ[8];     /* Constant for the duration of the execution */

    double m_dScreenRotatedCornerX[8];
    double m_dScreenRotatedCornerY[8];
    double m_dDstFromScreenRotated[8];
    unsigned char m_dCornerSortedByDst[8];
};

#endif // GVIMAGE_H
