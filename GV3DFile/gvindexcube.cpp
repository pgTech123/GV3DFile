#include "gvindexcube.h"

GVIndexCube::GVIndexCube()
{
    m_p_iImageWidth = 0;
    m_p_iImageHeight = 0;
    m_p_ucImageData = NULL;
}

GVIndexCube::GVIndexCube(int* p_iImageWidth, int* p_iImageHeight, unsigned char* p_ucImageData, GVIndexCube** p_GVImageArray)
{
    //Preset if error in setImageProperty
    m_p_iImageWidth = NULL;
    m_p_iImageHeight = NULL;
    m_p_ucImageData = NULL;

    setImageProperty(p_iImageWidth, p_iImageHeight, p_ucImageData);
    setGVIndexStorageReference(p_GVImageArray);
}

bool GVIndexCube::setImageProperty(int* p_iImageWidth, int* p_iImageHeight, unsigned char* p_ucImageData)
{
    if(*p_iImageWidth != 0 && *p_iImageHeight != 0 && p_ucImageData != NULL)
    {
        m_p_iImageWidth = p_iImageWidth;
        m_p_iImageHeight = p_iImageHeight;
        m_p_ucImageData = p_ucImageData;

        return true;
    }
    else
    {
        return false;
    }
}

void GVIndexCube::setGVIndexStorageReference(GVIndexCube** p_GVImageArray)
{
    m_p_GVImageArray = p_GVImageArray;
}

int GVIndexCube::getHierarchyLevel()
{
    return m_iHierarchyLevel;
}

void GVIndexCube::addPixelsCube(unsigned int uiID, unsigned char ucMap, unsigned char* ucRed, unsigned char* ucGreen, unsigned char* ucBlue)
{
    m_uiID = uiID;
    m_ucMap = ucMap;
    m_iHierarchyLevel = 0;

    //FILL PIXELS ACCORDING TO MAP
    int iPixelsNotEmpty = numberHighBits(m_ucMap);
    m_ucRed = new unsigned char[iPixelsNotEmpty];
    m_ucGreen = new unsigned char[iPixelsNotEmpty];
    m_ucBlue = new unsigned char[iPixelsNotEmpty];

    for(int i = 0; i < iPixelsNotEmpty; i++)
    {
        //ADD PIXEL
        m_ucRed[i] = *(ucRed+i);
        m_ucGreen[i] = *(ucGreen+i);
        m_ucBlue[i] = *(ucBlue+i);
    }
}

void GVIndexCube::addReferenceCube(unsigned int uiID, unsigned char ucMap, unsigned int* uiArrID)
{
    m_uiID = uiID;
    m_ucMap = ucMap;

    //FILL REFERENCES ACCORDING TO MAP
    int iReferencesNotEmpty = numberHighBits(m_ucMap);
    m_p_GVIndexCubeArray = new GVIndexCube*[iReferencesNotEmpty];

    for(int i = 0; i < iReferencesNotEmpty; i++)
    {
        //ADD REFERENCES
        m_p_GVIndexCubeArray[i] = *(m_p_GVImageArray + *(uiArrID + i));
        m_iHierarchyLevel = m_p_GVIndexCubeArray[i]->getHierarchyLevel() + 1;
    }

    //COMPUTE RENDER WIDTH
    m_iRenderWidth = 2 * sqrt(pow(pow(2,m_iHierarchyLevel),2)*3);
}

void GVIndexCube::ApplyRotation_and_Render( double iArrPosXRotation[8], //relative
                                            double iArrPosYRotation[8], //relative
                                            unsigned char ucSortedByDstFromScreen[8],
                                            double dCenterPointX,
                                            double dCenterPointY)
{
    if(m_iHierarchyLevel != 0)
    {

        for(int dst = 0; dst < 8; dst ++)
        {
            if(isBitHigh(m_ucMap, ucSortedByDstFromScreen[dst]))
            {
                //TODO: Call ApplyRotation_and_Render on child IF potential new pixel to be written
            }
        }
    }
    else
    {
        //CENTER POINT ROUNDED
        int iCenterPointXRounded = (int)round(dCenterPointX);
        int iCenterPointYRounded = (int)round(dCenterPointY);

        //RENDER PIXELS IN ORDER
        for(int i = 0; i < 8; i++)
        {
            //IF A PIXEL IS PRESENT
            if((m_ucMap & (0x01 << i)))
            {
                //ACCESS CORRESPONDING PIXEL AND VERIFY IF ALREADY WRITTEN

            }
        }









        //DISTANCE BETWEEN CORNERS / 2
        double dHalfDstBtw2CornersXX = (iArrPosXRotation[0] - iArrPosXRotation[3])/2;
        double dHalfDstBtw2CornersXY = (iArrPosYRotation[0] - iArrPosYRotation[3])/2;
        double dHalfDstBtw2CornersYX = (iArrPosXRotation[0] - iArrPosXRotation[1])/2;
        double dHalfDstBtw2CornersYY = (iArrPosYRotation[0] - iArrPosYRotation[1])/2;
        double dHalfDstBtw2CornersZX = (iArrPosXRotation[0] - iArrPosXRotation[4])/2;
        double dHalfDstBtw2CornersZY = (iArrPosYRotation[0] - iArrPosYRotation[4])/2;

        for(int dst = 0; dst < 8; dst ++)
        {
            if(isBitHigh(m_ucMap, ucSortedByDstFromScreen[dst]))
            {
                //SQUARE RANGE
                double dTop;// = dDeltaCenterPointRoundedY + iArrPosXRotation[/*TODO*/]/*TODO...*/;
                double dBottom;
                double dLeft;
                double dRight;
                //TODO: base sur la position du pixel apres rotation...


                //RENDER PIXELS
                //TODO:
                //centerpoint+top, centerpoint-bottom, ...l-r
                //cast(value*16)en x et en y
                int iImportanceInPixelX;
                int iImportanceInPixelY;
                int iPixelRenderedFactor = iImportanceInPixelX * iImportanceInPixelY;

                //value caste X * value caste Y * value pixel = pixel rendu
                //WRITE PIXEL
                //TODO:

                //TODO: add transparency
            }
        }
    }
}

