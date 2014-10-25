#include "gvindexcube.h"

GVIndexCube::GVIndexCube()
{
    m_p_iImageWidth = 0;
    m_p_iImageHeight = 0;
    m_p_ucImageData = NULL;
    m_p_bPixelFilled = NULL;
}

GVIndexCube::GVIndexCube(int* p_iImageWidth, int* p_iImageHeight, unsigned char* p_ucImageData,
                         bool* p_bPixelFilled, GVIndexCube** p_GVImageArray)
{
    //Preset if error in setImageProperty
    m_p_iImageWidth = NULL;
    m_p_iImageHeight = NULL;
    m_p_ucImageData = NULL;
    m_p_bPixelFilled = NULL;

    setImageProperty(p_iImageWidth, p_iImageHeight, p_ucImageData, p_bPixelFilled);
    setGVIndexStorageReference(p_GVImageArray);
}

bool GVIndexCube::setImageProperty(int* p_iImageWidth, int* p_iImageHeight,
                                   unsigned char* p_ucImageData,  bool* p_bPixelFilled)
{
    if(*p_iImageWidth != 0 && *p_iImageHeight != 0 && p_ucImageData != NULL && p_bPixelFilled != NULL)
    {
        m_p_iImageWidth = p_iImageWidth;
        m_p_iImageHeight = p_iImageHeight;
        m_p_ucImageData = p_ucImageData;
        m_p_bPixelFilled = p_bPixelFilled;

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

void GVIndexCube::addPixelsCube(unsigned int uiID, unsigned char ucMap, int* ucRed, int* ucGreen, int* ucBlue)
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
        m_ucRed[i] = (unsigned char)ucRed[i];
        m_ucGreen[i] = (unsigned char)ucGreen[i];
        m_ucBlue[i] = (unsigned char)ucBlue[i];
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
    //TODO: PROTECTION IF ADDRESSES NULL
    if(m_iHierarchyLevel != 0)
    {

        for(int dst = 0; dst < 8; dst ++)
        {
            if(isBitHigh(m_ucMap, ucSortedByDstFromScreen[dst]))
            {
                //TODO: Call ApplyRotation_and_Render on child IF potential new pixel to
                //be written(not already written)
            }
        }
    }
    else
    {
        //CENTER POINT ROUNDED
        int iCenterPointXRounded = (int)round(dCenterPointX);
        int iCenterPointYRounded = (int)round(dCenterPointY);

        unsigned char ucIndexPixel = 0;
        //RENDER PIXELS IN ORDER
        for(int i = 0; i < 8; i++)
        {
            //IF A PIXEL IS PRESENT
            if((m_ucMap & (0x01 << i)))
            {
                //ACCESS CORRESPONDING PIXEL AND VERIFY IF IT IS NOT WRITTEN YET
                if(iArrPosXRotation[ucSortedByDstFromScreen[i]] < 0)
                {
                    if(iArrPosYRotation[ucSortedByDstFromScreen[i]] < 0)
                    {
                        //  ---------
                        //  | x |   |
                        //  ---------
                        //  |   |   |
                        //  ---------
                        if(!m_p_bPixelFilled[(iCenterPointXRounded-1)+((iCenterPointYRounded-1)*(*m_p_iImageWidth))])
                        {
                            //WRITE PIXEL
                            m_p_ucImageData[(iCenterPointXRounded-1+(iCenterPointYRounded-1)*(*m_p_iImageWidth))*3] = *(m_ucRed + ucIndexPixel);
                            m_p_ucImageData[(iCenterPointXRounded-1+(iCenterPointYRounded-1)*(*m_p_iImageWidth))*3+1] = m_ucGreen[ucIndexPixel];
                            m_p_ucImageData[(iCenterPointXRounded-1+(iCenterPointYRounded-1)*(*m_p_iImageWidth))*3+2] = m_ucBlue[ucIndexPixel];
                            m_p_bPixelFilled[(iCenterPointXRounded-1)+((iCenterPointYRounded-1)*(*m_p_iImageWidth))] = true;
                        }
                    }
                    else
                    {
                        //  ---------
                        //  |   |   |
                        //  ---------
                        //  | x |   |
                        //  ---------
                        if(!m_p_bPixelFilled[(iCenterPointXRounded-1)+((iCenterPointYRounded)*(*m_p_iImageWidth))])
                        {
                            //WRITE PIXEL
                            m_p_ucImageData[(iCenterPointXRounded-1+(iCenterPointYRounded)*(*m_p_iImageWidth))*3] = m_ucRed[ucIndexPixel];
                            m_p_ucImageData[(iCenterPointXRounded-1+(iCenterPointYRounded)*(*m_p_iImageWidth))*3+1] = m_ucGreen[ucIndexPixel];
                            m_p_ucImageData[(iCenterPointXRounded-1+(iCenterPointYRounded)*(*m_p_iImageWidth))*3+2] = m_ucBlue[ucIndexPixel];
                            m_p_bPixelFilled[(iCenterPointXRounded-1)+((iCenterPointYRounded)*(*m_p_iImageWidth))] = true;
                        }
                    }
                }
                else
                {
                    if(iArrPosYRotation[ucSortedByDstFromScreen[i]] < 0)
                    {
                        //  ---------
                        //  |   |x  |
                        //  ---------
                        //  |   |   |
                        //  ---------
                        if(!m_p_bPixelFilled[(iCenterPointXRounded)+((iCenterPointYRounded-1)*(*m_p_iImageWidth))])
                        {
                            //WRITE PIXEL
                            m_p_ucImageData[(iCenterPointXRounded+(iCenterPointYRounded-1)*(*m_p_iImageWidth))*3] = m_ucRed[ucIndexPixel];
                            m_p_ucImageData[(iCenterPointXRounded+(iCenterPointYRounded-1)*(*m_p_iImageWidth))*3+1] = m_ucGreen[ucIndexPixel];
                            m_p_ucImageData[(iCenterPointXRounded+(iCenterPointYRounded-1)*(*m_p_iImageWidth))*3+2] = m_ucBlue[ucIndexPixel];
                            m_p_bPixelFilled[(iCenterPointXRounded)+((iCenterPointYRounded-1)*(*m_p_iImageWidth))] = true;
                        }
                    }
                    else
                    {
                        //  ---------
                        //  |   |   |
                        //  ---------
                        //  |   | x |
                        //  ---------
                        if(!m_p_bPixelFilled[(iCenterPointXRounded)+((iCenterPointYRounded)*(*m_p_iImageWidth))])
                        {
                            //WRITE PIXEL
                            m_p_ucImageData[(iCenterPointXRounded+(iCenterPointYRounded)*(*m_p_iImageWidth))*3] = m_ucRed[ucIndexPixel];
                            m_p_ucImageData[(iCenterPointXRounded+(iCenterPointYRounded)*(*m_p_iImageWidth))*3+1] = m_ucGreen[ucIndexPixel];
                            m_p_ucImageData[(iCenterPointXRounded+(iCenterPointYRounded)*(*m_p_iImageWidth))*3+2] = m_ucBlue[ucIndexPixel];
                            m_p_bPixelFilled[(iCenterPointXRounded)+((iCenterPointYRounded)*(*m_p_iImageWidth))] = true;
                        }
                    }
                }
                ucIndexPixel++;
            }
        }
    }
}

