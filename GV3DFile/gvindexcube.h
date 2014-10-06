#ifndef GVINDEXCUBE_H
#define GVINDEXCUBE_H

#include <iostream>
#include <math.h>
#include "gvbinaryfunctions.h"

using namespace std;

class GVIndexCube
{
public:
    GVIndexCube();
    GVIndexCube(int* p_iImageWidth, int* p_iImageHeight, unsigned char* p_ucImageData,
                bool* p_bPixelFilled, GVIndexCube** p_GVImageArray);


    //SETTER
    bool setImageProperty(int* p_iImageWidth, int* p_iImageHeight, unsigned char* p_ucImageData,
                          bool* p_bPixelFilled);
    void setGVIndexStorageReference(GVIndexCube** p_GVImageArray);

    //GETTER
    int getHierarchyLevel();

    //ADD
    void addPixelsCube(unsigned int uiID, unsigned char ucMap, unsigned char* ucRed, unsigned char* ucGreen, unsigned char* ucBlue);
    void addReferenceCube(unsigned int uiID, unsigned char ucMap, unsigned int* uiArrID);

    //TRANSFORM AND RENDER
    void ApplyRotation_and_Render(double iArrPosXRotation[8], double iArrPosYRotation[8], unsigned char ucSortedByDstFromScreen[8],
                                  double iCenterPointX, double iCenterPointY);


private:
    //GLOBAL
    unsigned int m_uiID;

protected:
    //GLOBAL IMAGE DATA REFERENCES
    int* m_p_iImageWidth;
    int* m_p_iImageHeight;
    unsigned char* m_p_ucImageData;
    bool* m_p_bPixelFilled;
    GVIndexCube** m_p_GVImageArray;

private:
    //CHILD IMAGE INFO
    GVIndexCube** m_p_GVIndexCubeArray;
    unsigned char* m_ucRed;
    unsigned char* m_ucGreen;
    unsigned char* m_ucBlue;

protected:                   //TODO: Verify when everything is done what can be private
    //CURRENT CUBE DATA
    unsigned char m_ucMap;
    int m_iHierarchyLevel;
    int m_iRenderWidth;

    //ROTATION
    //MAYBE NOT NECESSARY IN PRIVATE
    //TODO: Modify: need 8 corner + center  todo: determiner si corner relative to center or absolute
    int m_iArrPosXRotation[9];      //m_iArrPosXRotation[0] = center absolute ???
    int m_iArrPosYRotation[9];      //m_iArrPosYRotation[0] = center absolute ???
    char m_cSortedByDstFromScreen[8];   //index begin at 0

};

#endif // GVINDEXCUBE_H
